#ifndef USB_H
#define USB_H

#include <libusb.h>

#define USB_VENDOR_ID 0x1532
#define USB_PRODUCT_ID 0x0098

int init_usb_context();
libusb_device_handle* open_device(uint16_t vendor_id, uint16_t product_id);
void print_devs(libusb_device** devs);
libusb_device* find_device(libusb_device** devices, uint16_t vendor, uint16_t product);

#endif