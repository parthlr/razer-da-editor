#include <iostream>
#include "usb.h"

using namespace std;

int main() {
    int r;

    r = libusb_init_context(/*ctx=*/NULL, /*options=*/NULL, /*num_options=*/0);
    if (r < 0)
        return r;

    libusb_device_handle* dev = libusb_open_device_with_vid_pid(NULL, 0x1532, 0x0098);
    if (dev == NULL) {
        std::cout << "Device not found" << std::endl;
    }
    else {
        std::cout << "Device found" << std::endl;
    }

    return 0;
}