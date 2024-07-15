#include <iostream>
extern "C" {
    #include "usb.h"
    #include "razer.h"
}

using namespace std;

int main() {
    int r;

    r = libusb_init_context(/*ctx=*/NULL, /*options=*/NULL, /*num_options=*/0);
    if (r < 0)
        return r;

    libusb_device_handle* dev = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    if (dev == NULL) {
        std::cout << "Device not found" << std::endl;
    }
    else {
        std::cout << "Device found" << std::endl;
    }

    // Test set brightness to 21 out of max 255
    razer_set_brightness(dev, 0x15, 1);

    return 0;
}