#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

void *print_message_function( void *ptr );
void * writethread(void *ptr);
void * readthread(void *ptr);
int open_port(char str[]);
int open_port2(char str[]);
main()
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */
     
     iret1 = pthread_create( &thread1, NULL, readthread, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, writethread, (void*) message2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}


int open_port(char str[])
{
    int fd = open(str, O_RDWR | O_NOCTTY | O_NONBLOCK); // ?? NDELAY or NONBLOCK?

  if (fd == -1)
  {
                    perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
                    fcntl(fd, F_SETFL, 0);

      struct termios options;
      tcgetattr(fd, &options); //this gets the current options set for the port

      // setting the options

      cfsetispeed(&options, B38400); //input baudrate
      cfsetospeed(&options, B38400); // output baudrate
      options.c_cflag |= (CLOCAL | CREAD); // ?? enable receicer and set local mode
      //options.c_cflag &= ~CSIZE; /* mask the character size bits */
      options.c_cflag |= CS8;    /* select 8 data bits */
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // choosing raw input
      options.c_iflag &= ~INPCK; // disable parity check
      options.c_iflag &= ~(IXON | IXOFF | IXANY); // disable software flow control
      options.c_oflag |= OPOST; // ?? choosing processed output
      options.c_cc[VMIN] = 0; // Wait until x bytes read (blocks!)
      options.c_cc[VTIME] = 0; // Wait x * 0.1s for input (unblocks!)

      // settings for no parity bit
      options.c_cflag &= ~PARENB;
      options.c_cflag &= ~CSTOPB;
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;

      tcsetattr(fd, TCSANOW, &options); /*set the new options  TCSANOW specifies all //option changes to occur immediately*/

  return (fd);
}

int open_port2(char str[])
{
    int fd = open(str, O_RDWR | O_NOCTTY | O_NONBLOCK ); // ?? NDELAY or NONBLOCK?

  if (fd == -1)
  {
        perror("open_port: Unable to open /dev/ttyS2 - ");
  }
  else
        fcntl(fd, F_SETFL, 0);

  struct termios options;
  tcgetattr(fd, &options); //this gets the current options set for the port

  // setting the options

  cfsetispeed(&options, B38400); //input baudrate
  cfsetospeed(&options, B38400); // output baudrate
  options.c_cflag |= (CLOCAL | CREAD); // ?? enable receicer and set local mode
  //options.c_cflag &= ~CSIZE; /* mask the character size bits */
  options.c_cflag |= CS8;    /* select 8 data bits */
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // choosing raw input
  options.c_iflag &= ~INPCK; // disable parity check
  options.c_iflag &= ~(IXON | IXOFF | IXANY); // disable software flow control
  options.c_oflag |= OPOST; // ?? choosing processed output
  options.c_cc[VMIN] = 0; // Wait until x bytes read (blocks!)
  options.c_cc[VTIME] = 0; // Wait x * 0.1s for input (unblocks!)

  // settings for no parity bit
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  tcsetattr(fd, TCSANOW, &options); //set the new options ... TCSANOW specifies all option changes to occur immediately

  return (fd);
}

void * writethread(void *ptr){
            //writing
            int writeport = open_port("/dev/ttyS0");

            char str[] = "hellow how are u \n";
            int n;
        
             n = write(writeport, str, strlen(str));
            if (n < 0)
                    fputs("write() of bytes failed!\n", stderr);
	    
            //closing ports
           // close(writeport);
            
            }
            
void * readthread(void *ptr){
    //reading   
    int readport = open_port2("/dev/ttyS2");

    //trying to read one character at a time
    char buff;
   
    int n = 1;

   while (n > 0)
   {
    n = read(readport, &buff, 1);
    printf("%c", buff, buff);
   
   }
   

    printf("\n");

    //closing ports
    //close(readport);
}
          
