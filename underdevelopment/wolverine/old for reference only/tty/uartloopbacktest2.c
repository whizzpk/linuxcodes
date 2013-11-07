/**************************** LOOP BACK TEST APLLICATION :- UART *********************************

This application is designed to do loopback test for UART port . Two of the
following cases are met in this application.

First Case : UART of system sends a string to UART of target board , which will be displayed on
screen thus system acts as a transmitter and target board acts as a receiver.

Second Case : UART of target will transmit again another string which will be collected by UART
of system and displayed on screen. Thus target acting as a transmitter and system acting as a
receiver.

*************************************************************************************************/
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>                                              
//The termios functions describe a general terminal interface that is provided to 
////control
#include <string.h>
//asynchronous communications ports.
#include <unistd.h>
#define BAUD_RATE B115200
int fd;
int uart_init(int fd)
{
int status=0;
struct termios pre_settings;

tcflush(fd , TCIFLUSH);                                   //Flushes data received but not read
tcgetattr(fd, &pre_settings);                             //Get the current options for the port
cfsetispeed(&pre_settings, BAUD_RATE);               //Setting input baud rate
cfsetospeed(&pre_settings, BAUD_RATE);               //Setting output baud rate

pre_settings.c_cflag |= (CLOCAL | CREAD);                 //Enable the receiver and set local mode

pre_settings.c_cflag &= ~PARENB;                          
//No parity
pre_settings.c_cflag &= ~CSTOPB;                          
//One Stop bit
pre_settings.c_cflag &= ~CSIZE;                           
//Character size mask
pre_settings.c_cflag |= CS8;                              
//8 data bits

tcflush(fd, TCOFLUSH);                                   
 //Flushes data written but not transmitted

if (tcsetattr(fd, TCSANOW, &pre_settings)==-1)
{
perror(“On tcsetattr:”);
status = -1;
}
else
status = 1;
return status;
}

void handler_init(int signum)
{
close(fd);
printf(“\nExiting\nDevice Node Closed\n”);
exit(1);
}

int main(int argc, char *argv[])
{
int choice,check;
char buffer[5];
char data[]=”omji”;

struct sigaction sa_init;
memset(&sa_init, 0, sizeof(sa_init));
sa_init.sa_handler = &handler_init;
sigaction (SIGINT, &sa_init, NULL);

if(argc != 2)
{
printf(“usage: ./a.out node-name\n”);
exit(1);
}

//if( fd = open (argv[1], O_RDWR | O_NOCTTY ) < 0 )               
//Getting file descriptor for tty
if( fd = open (argv[1], O_RDWR  ) < 0 )                          
 //Getting file descriptor for tty
{
perror(“tty”);
exit(1);
}
printf(“TTY device opened with file descriptor : %d \n”,fd);

if (uart_init(fd) == -1)
{
printf(“UART Initialisation Error\n”);
close(fd);
exit(1);
}
else
printf(“Initialisations are done\n”);

printf(“Operation to perform:\n     1.Read\n     2.Write\n     0.Exit\nChoice : “);
scanf(“%d”, &choice);
switch(choice)
{
case 1:
while(1)
{
if( (read(fd, &buffer, sizeof(data)) ) < 0)
printf(“Read Failure\n”);
else
printf(“\nRead Success\nREAD STRING : %s \n”, buffer);
sleep(3);
}
break;
case 2:
while(1)
{
if( (write(fd,&data,sizeof(data)) ) < 0)
printf(“Write Failure\n”);
else
printf(“\nWrite Success\n”);
sleep(3);
}
break;
case 0:
close(fd);
printf(“Exiting\n”);
exit(1);
break;
default:
printf(“Wrong choice : Try again !!!!!\n”);
break;
}
}
