#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

int main(){
    int fd;
    struct termios options;
 
    /* open the port */
    fd = open("/dev/ttyUSB2", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	   {                                              /* Could not open the port */
	     fprintf(stderr, "open_port: Unable to open /dev/ttyUSB0 - %s\n",strerror(errno));
	   }else{
		printf("port opened\n");
	    }
    fcntl(fd, F_SETFL, 0);
 
    /* get the current options */
    tcgetattr(fd, &options);
 
    /* set raw input, 1 second timeout */
    options.c_cflag     |= (CLOCAL | CREAD);
    options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag     &= ~OPOST;
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 10;
 
    /* set the options */
    tcsetattr(fd, TCSANOW, &options);
 
	char buffer[400];  /* Input buffer */
      char *bufptr;      /* Current char in buffer */
      int  nbytes;       /* Number of bytes read */
      int  tries;        /* Number of tries so far */
 
      for (tries = 0; tries < 1; tries ++)
      {
       /* send an AT command*/
	if (write(fd, "AT\r", strlen("AT\r")) < 3){
		printf("command sent\n");
	  continue;
	}
 
       /* read characters into our string buffer*/
	bufptr = buffer;
 
	nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1);
	printf("%s\n",bufptr);
	
 
    char *p;
 	p = strstr(bufptr, "OK");
 	if(p != NULL) printf("SIM CARD TEST PASS\n"); else printf("SIM CARD TEST FAIL\n");
    p = strstr(buffer, "tin");
    printf("%s",p);
 
	p = strstr(buffer, "server");
	if(p == NULL) printf("not from server\n");
 
	*bufptr = '\0';
 
}
	return 0;
}
 
