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

static void print_devs(libusb_device **devs);
int compare(void);
static void i2ctest(void);
static int set_i2c_register(int file,
                            unsigned char addr,
                            unsigned char reg,
                            unsigned char value);
static int set_i2c_register(int file,
                            unsigned char addr,
                            unsigned char reg,
                            unsigned char value);

int main(void)
{
	printf("starting tests2");
	//pointer to 2d array of devices
        libusb_device **devs;
        int r;
        ssize_t cnt;
	//writting to pointer to 2d array of devices
        r = libusb_init(NULL);
        if (r < 0){
        printf("starting line17");
                return r;}
        cnt = libusb_get_device_list(NULL, &devs);
        if (cnt < 0){
        printf("starting line21");
                return (int) cnt;}
        print_devs(devs);
        libusb_free_device_list(devs, 1);
        libusb_exit(NULL);
        int check=compare();
        return 0;
}
int compare(void){
    FILE *fp1, *fp2;
    int ch1, ch2;
    char fname1[40], fname2[40] ;

    //printf("Enter name of first file :") ;
    //gets(fname1);

    //printf("Enter name of second file:");
    //gets(fname2);

    fp1 = fopen( "results.dat",  "r" );
    fp2 = fopen( "results.dat",  "r" ) ;

    if ( fp1 == NULL )
       {
       printf("Cannot open %s for reading ", fname1 );
       exit(1);
       }
    else if (fp2 == NULL)
       {
       printf("Cannot open %s for reading ", fname2 );
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

        if (ch1 == ch2)
            printf("PAss \n");
        else if (ch1 !=  ch2)
            printf("Fail \n");

        fclose ( fp1 );
        fclose ( fp2 );
       }
return(0);
}
static void print_devs(libusb_device **devs)
{ 
    	FILE *fp;
	//traversing first then indexing
        libusb_device *dev;
        int i = 0;
        while ((dev = devs[i++]) != NULL) {
		//keeping time complexity to the minimum
                struct libusb_device_descriptor desc;
                int r = libusb_get_device_descriptor(dev, &desc);
                if (r < 0) {
                        fprintf(stderr, "failed to get device descriptor");
                        return;
                }
                fp = fopen("results.dat", "a");
      		if (fp == NULL) {
         	printf("I couldn't open results.dat for writing.\n");
         	exit(0);
   		}
                 printf("%04x:%04x (bus %d, device %d)\n",
                        desc.idVendor, desc.idProduct,
                        libusb_get_bus_number(dev), libusb_get_device_address(dev));
                 fprintf(fp,"%04x:%04x (bus %d, device %d)\n",
                        desc.idVendor, desc.idProduct,
                        libusb_get_bus_number(dev), libusb_get_device_address(dev));
                       
        }
        fclose ( fp );
}

static void i2ctest(void){
  int i2c_file;
 if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
        perror("Unable to open i2c control file");
        exit(1);
    }

  
    FILE *fp;
    fp = fopen("results.dat", "a");
      		if (fp == NULL) {
         	printf("I couldn't open results.dat for writing.\n");
         	exit(0);
   		}
	 int addr = strtol("hardcodedvalue", NULL, 0);
        int reg = strtol("hardcoded", NULL, 0);
        unsigned char value;
        if(get_i2c_register(i2c_file, addr, reg, &value)) {
            printf("Unable to get register!\n");
        }
        else {
             fprintf(fp,"Register %d: %d (%x)\n", reg, (int)value, (int)value);
        }
    	if(set_i2c_register(i2c_file, addr, reg, value)) {
            printf("Unable to get register!\n");
        }
        else {
           fprintf(fp,"Set register %x: %d (%x)\n", reg, value, value);
        }
    // I2c_FILE_NAME used to open connection to i2c user space ctl file
   
  } 
  
  static int get_i2c_register(int file,
                            unsigned char addr,
                            unsigned char reg,
                            unsigned char *val) {
    unsigned char inbuf, outbuf;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    /* read write to regidter , first dummy data is written*/
    outbuf = reg;
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(outbuf);
    messages[0].buf   = &outbuf;

    /* data getting returned in this structure */
    messages[1].addr  = addr;
    messages[1].flags = I2C_M_RD/* | I2C_M_NOSTART*/;
    messages[1].len   = sizeof(inbuf);
    messages[1].buf   = &inbuf;

    /* Sending the request to kernel and getting back the result  */
    packets.msgs      = messages;
    packets.nmsgs     = 2;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("Unable to send data");
        return 1;
    }
    *val = inbuf;

    return 0;
}

static int set_i2c_register(int file,
                            unsigned char addr,
                            unsigned char reg,
                            unsigned char value) {

    unsigned char outbuf[2];
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(outbuf);
    messages[0].buf   = outbuf;

    /* The first byte indicates which register we'll write */
    outbuf[0] = reg;

    /* 
     * The second byte indicates the value to write.  Note that for many
     * devices, we can write multiple, sequential registers at once by
     * simply making outbuf bigger.
     */
    outbuf[1] = value;

    /* Transfer the i2c packets to the kernel and verify it worked */
    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("Unable to send data");
        return 1;
    }

    return 0;
}

