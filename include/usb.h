#include <libusb.h>

void print_devs(libusb_device** devs);
libusb_device* find_device(libusb_device** devices, uint16_t vendor, uint16_t product);