/*
* Standard in kernel modules
*/
#include <linux/kernel.h> /* Все-таки мы работаем с ядром! */
#include <linux/module.h> /* Необходимо для любого модуля */
#include <linux/workqueue.h> /* очереди задач */
#include <linux/sched.h> /* Взаимодействие с планировщиком
*/
#include <linux/interrupt.h> /* определение irqreturn_t */
#include <asm/io.h>
#define MY_WORK_QUEUE_NAME "WQsched.c"
static struct workqueue_struct *my_workqueue;
/*
* Эта функция вызывается ядром, поэтому в ней будут безопасны
все действия
* которые допустимы в модулях ядра.
*/
static void got_char(void *scancode)
{
printk("Scan Code %x %s.\n",
(int)*((char *)scancode) & 0x7F,
*((char *)scancode) & 0x80 ? "Released" : "Pressed");
}
/*
* Обработчик прерываний от клавиатуры. Он считывает информацию
с клавиатуры
* и передает ее менее критичной по времени исполнения части,
* которая будет запущена сразу же, как только ядро сочтет это
возможным.
*/
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs
*regs)
{
/*
* Эти переменные объявлены статическими, чтобы имелась
возможность
* доступа к ним (посредством указателей) из "нижней
половины".
*/
static int initialised = 0;
static unsigned char scancode;
static struct work_struct task;
unsigned char status;
/*
* Прочитать состояние клавиатуры
*/
status = inb(0x64);
scancode = inb(0x60);
if (initialised == 0) {
INIT_WORK(&task, got_char, &scancode);
initialised = 1;
} else {
PREPARE_WORK(&task, got_char, &scancode);
}
queue_work(my_workqueue, &task);
return IRQ_HANDLED;
}
/*
* Инициализация модуля - регистрация обработчика прерывания
*/
int init_module()
{
my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
/*
* Поскольку стандартный обработчик прерываний от клавиатуры
не может
* сосуществовать с таким как наш, то придется запретить его
* (освободить IRQ) прежде, чем что либо сделать.
* Но поскольку мы не знаем где он находится в ядре, то мы
лишены
* возможности переустановить его - поэтому компьютер придется
перезагрузить
* после опробования этого примера.
*/
free_irq(1, NULL);
/*
* Подставить свой обработчик (irq_handler) на IRQ 1.
* SA_SHIRQ означает, что мы допускаем возможность совместного
* обслуживания этого IRQ другими обработчиками.
*/
return request_irq(1, /* Номер IRQ */
irq_handler, /* наш обработчик */
SA_SHIRQ,
"test_keyboard_irq_handler",
(void *)(irq_handler));
}
/*
* Завершение работы
*/
void cleanup_module()
{
/*
* Эта функция добавлена лишь для полноты изложения.
* Она вообще бессмысленна, поскольку я не вижу способа
* восстановить стандартный обработчик прерываний от
клавиатуры
* поэтому необходимо выполнить перезагрузку системы.
*/
free_irq(1, NULL);
}
/*
* некоторые функции, относящиеся к work_queue
* доступны только если модуль лицензирован под GPL
*/
MODULE_LICENSE("GPL");