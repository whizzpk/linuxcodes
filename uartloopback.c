/*
 * uart-loopback.c - userspace uart loopback test
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <termios.h>
#include <sys/ioctl.h>


void print_usage(char *prg)
{
	fprintf(stderr, "\nUsage: %s [options] tty\n\n", prg);
	fprintf(stderr, "Options: -b <baud>  (uart baud rate)\n");
	fprintf(stderr, "Options: -c <count>  (ascii count)\n");
	fprintf(stderr, "         -?         (show this help)\n");
	fprintf(stderr, "\nExample:\n");
	fprintf(stderr, "uart-loopback /dev/ttyS1\n");
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char **argv)
{
	fd_set readfs;    /* file descriptor set */
        struct timeval Timeout;
	int fd,ret;
	char *tty;
	char j[2];
	char *btr = NULL;
	int opt,count=127;
	char i;

	while ((opt = getopt(argc, argv, "bc:?")) != -1) {
		switch (opt) {
		case 'b':
			btr = optarg;
			printf("baud=%s\n",btr);
			break;

		case 'c':
			count = atoi(optarg);
			break;

		case '?':
		default:
			print_usage(argv[0]);
			break;
		}
	}
    
                                                                
	if (argc - optind != 1)
		print_usage(argv[0]);

	tty = argv[optind];

	printf("count=%d\n",count);

	printf("uart port used: %s\n",tty);
	
	if ((fd = open (tty, O_RDWR | O_NOCTTY)) < 0) {
		perror(tty);
		exit(1);
	}

	tcflush(fd, TCIFLUSH);
 
	for (i=33; i < count+33; i++) {
	    ret=write(fd,&i, 1);
	    if (ret != 1) {
		printf("write error!\n");
		exit(1);
	    }

	    FD_SET(fd, &readfs);  /* set testing source */

    	    /* set timeout value within input loop */
    	    Timeout.tv_usec = 0;  /* milliseconds */
    	    Timeout.tv_sec  = 10;  /* seconds */
    	    ret = select(fd+1, &readfs, NULL, NULL, &Timeout);
            if (ret==0){
		printf("read timeout error!\n");
		exit(1);
	    }
	    else
		ret=read(fd, &j, 1);

	    if (ret!=1) {
		printf("read error!\n");
		exit(1);
	    }

	    if ( i!=j[0] ) {
		printf("read data error: wrote 0x%x read 0x%x\n",i,j[0]);
		exit(1);
	    }

	    printf("%c",j[0]);

	}

	printf("\n");

	close(fd);

	return 0;
}
