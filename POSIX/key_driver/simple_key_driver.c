#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/slab.h>

#include <linux/interrupt.h>
#include <asm/io.h>

MODULE_AUTHOR("Alex.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple driver for Intel based keyboard");

#define MY_WORK_QUEUE_NAME "my_queue"
static struct workqueue_struct* my_workqueue;
static struct work_struct* work;
static int initialised = 0;
static char scancode = 10;



//---Printing char function
void got_char()
{
	printk(KERN_ALERT"Code received %x %c %s\n",(int)scancode, scancode,
		(int)scancode & 0x80 ? "Released" : "Pressed");
	printk(KERN_ALERT"My keyboard driver : irq handled!");
}

//---Interrupt function
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs* regs)
{
//	static unsigned char scancode;

	unsigned char status;	
	scancode = inb(0x60); 
	status = inb(0x64);
	

	if (!initialised)
	{
		initialised = 1;	
		INIT_WORK((struct work_struct *) work, (void *) got_char);
	}
	else
	{
		//PREPARE_WORK(&work, (void *)got_char);
	//	shedule_work(&work);
		PREPARE_WORK(work, (void *)got_char);
		queue_work(my_workqueue, work); //---Put our program into queue
	}

	return IRQ_HANDLED;
}

//---Load driver 
static int __init load_driver(void)
{
	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);	//---Creting workqueue

	if (my_workqueue)
	{
		work = (struct work_struct *)kmalloc(sizeof(struct work_struct), GFP_KERNEL);	//---Creating work

		if (work)
		{
			INIT_WORK(work, (void *)got_char);	//---Connect work with function
			queue_work(my_workqueue, (void *)work);
		}
		else
		{
			printk(KERN_ALERT"Animus error : can't create work.\n");
			return 1;
		}
	}
	else
	{
		printk(KERN_ALERT"Animus, error: workqueue aws't been created.\n");		
		return 1;
	}

	printk(KERN_ALERT"Animus in kernel.\n");
	free_irq(1, NULL);
	return request_irq(1, (irq_handler_t) irq_handler, IRQF_SHARED, "test_keyboard", (void *) irq_handler);	
}


//---Release driver
static void __exit release_driver(void)
{
	printk(KERN_ALERT"Animus left then linux kernel.\n");
}

module_init(load_driver);
module_exit(release_driver);
