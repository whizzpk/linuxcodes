#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "test passed!\n";
        char    readbuffer[80];
	fd_set set;
  	struct timeval timeout;
  	int rv;

        pipe(fd);
        
        //test writing side of fd with other pipe
        
        

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
            fd[1]=open("/dev/ttyS2",O_WRONLY);   
        if(fd[1]<0)
        {
            printf("the device is not opened\n");
            exit(-1);
        }   
                /* Send "string" through the output side of pipe */
                int i=write(fd[1], string, (strlen(string)+1));
                if(i<0) printf("test failed");
                exit(0);
        }
        else
        {

                /* Parent process closes up output side of pipe */
                close(fd[1]);
        fd[0]=open("/dev/ttyS2",O_RDONLY);
        if(fd[0]<0)
        {
            printf("the device is not opened\n");
            exit(-1);
        }
                /* Read in a string from the pipe */
                /*
                
                
				FD_ZERO(&set); /* clear the set */
		  FD_SET(fd[0], &set); /* add our file descriptor to the set */

		  timeout.tv_sec = 2;
		  timeout.tv_usec = 10000;

		  rv = select(fd[0] + 1, &set, NULL, NULL, &timeout);
		  if(rv == -1)
		    perror("select"); /* an error accured */
		  else if(rv == 0)
		    printf("test failed"); /* a timeout occured */
		  else{
                
                
                size_t count1=0;
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                size_t count2=sizeof(readbuffer);
                if(count2==count1 || nbytes<0) printf("test failed 2");
                else
                printf(" Received string: %s", readbuffer);}
        }

        return(0);
}
