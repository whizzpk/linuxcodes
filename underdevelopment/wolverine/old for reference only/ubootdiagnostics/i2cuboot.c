#include <common.h>
#include <i2c.h>
#include <command.h>
#include <asm/io.h>
#ifdef CONFIG_HARD_I2C
#include <i2c.h>
#include <asm/i2c.h>
#ifdef CONFIG_MPC8349ADS
i2c_t * mpc8349_i2c = (i2c_t*)(CFG_IMMRBAR + CFG_I2C_OFFSET);
#endif
int main(){


//initilaize bus
void send_star();


//probe for device to initialize it

i2c_init(int speed, int slaveadd);


//list i2c devices on u boot level



return 0;
}







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

void
i2c_init(int speed, int slaveadd)
{
	/* stop I2C controller */
	writeb(0x00 , &I2C->cr);

	/* set clock */
	writeb(0x3f, &I2C->fdr);

	/* set default filter */
	writeb(0x10,&I2C->dfsrr);

	/* write slave address */
	writeb(slaveadd, &I2C->adr);

	/* clear status register */
	writeb(0x00, &I2C->sr);

	/* start I2C controller */
	writeb(I2C_CR_MEN, &I2C->cr);
}

static __inline__ int
i2c_wait4bus (void)
{
	ulong timeval = get_timer (0);
	while (readb(&I2C->sr) & I2C_SR_MBB) {
		if (get_timer (timeval) > I2C_TIMEOUT) {
			return -1;
		}
	}
	return 0;
}

static __inline__ int
i2c_wait (int write)
{
	u32 csr;
	ulong timeval = get_timer(0);
	do {
		csr = readb(&I2C->sr);

		if (!(csr & I2C_SR_MIF))
			continue;

		writeb(0x0, &I2C->sr);

		if (csr & I2C_SR_MAL) {
			debug("i2c_wait: MAL\n");
			return -1;
		}

		if (!(csr & I2C_SR_MCF))	{
			debug("i2c_wait: unfinished\n");
			return -1;
		}

		if (write == I2C_WRITE && (csr & I2C_SR_RXAK)) {
			debug("i2c_wait: No RXACK\n");
			return -1;
		}

		return 0;
	} while (get_timer (timeval) < I2C_TIMEOUT);
	debug("i2c_wait: timed out\n");
}

static __inline__ int
i2c_write_addr (u8 dev, u8 dir, int rsta)
{
	writeb(I2C_CR_MEN | I2C_CR_MSTA | I2C_CR_MTX |
	       (rsta?I2C_CR_RSTA:0),
	       &I2C->cr);

	writeb((dev << 1) | dir, &I2C->dr);

	if (i2c_wait (I2C_WRITE) < 0)
		return 0;
	return 1;
}

static __inline__ int
__i2c_write (u8 *data, int length)
{
	int i;

	writeb(I2C_CR_MEN | I2C_CR_MSTA | I2C_CR_MTX,
	       &I2C->cr);

	for (i=0; i < length; i++) {
		writeb(data[i], &I2C->dr);

		if (i2c_wait (I2C_WRITE) < 0)
			break;
	}
	return i;
}

static __inline__ int
__i2c_read (u8 *data, int length)
{
	int i;

	writeb(I2C_CR_MEN | I2C_CR_MSTA |
	       ((length == 1) ? I2C_CR_TXAK : 0),
	       &I2C->cr);

	/* dummy read */
	readb(&I2C->dr);

	for (i=0; i < length; i++) {
		if (i2c_wait (I2C_READ) < 0)
			break;

		/* Generate ack on last next to last byte */
		if (i == length - 2)
			writeb(I2C_CR_MEN | I2C_CR_MSTA |
			       I2C_CR_TXAK,
			       &I2C->cr);

		/* Generate stop on last byte */
		if (i == length - 1)
			writeb(I2C_CR_MEN | I2C_CR_TXAK, &I2C->cr);

		data[i] = readb(&I2C->dr);
	}
	return i;
}

int
i2c_read (u8 dev, uint addr, int alen, u8 *data, int length)
{
	int i = 0;
	u8 *a = (u8*)&addr;

	if (i2c_wait4bus () < 0)
		goto exit;

	if (i2c_write_addr (dev, I2C_WRITE, 0) == 0)
		goto exit;

	if (__i2c_write (&a[4 - alen], alen) != alen)
		goto exit;

	if (i2c_write_addr (dev, I2C_READ, 1) == 0)
		goto exit;

	i = __i2c_read (data, length);

 exit:
	writeb(I2C_CR_MEN, &I2C->cr);
	return !(i == length);
}

int
i2c_write (u8 dev, uint addr, int alen, u8 *data, int length)
{
	int i = 0;
	u8 *a = (u8*)&addr;

	if (i2c_wait4bus () < 0)
		goto exit;

	if (i2c_write_addr (dev, I2C_WRITE, 0) == 0)
		goto exit;

	if (__i2c_write (&a[4 - alen], alen) != alen)
		goto exit;

	i = __i2c_write (data, length);

 exit:
	writeb(I2C_CR_MEN, &I2C->cr);
	return !(i == length);
}

int i2c_probe (uchar chip)
{
	int tmp;

	/*
	 * Try to read the first location of the chip.  The underlying
	 * driver doesn't appear to support sending just the chip address
	 * and looking for an <ACK> back.
	 */
	udelay(10000);
	return i2c_read (chip, 0, 1, (char *)&tmp, 1);
}

uchar i2c_reg_read (uchar i2c_addr, uchar reg)
{
	char buf[1];

	i2c_read (i2c_addr, reg, 1, buf, 1);

	return (buf[0]);
}

void i2c_reg_write (uchar i2c_addr, uchar reg, uchar val)
{
	i2c_write (i2c_addr, reg, 1, &val, 1);
}

#endif /* CONFIG_HARD_I2C */


int main(int argc, char **argv) {
    int i2c_file;

    
    // I2c_FILE_NAME used to open connection to i2c user space ctl file
    if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
        perror("Unable to open i2c control file");
        exit(1);
    }


    if(argc > 3 && !strcmp(argv[1], "r")) {
        int addr = strtol(argv[2], NULL, 0);
        //
        char * ubootaddr=argv[2];
        //
        int reg = strtol(argv[3], NULL, 0);
        //
        char * ubootreg = argv[3];
        //
        unsigned char value;
        //
        i2c_reg_read (ubootaddr, ubbotreg);
        //
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
