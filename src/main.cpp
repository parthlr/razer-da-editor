#include <iostream>
extern "C" {
    #include "usb.h"
    #include "razer.h"
}

using namespace std;

int main() {
    int context_return = init_usb_context();
    if (context_return < 0) {
        return context_return;
    }

    libusb_device_handle* dev = open_device(USB_VENDOR_ID, USB_PRODUCT_ID);
    if (dev == NULL) {
        return -1;
    }

    // Test set brightness to 21 out of max 255
    razer_set_brightness(dev, 0xA9, 1);

    return 0;
}