#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QColorDialog>
#include <QSlider>
#include <QPushButton>

class gui : public QWidget {

    public:
        gui();
        ~gui();

    private slots:
        void updateTransitionSpeed();
        void updateColorHoldDuration();
        void updateBrightness();
        void setColor1();
        void setColor2();
        void closeWindow();

    private:
        QGridLayout* settingsLayout;

        QLabel* animationTypeLabel;
        QComboBox* animationType;

        QLabel* transitionSpeedLabel;
        QSlider* transitionSpeed;
        QLineEdit* transitionSpeedValue;
        QGridLayout* transitionSpeedLayout;

        QLabel* colorHoldLabel;
        QSlider* colorHoldDuration;
        QLineEdit* colorHoldDurationValue;
        QGridLayout* colorHoldLayout;

        QLabel* color1Label;
        QWidget* color1Box;
        QPushButton* color1EditButton;
        QPalette color1Palette;
        QGridLayout* color1Layout;

        QLabel* color2Label;
        QWidget* color2Box;
        QPushButton* color2EditButton;
        QPalette color2Palette;
        QGridLayout* color2Layout;

        QLabel* brightnessLabel;
        QSlider* brightness;
        QLineEdit* brightnessValue;
        QGridLayout* brightnessLayout;

        QHBoxLayout* buttonLayout;
        QPushButton* saveButton;
        QPushButton* closeButton;

        QVBoxLayout* layout;
};

#endif