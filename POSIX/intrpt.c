/*
* Standard in kernel modules
*/
#include <linux/kernel.h> /* ���-���� �� �������� � �����! */
#include <linux/module.h> /* ���������� ��� ������ ������ */
#include <linux/workqueue.h> /* ������� ����� */
#include <linux/sched.h> /* �������������� � �������������
*/
#include <linux/interrupt.h> /* ����������� irqreturn_t */
#include <asm/io.h>
#define MY_WORK_QUEUE_NAME "WQsched.c"
static struct workqueue_struct *my_workqueue;
/*
* ��� ������� ���������� �����, ������� � ��� ����� ���������
��� ��������
* ������� ��������� � ������� ����.
*/
static void got_char(void *scancode)
{
printk("Scan Code %x %s.\n",
(int)*((char *)scancode) & 0x7F,
*((char *)scancode) & 0x80 ? "Released" : "Pressed");
}
/*
* ���������� ���������� �� ����������. �� ��������� ����������
� ����������
* � �������� �� ����� ��������� �� ������� ���������� �����,
* ������� ����� �������� ����� ��, ��� ������ ���� ������ ���
���������.
*/
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs
*regs)
{
/*
* ��� ���������� ��������� ������������, ����� �������
�����������
* ������� � ��� (����������� ����������) �� "������
��������".
*/
static int initialised = 0;
static unsigned char scancode;
static struct work_struct task;
unsigned char status;
/*
* ��������� ��������� ����������
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
* ������������� ������ - ����������� ����������� ����������
*/
int init_module()
{
my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
/*
* ��������� ����������� ���������� ���������� �� ����������
�� �����
* �������������� � ����� ��� ���, �� �������� ��������� ���
* (���������� IRQ) ������, ��� ��� ���� �������.
* �� ��������� �� �� ����� ��� �� ��������� � ����, �� ��
������
* ����������� �������������� ��� - ������� ��������� ��������
�������������
* ����� ����������� ����� �������.
*/
free_irq(1, NULL);
/*
* ���������� ���� ���������� (irq_handler) �� IRQ 1.
* SA_SHIRQ ��������, ��� �� ��������� ����������� �����������
* ������������ ����� IRQ ������� �������������.
*/
return request_irq(1, /* ����� IRQ */
irq_handler, /* ��� ���������� */
SA_SHIRQ,
"test_keyboard_irq_handler",
(void *)(irq_handler));
}
/*
* ���������� ������
*/
void cleanup_module()
{
/*
* ��� ������� ��������� ���� ��� ������� ���������.
* ��� ������ ������������, ��������� � �� ���� �������
* ������������ ����������� ���������� ���������� ��
����������
* ������� ���������� ��������� ������������ �������.
*/
free_irq(1, NULL);
}
/*
* ��������� �������, ����������� � work_queue
* �������� ������ ���� ������ ������������ ��� GPL
*/
MODULE_LICENSE("GPL");