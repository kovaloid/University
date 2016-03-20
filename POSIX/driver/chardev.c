#include <linux/fs.h>
#include <linux/init.h> //определени€ макросов
#include <linux/module.h> //дл€ корректной работы модул€
#include <linux/kernel.h> //дл€ printk() и т.д.
#include <asm/uaccess.h> //put_user(), get_user()
#include "ioctl.h"

#define MY_MODNAME "my_ioctl_dev" //им€ устройства

//задаЄм информацию о модуле, которую можно будет увидеть с помощью modinfo
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Kovalev A.D." );
MODULE_DESCRIPTION( "ioctl char driver" );
MODULE_VERSION( "1.0" );

//глобальные переменные, объ€влены как static, воизбежание конфликтов имен
static char text[BUF_LEN] = "Message passed by ioctl\n"; //буфер
static char *text_ptr; //указатель на текущую позицию в тексте
static char text_delete[BUF_LEN] = "delete\n";
static char text_forward[BUF_LEN] = "direction_forward\n";
static char text_back[BUF_LEN] = "direction_back\n";
static int device_open = 0; //используетс€ ли устройство?
static int direction = 0; //направление вывода текста

//функци€ открыти€ устройства
static int dev_open(struct inode *n, struct file *f) 
{
   text_ptr = text;
   printk(KERN_INFO "=== device open\n");
   if (device_open) return -EBUSY;
   device_open++;
   return 0;
}

//функци€ закрыти€ устройства
static int dev_release(struct inode *n, struct file *f) 
{
   printk(KERN_INFO "=== device release\n");
   device_open--;
   return 0;
}

//функци€ чтени€ из устройства
static ssize_t dev_read(struct file *f, char *buffer, size_t length, loff_t *offset)
{
   int byte_read = 0;
   if ( *text_ptr == 0 ) 
   {
      printk(KERN_INFO "=== empty or end of file\n");
      return 0;
   }
   //разный вывод в зависимости от направлени€ direction
   if (direction == 0)
   {
      while ( length && *text_ptr )
      {
         put_user( *( text_ptr++ ), buffer++ );
         length--;
         byte_read++;
      }
   }
   else if (direction == 1)
   {
      int len = strlen( text );
      text_ptr = &text[len-2];
      while ( length && *text_ptr )
      {
         put_user( *( text_ptr-- ), buffer++ );
         length--;
         byte_read++;
      }
      put_user( '\n', buffer++ );
      byte_read++;
   }
   printk(KERN_INFO "=== bytes read: %d\n", byte_read);
   return byte_read;
}

//функци€ записи в устройство
static ssize_t dev_write(struct file *f, const char *buffer, size_t length, loff_t *offset)
{
   int i;
   char temp[BUF_LEN];
   for (i=0; i<BUF_LEN; i++)
      temp[i] = text[i];
   for (i=0; i<length && i<BUF_LEN; i++)
      get_user(text[i], buffer+i);
   text[i] = '\0';
   text_ptr = text;
   printk(KERN_INFO "=== bytes write: %d\n", (int)length);
   printk(text);
   //сравнение введенного сообщени€ с управл€ющими фразами
   if (strcmp(text, text_delete) == 0)
   {
      printk(KERN_INFO "=== clear buffer\n");
      text[0] = '\0';
   }
   else if (strcmp(text, text_forward) == 0)
   {
      printk(KERN_INFO "=== forward read activate\n");
      direction = 0;
      for (i=0; i<BUF_LEN; i++)
         text[i] = temp[i];
   }
   else if (strcmp(text, text_back) == 0) 
   {
      printk(KERN_INFO "=== backward read activate\n");
      direction = 1;
      for (i=0; i<BUF_LEN; i++)
         text[i] = temp[i];
   }    
   return i;
}

//функци€ записи в устройство использу€ ioctl
static long dev_ioctl_write(const char *arg)
{
   long len;
   len = strlen(arg);
   if (len >= BUF_LEN) 
   {
      printk(KERN_INFO "=== too long string for ioctl\n");
      return -EFAULT;
   }
   text[0] = '\0';
   if (copy_from_user(text, arg, len)) return -EFAULT;
   text[len] = '\0';
   return 0;
}

//функци€ ioctl
static int dev_ioctl(struct file *f, unsigned int cmd, unsigned long arg) 
{
   int i;
   char *temp;
   char ch;

   switch( cmd ) 
   {
      case IOCTL_GET_MSG: //читать
         i = dev_read(f, (char *)arg, 99, 0);
         put_user('\0', (char *)arg + i);
         break;
      case IOCTL_CLR_MSG: //очистить
         text[0] = '\0';
         break;
      case IOCTL_SET_MSG: //записать
         temp = (char *)arg;
         get_user(ch, temp);
         for (i=0; ch && i<BUF_LEN; i++, temp++)
            get_user(ch, temp);
         dev_write(f, (char *)arg, i, 0);
         break;
      case IOCTL_FORWARD_MSG: //пр€мой вывод
         direction = 0;
         break;
      case IOCTL_BACK_MSG: //обратный вывод
         direction = 1;
         break;
      case IOCTL_WRITE_FILE: //записать из файла
         return dev_ioctl_write((char *)arg);
         break;
      default: 
         return -ENOTTY;
   }
   return 0;
}

//обработчики операций над устройством
static const struct file_operations my_fops = {
   .owner = THIS_MODULE,
   .open = dev_open,
   .release = dev_release,
   .read  = dev_read,
   .write  = dev_write,
   .unlocked_ioctl = dev_ioctl
};

//функци€ загрузки модул€, входна€ точка, можно считать что это наш main()
static int __init dev_init( void ) 
{
   //регистрируем устройсво
   int ret = register_chrdev( MY_MAJOR, MY_MODNAME, &my_fops );
   if( ret < 0 )
   {
      printk(KERN_ERR "=== can not register char device\n");
      return ret;
   }
   printk(KERN_INFO "=== register char device\n");
   printk(KERN_INFO "=== major device number: %d.\n", MY_MAJOR);
   printk(KERN_INFO "=== to create dev file: mknod %s c %d 0\n", DEVPATH, MY_MAJOR);
   return 0;
}

//функци€ выгрузки модул€
static void __exit dev_exit( void ) 
{
   //освобождаем устройство
   unregister_chrdev( MY_MAJOR, MY_MODNAME );
   printk(KERN_INFO "=== unregister char device\n");
}

//указываем наши функции загрузки и выгрузки
module_init( dev_init );
module_exit( dev_exit );
