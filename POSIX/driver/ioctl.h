#include <linux/ioctl.h>

#define BUF_LEN 160 //размер буфера
#define MY_MAJOR 200 //старший номер моего устройства
#define DEVPATH "/dev/ioctl" //файл устройства

   char msg[BUF_LEN]; //вспомогательный массив

//макросы ioctl используемые в драйвере
#define IOCTL_GET_MSG _IOR( MY_MAJOR, 1, char *)
#define IOCTL_CLR_MSG _IO( MY_MAJOR, 2 )
#define IOCTL_SET_MSG _IOW( MY_MAJOR, 3, char *)
#define IOCTL_FORWARD_MSG _IO( MY_MAJOR, 4 )
#define IOCTL_BACK_MSG _IO( MY_MAJOR, 5 )
#define IOCTL_WRITE_FILE _IOW( MY_MAJOR, 6, char * )








