#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
// The specific GPIO being used must be setup and replaced thru
// this code.  The GPIO of 0 is in the path of most the sys dirs
// and in the export write.
//
// Figuring out the exact GPIO was not totally obvious when there
// were multiple GPIOs in the system. One way to do is to go into
// the gpiochips in /sys/class/gpio and view the label as it should
// reflect the address of the GPIO in the system. The name of the
// the chip appears to be the 1st GPIO of the controller.
//
// The export causes the gpio0 dir to appear in /sys/class/gpio.
// Then the direction and value can be changed by writing to them.
 
// The performance of this is pretty good, using a nfs mount,
// running on open source linux, on the ML507 reference system,
// the GPIO can be toggled about every 4 usec.
 
// The following commands from the console setup the GPIO to be
// exported, set the direction of it to an output and write a 1
// to the GPIO.
//
// bash> echo 0 > /sys/class/gpio/export
// bash> echo out > /sys/class/gpio/gpio0/direction
// bash> echo 1 > /sys/class/gpio/gpio0/value
 
// if sysfs is not mounted on your system, the you need to mount it
// bash> mount -t sysfs sysfs /sys
 
// the following bash script to toggle the gpio is also handy for
// testing
//
// while [ 1 ]; do
//  echo 1 > /sys/class/gpio/gpio0/value
//  echo 0 > /sys/class/gpio/gpio0/value
// done
 
// to compile this, use the following command
// gcc gpio.c -o gpio
 
// The kernel needs the following configuration to make this work.
//
// CONFIG_GPIO_SYSFS=y
// CONFIG_SYSFS=y
// CONFIG_EXPERIMENTAL=y
// CONFIG_GPIO_XILINX=y
                                                
int main()
{
    int valuefd, exportfd, directionfd;
    printf("GPIO test running...\n"); 
    // The GPIO has to be exported to be able to see it
    // in sysfs 
    exportfd = open("/proc/cns3xxx/gpio", O_WRONLY);
    if (exportfd < 0)
    {
        printf("Cannot open GPIO to export it\n");
        exit(1);
    }
    write(exportfd, "direct output 10 1", 20);
    write(exportfd, "set value 10 1", 15);
    write(exportfd, "direct output 11 1", 20);
    write(exportfd, "set value 11 1", 15);
    write(exportfd, "direct output 10 0", 20);
    write(exportfd, "set value 10 0", 15);
    close(exportfd);
    printf("GPIO successfully set\n");    
}
