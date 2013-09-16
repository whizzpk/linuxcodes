#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int main()
{
    //reading   
    int readport = open_port("/dev/ttyS0");

    //trying to read one character at a time
    char buff;
   
    int n = 1;
while(1){
   while (n > 0)
   {
    n = read(readport, &buff, 1);
    printf("%c", buff, buff);
   
   }
}
    printf("\n");

    //closing ports
    close(readport);
}

int open_port(char str[])
{
    int fd = open(str, O_RDWR | O_NOCTTY); // ?? NDELAY or NONBLOCK?

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

  tcsetattr(fd, TCSANOW, &options); //set the new options ... TCSANOW specifies all option changes to occur immediately

  return (fd);
}
