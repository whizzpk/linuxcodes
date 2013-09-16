
#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>

#define I2C_FILE_NAME "/dev/i2c-0"
#define USAGE_MESSAGE \
    "Usage:\n" \
    "  %s r [addr] [register]   " \
        "to read value from [register]\n" \
    "  %s w [addr] [register] [value]   " \
        "to write a value [value] to register [register]\n" \
    ""



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

int main(int argc, char **argv) {
    int i2c_file;
    FILE *fp;
	 int addr = strtol("hardcodedvalue", NULL, 0);
        int reg = strtol("hardcoded", NULL, 0);
        unsigned char value;
        if(get_i2c_register(i2c_file, addr, reg, &value)) {
            printf("Unable to get register!\n");
        }
        else {
             fprintf(fp,"Register %d: %d (%x)\n", reg, (int)value, (int)value);
        }
    
    // I2c_FILE_NAME used to open connection to i2c user space ctl file
    if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
        perror("Unable to open i2c control file");
        exit(1);
    }

    
    if(argc > 3 && !strcmp(argv[1], "r")) {
        int addr = strtol(argv[2], NULL, 0);
        int reg = strtol(argv[3], NULL, 0);
        unsigned char value;
        if(get_i2c_register(i2c_file, addr, reg, &value)) {
            printf("Unable to get register!\n");
        }
        else {
            printf("Register %d: %d (%x)\n", reg, (int)value, (int)value);
        }
    }
    else if(argc > 4 && !strcmp(argv[1], "w")) {
        int addr = strtol(argv[2], NULL, 0);
        int reg = strtol(argv[3], NULL, 0);
        int value = strtol(argv[4], NULL, 0);
        if(set_i2c_register(i2c_file, addr, reg, value)) {
            printf("Unable to get register!\n");
        }
        else {
            printf("Set register %x: %d (%x)\n", reg, value, value);
        }
    }
    else {
        fprintf(stderr, USAGE_MESSAGE, argv[0], argv[0]);
    }


    close(i2c_file);


    return 0;
	/*lovely generic i2c utiltiy*/
}
