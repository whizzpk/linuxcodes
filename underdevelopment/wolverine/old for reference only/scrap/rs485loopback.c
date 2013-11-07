#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>

#define UART_SPEED B115200

char buf[512];

void init_serial (int fd)
{
    struct termios termios;
    int res;

    res = tcgetattr (fd, &termios);
    if (res < 0) {
        fprintf (stderr, "Termios get error: %s\n", strerror (errno));
        exit (-1);
    }

    cfsetispeed (&termios, UART_SPEED);
    cfsetospeed (&termios, UART_SPEED);

    termios.c_iflag &= ~(IGNPAR | IXON | IXOFF);
    termios.c_iflag |= IGNPAR;

    termios.c_cflag &= ~(CSIZE | PARENB | CSTOPB | CREAD | CLOCAL);
    termios.c_cflag |= CS8;
    termios.c_cflag |= CREAD;
    termios.c_cflag |= CLOCAL;

    termios.c_lflag &= ~(ICANON | ECHO);
    termios.c_cc[VMIN] = 1;
    termios.c_cc[VTIME] = 0;

    res = tcsetattr (fd, TCSANOW, &termios);
    if (res < 0) {
        fprintf (stderr, "Termios set error: %s\n", strerror (errno));
        exit (-1);
    }
}

int main (int argc, char **argv)
{
    int fd,fi;
    int res;
    int i;

    if (argc < 2) {
        fprintf (stderr, "Please enter device name\n");
        return -1;
    }

    fd = open (argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        fprintf (stderr, "Cannot open %s: %s\n", argv[1], strerror(errno));
        return -1;
    }

    init_serial (fd);
    
    res = write (fd, "P=21\r\n", 7);
    if (res < 0) {
        fprintf (stderr, "Write error: %s\n", strerror(errno));
        return -1;
    }
    tcdrain (fd);
    
   if(tcflush(fd, TCIOFLUSH)==0)printf("%s\n","flush successful");

    res = read (fd, buf, 512);
    
    printf ("%d\n", fd);
    if (res < 0) {
        fprintf (stderr, "Read error: %s\n", strerror(errno));
        return -1;
    }
    
    

    for (i=0; i<res; i++) {
        printf ("%c", buf[i]);
    }
    
    for (i=0; i<512; i++) {
       buf[i]=0;
    }

    return 0;
}
