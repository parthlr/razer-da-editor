#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QBoxLayout>

class gui : public QWidget {

    public:
        gui();
        ~gui();

    private:
        QVBoxLayout* layout;
};

#endif