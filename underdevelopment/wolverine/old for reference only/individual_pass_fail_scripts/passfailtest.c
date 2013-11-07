#include <stdio.h>
#include <sys/types.h>
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>


int compare(char *);

int main(int argc, char *argv[])
{
	
        int check=compare(argv[1]);
        return 0;
}
int compare(char* fn){
    FILE *fp1, *fp2;
    int ch1, ch2;
    char fname1[40], fname2[40] ;
 
    //printf("Enter name of first file :") ;
    //gets(fname1);

    //printf("Enter name of second file:");
    //gets(fname2);

    fp1 = fopen( "results.dat",  "r" );
    fp2 = fopen( fn,  "r" );

    if ( fp1 == NULL )
       {
       printf("Cannot open %s for reading ", fname1 );
       exit(1);
       }
    else if (fp2 == NULL)
       {
       printf("Control file not available  %s for reading ", fn );
       exit(1);
       }
    else
       {
       ch1  =  getc( fp1 ) ;
       ch2  =  getc( fp2 ) ;

       while( (ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2))
        {
            ch1 = getc(fp1);
            ch2 = getc(fp2) ;
        }

        if (ch1 == ch2){
            printf("Tests Passed \n");
            printf("---8<---results below-----8<------------8<---- \n");}
        else if (ch1 !=  ch2)
            printf("Fail \n");

        fclose ( fp1 );
        fclose ( fp2 );
       }
return(0);
}

