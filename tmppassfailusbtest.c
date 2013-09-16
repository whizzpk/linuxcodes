#include <stdio.h>
#include <sys/types.h>
#include <libusb-1.0/libusb.h>
static void print_devs(libusb_device **devs);

int main(void)
{
	//pointer to 2d array of devices
        libusb_device **devs;
        int r;
        ssize_t cnt;
	//writting to pointer to 2d array of devices
        r = libusb_init(NULL);
        if (r < 0){
         fprintf(stderr, "failed to get device descriptor");
                return r;}
        cnt = libusb_get_device_list(NULL, &devs);
        if (cnt < 0)
                return (int) cnt;
        print_devs(devs);
        libusb_free_device_list(devs, 1);
        libusb_exit(NULL);
        return 0;
}
static void print_devs(libusb_device **devs)
{
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
                printf("%04x:%04x (bus %d, device %d)\n",
                        desc.idVendor, desc.idProduct,
                        libusb_get_bus_number(dev), libusb_get_device_address(dev));
        }
       
}
