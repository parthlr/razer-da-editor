#include <iostream>
#include <QApplication>
#include "gui.h"

extern "C" {
    #include "usbutil.h"
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int contextVal = init_usb_context();
    if (contextVal < 0) {
        std::cout << "Failed to initialize USB context" << std::endl;
        return -1;
    }

    libusb_device_handle* device = open_device(USB_VENDOR_ID, USB_PRODUCT_ID);
    if (device == NULL) {
        std::cout << "Failed to open device with vendor ID " << USB_VENDOR_ID << "and product ID" << USB_PRODUCT_ID << std::endl;
        return -1;
    }

    gui window(device);
    window.setMinimumWidth(500);
    window.show();

    return app.exec();
}