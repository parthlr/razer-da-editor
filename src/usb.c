#include "usb.h"
#include <libusb.h>
#include <stdint.h>
#include <cstdio>

void print_devs(libusb_device** devs) {
	libusb_device* dev;
	int i = 0, j = 0;
	uint8_t path[8];

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "Failed to get device descriptor");
			return;
		}

		printf("%04x:%04x (bus %d, device %d)",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++)
				printf(".%d", path[j]);
		}
		printf("\n");
	}
}

libusb_device* find_device(libusb_device** devices, uint16_t vendor, uint16_t product) {
	libusb_device* device;
	int i = 0;

	while ((device = devices[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor(device, &desc) < 0) {
			printf("Failed to open device descriptor\n");
			return NULL;
		}

		if (desc.idVendor == vendor && desc.idProduct == product) {
			printf("Found device\n");
			return device;
		}
	}

	printf("Device not found\n");
	return NULL;
}