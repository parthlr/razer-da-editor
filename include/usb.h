#include <libusb.h>

#define USB_VENDOR_ID 0x1532
#define USB_PRODUCT_ID 0x0098

void print_devs(libusb_device** devs);
libusb_device* find_device(libusb_device** devices, uint16_t vendor, uint16_t product);