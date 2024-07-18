#include "gui.h"

gui::gui() {
    // Settings layout
    settingsLayout = new QGridLayout();
    settingsLayout->setContentsMargins(11, 11, 11, 20);
    settingsLayout->setVerticalSpacing(15);

    // Animation type
    animationTypeLabel = new QLabel("Animation");

    animationType = new QComboBox();
    animationType->addItem("Rainbow");
    animationType->addItem("Static Color");
    animationType->addItem("Gradient");
    animationType->addItem("Color Pulse");

    settingsLayout->addWidget(animationTypeLabel, 0, 0);
    settingsLayout->addWidget(animationType, 0, 1, 1, 4);

    // Transition speed
    transitionSpeedLabel = new QLabel("Transition Speed");

    transitionSpeed = new QSlider(Qt::Horizontal);
    transitionSpeed->setTickPosition(QSlider::TicksBelow);
    transitionSpeed->setTickInterval(15);
    transitionSpeed->setSingleStep(1);
    transitionSpeed->setPageStep(1);
    transitionSpeed->setMinimum(0);
    transitionSpeed->setMaximum(255);

    transitionSpeedValue = new QLineEdit();
    transitionSpeedValue->setMaximumWidth(40);
    transitionSpeedValue->setReadOnly(true);

    transitionSpeedLayout = new QGridLayout();
    transitionSpeedLayout->setHorizontalSpacing(11);
    transitionSpeedLayout->addWidget(transitionSpeed, 0, 0);
    transitionSpeedLayout->addWidget(transitionSpeedValue, 0, 1, 1, 6);

    settingsLayout->addWidget(transitionSpeedLabel, 1, 0);
    settingsLayout->addLayout(transitionSpeedLayout, 1, 1, 1, 4);

    // Color hold duration
    colorHoldLabel = new QLabel("Color Hold Duration");

    colorHoldDuration = new QSlider(Qt::Horizontal);
    colorHoldDuration->setTickPosition(QSlider::TicksBelow);
    colorHoldDuration->setTickInterval(15);
    colorHoldDuration->setSingleStep(1);
    colorHoldDuration->setPageStep(1);
    colorHoldDuration->setMinimum(0);
    colorHoldDuration->setMaximum(255);

    colorHoldDurationValue = new QLineEdit();
    colorHoldDurationValue->setMaximumWidth(40);
    colorHoldDurationValue->setReadOnly(true);

    colorHoldLayout = new QGridLayout();
    colorHoldLayout->setHorizontalSpacing(11);
    colorHoldLayout->addWidget(colorHoldDuration, 0, 0);
    colorHoldLayout->addWidget(colorHoldDurationValue, 0, 1, 1, 6);

    settingsLayout->addWidget(colorHoldLabel, 2, 0);
    settingsLayout->addLayout(colorHoldLayout, 2, 1, 1, 4);

    // Color 1
    color1Label = new QLabel("Color 1");

    color1Palette = QPalette();
    color1Palette.setColor(QPalette::Window, Qt::red);

    color1Box = new QWidget();
    color1Box->setAutoFillBackground(true);
    color1Box->setPalette(color1Palette);

    color1EditButton = new QPushButton("Edit");
    color1EditButton->setMaximumWidth(75);

    color1Layout = new QGridLayout();
    color1Layout->setHorizontalSpacing(11);
    color1Layout->addWidget(color1Box, 0, 0);
    color1Layout->addWidget(color1EditButton, 0, 1, 1, 6);

    settingsLayout->addWidget(color1Label, 3, 0);
    settingsLayout->addLayout(color1Layout, 3, 1, 1, 4);

    // Color 2
    color2Label = new QLabel("Color 2");

    color2Palette = QPalette();
    color2Palette.setColor(QPalette::Window, Qt::red);

    color2Box = new QWidget();
    color2Box->setAutoFillBackground(true);
    color2Box->setPalette(color2Palette);

    color2EditButton = new QPushButton("Edit");
    color2EditButton->setMaximumWidth(75);

    color2Layout = new QGridLayout();
    color2Layout->setHorizontalSpacing(11);
    color2Layout->addWidget(color2Box, 0, 0);
    color2Layout->addWidget(color2EditButton, 0, 1, 1, 6);

    settingsLayout->addWidget(color2Label, 4, 0);
    settingsLayout->addLayout(color2Layout, 4, 1, 1, 4);

    // LED brightness level
    brightnessLabel = new QLabel("Brightness");

    brightness = new QSlider(Qt::Horizontal);
    brightness->setTickPosition(QSlider::TicksBelow);
    brightness->setTickInterval(15);
    brightness->setSingleStep(1);
    brightness->setPageStep(1);
    brightness->setMinimum(0);
    brightness->setMaximum(255);

    brightnessValue = new QLineEdit();
    brightnessValue->setMaximumWidth(40);
    brightnessValue->setReadOnly(true);

    brightnessLayout = new QGridLayout();
    brightnessLayout->setHorizontalSpacing(11);
    brightnessLayout->addWidget(brightness, 0, 0);
    brightnessLayout->addWidget(brightnessValue, 0, 1, 1, 6);

    settingsLayout->addWidget(brightnessLabel, 5, 0);
    settingsLayout->addLayout(brightnessLayout, 5, 1, 1, 4);

    buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save");
    saveButton->setMaximumWidth(75);

    closeButton = new QPushButton("Close");
    closeButton->setMaximumWidth(75);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->setAlignment(Qt::AlignHCenter);

    layout = new QVBoxLayout();
    layout->addLayout(settingsLayout);
    layout->addLayout(buttonLayout);
    
    setLayout(layout);
    setWindowTitle("Razer DeathAdder Essential RGB Editor");

    connect(transitionSpeed, &QSlider::valueChanged, this, &gui::updateTransitionSpeed);
    connect(colorHoldDuration, &QSlider::valueChanged, this, &gui::updateColorHoldDuration);
    connect(brightness, &QSlider::valueChanged, this, &gui::updateBrightness);
    connect(color1EditButton, &QPushButton::clicked, this, &gui::setColor1);
    connect(color2EditButton, &QPushButton::clicked, this, &gui::setColor2);
    connect(closeButton, &QPushButton::clicked, this, &gui::closeWindow);
}

gui::~gui() {
    close();
}

void gui::updateTransitionSpeed() {
    transitionSpeedValue->setText(QString::number(transitionSpeed->value()));
}

void gui::updateColorHoldDuration() {
    colorHoldDurationValue->setText(QString::number(colorHoldDuration->value()));
}

void gui::updateBrightness() {
    brightnessValue->setText(QString::number(brightness->value()));
}

void gui::setColor1() {
    QColor newColor1 = QColorDialog::getColor();
    color1Palette.setColor(QPalette::Window, newColor1);
    color1Box->setPalette(color1Palette);
}

void gui::setColor2() {
    QColor newColor2 = QColorDialog::getColor();
    color2Palette.setColor(QPalette::Window, newColor2);
    color2Box->setPalette(color2Palette);
}

void gui::closeWindow() {
    close();
}