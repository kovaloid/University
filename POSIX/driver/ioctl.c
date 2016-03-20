#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "ioctl.h"

//������ ��� �������� ������ ��������� �� �������
#define ERR(...) fprintf( stderr, "\7" __VA_ARGS__ ), exit( EXIT_FAILURE )

//����� ����������� ���������� �� �����
void get_msg(int fd)
{ 
   if(ioctl(fd, IOCTL_GET_MSG, &msg)) 
      ERR("IOCTL_GET_MSG error: %m\n");
   else
   {
      printf("READ: %s", &msg[0]);
      if (*msg == 0) printf("<empty>\n");
   }
}

//������� ������
void clr_msg(int fd)
{
   if (ioctl(fd, IOCTL_CLR_MSG))
      ERR("IOCTL_CLR_MSG error: %m\n");
}

//������ ��������� � ����������
void set_msg(int fd)
{
   int i, len=0;
   char v[BUF_LEN];
   printf("WRITE: ");
   scanf("%s", &v[0]);
   getchar();
   for (i=0; i<BUF_LEN; i++)
   {
      if (v[i] == '\0') break;
      len++;
   }
   for (i=0; i<len ; i++)
      msg[i] = v[i];
   msg[i] = '\n';
   if(ioctl(fd, IOCTL_SET_MSG, &msg)) 
      ERR("IOCTL_SET_MSG error: %m\n");
}

//��������� ������� ����������� ������
void forward_msg(int fd)
{
   if (ioctl(fd, IOCTL_FORWARD_MSG))
      ERR("IOCTL_FORWARD_MSG error: %m\n");
}

//��������� ��������� ����������� ������
void back_msg(int fd)
{
   if (ioctl(fd, IOCTL_BACK_MSG))
      ERR("IOCTL_BACK_MSG error: %m\n");
}

//������ ������ � ���������� �� �����
void write_file(int fd, char *msg_filename)
{
   FILE *msg_file;
   long msg_file_size;
   char *buf;
   msg_file = fopen(msg_filename, "r");
   if (msg_file == NULL) 
   {
      printf("ERROR OPENING FILE\n");
      return;
   }
   fseek(msg_file, 0L, SEEK_END);
   msg_file_size = ftell(msg_file);
   rewind(msg_file);
   buf = malloc(sizeof(char) * (msg_file_size + 1));
   if (!buf)
   {
      fprintf(stderr, "MEMORY ERROR\n");
      fclose(msg_file);
      return;
   }
   //������ �����
   if (fread(buf, msg_file_size, 1, msg_file) != 1)
   {
      fprintf(stderr, "FILE READ ERROR\n");
      free(buf);
      fclose(msg_file);
      return;
   }
   fclose(msg_file);
   if (ioctl(fd, IOCTL_WRITE_FILE, buf))
      ERR("IOCTL_WRITE_FILE error: %m\n");
   free(buf);
   return;
}

//������ ������ �� ���������� � ����
void read_file(int fd, char *msg_filename)
{
   FILE *msg_file;
   long msg_file_size;
   msg_file = fopen(msg_filename, "w");
   if (msg_file == NULL)
   {
      printf("ERROR OPENING FILE\n");
      return;
   }
   if (ioctl(fd, IOCTL_GET_MSG, &msg))
      ERR("IOCTL_GET_MSG error: %m\n");
   msg_file_size = strlen(msg);
   //������ � ����
   if (fwrite(msg, msg_file_size, 1, msg_file) != 1)
      fprintf(stderr, "FILE WRITE ERROR\n");
   fclose(msg_file);
   return;
}

//�������� ����� � ������� ������
void delete_file(int fd, char *msg_filename)
{
   if(remove(msg_filename)) printf("FILE REMOVING ERROR\n");
   if (ioctl(fd, IOCTL_CLR_MSG))
      ERR("IOCTL_CLR_MSG error: %m\n");
}

int main(int argc, char *argv[]) 
{
   int fd; //�������� ���������� ����������
   char *msg_filename; //�������� ����� ��� ������\������
   enum {e_get, e_clr, e_set, e_forward, e_back, e_write, e_read, e_delete} option;

   //����������� ���������� �������� � ��������� ������ �� ./ioctl
   if (argc == 1) option = e_get;
   else if (argc == 2)
   {
      if (strcmp(argv[1], "-g") == 0) option = e_get;
      else if (strcmp(argv[1], "-c") == 0) option = e_clr;
      else if (strcmp(argv[1], "-s") == 0) option = e_set;
      else if (strcmp(argv[1], "-f") == 0) option = e_forward;
      else if (strcmp(argv[1], "-b") == 0) option = e_back;
      else
      {
         fprintf(stderr, "Use: %s [-g | -c | -s | -f | -b ]\n", argv[0]);
         return 1;
      }
   }
   else if (argc == 3)
   {
      if (strcmp(argv[1], "-w") == 0) 
      {
         option = e_write;
         msg_filename = argv[2];
      }
      else if (strcmp(argv[1], "-r") == 0) 
      {
         option = e_read;
         msg_filename = argv[2];
      }
      else if (strcmp(argv[1], "-d") == 0) 
      {
         option = e_delete;
         msg_filename = argv[2];
      }
      else
      {
         fprintf(stderr, "Use: %s [-w <file> | -r <file> | -d <file>]\n", argv[0]);
         return 1;
      }
   }
   else
   {
      fprintf(stderr, "Use: %s [-g | -c | -s | -f | -b | -w <f> | -r <f> | -d <f>]\n", argv[0]);
      return 1;
   }
     
   if((fd = open(DEVPATH, O_RDWR)) < 0)
      ERR("Open device error: %m\n");

   //� ����������� �� ��������� ��������� ����������� ��������������� �������
   switch (option)
   {
      case e_get: 
         get_msg(fd);
         break;
      case e_clr:
         clr_msg(fd);
         break;
      case e_set:
         set_msg(fd);
         break;
      case e_forward:
         forward_msg(fd);
         break;
      case e_back:
         back_msg(fd);
         break;
      case e_write:
         write_file(fd, msg_filename);
         break;
      case e_read:
         read_file(fd, msg_filename);
         break;
      case e_delete:
         delete_file(fd, msg_filename);
         break;
      default:
         break;
   }

   close(fd);
   return EXIT_SUCCESS;
}
