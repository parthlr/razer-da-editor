#include <iostream>
#include <QApplication>
#include "gui.h"

extern "C" {
    #include "usb.h"
    #include "razer.h"
}

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    gui window;
    window.setMinimumWidth(500);
    window.show();

    return app.exec();
}