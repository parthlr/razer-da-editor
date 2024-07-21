#include "gui.h"
#include <iostream>
#include <fstream>
#include <string>

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

    gui::loadSettings();
    
    setLayout(layout);
    setWindowTitle("Razer DeathAdder Essential RGB Editor");

    connect(animationType, &QComboBox::currentTextChanged, this, &gui::updateAnimationType);
    connect(transitionSpeed, &QSlider::valueChanged, this, &gui::updateTransitionSpeed);
    connect(colorHoldDuration, &QSlider::valueChanged, this, &gui::updateColorHoldDuration);
    connect(brightness, &QSlider::valueChanged, this, &gui::updateBrightness);
    connect(color1EditButton, &QPushButton::clicked, this, &gui::setColor1);
    connect(color2EditButton, &QPushButton::clicked, this, &gui::setColor2);
    connect(saveButton, &QPushButton::clicked, this, &gui::saveSettings);
    connect(closeButton, &QPushButton::clicked, this, &gui::closeWindow);
}

gui::~gui() {
    close();
}

void gui::loadSettings() {
    std::ifstream settingsFile ("settings.json");
    std::string settingsString;

    if (settingsFile.is_open()) {
        while (settingsFile.good()) {
            std::string currentLine;
            settingsFile >> currentLine;
            settingsString += currentLine;
        }
    }
    settingsFile.close();

    std::cout << "JSON: " << settingsString << std::endl;

    cJSON* settingsJSON = cJSON_Parse(settingsString.c_str());
    if (settingsJSON == NULL) {
        std::cout << "Error reading settings.json file" << std::endl;
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON* animationTypeJSON = cJSON_GetObjectItemCaseSensitive(settingsJSON, "type");
    if (animationTypeJSON == NULL) {
        std::cout << "Error getting animation type" << std::endl;
        cJSON_Delete(settingsJSON);
        return;
    }
    std::string animationTypeValue(animationTypeJSON->valuestring);
    gui::updateSettingsVisibility(animationTypeValue);

    if (transitionSpeed->isEnabled()) {
        cJSON* transitionSpeedJSON = cJSON_GetObjectItemCaseSensitive(settingsJSON, "transitionSpeed");
        if (transitionSpeed == NULL) {
            std::cout << "Error getting transition speed" << std::endl;
            cJSON_Delete(settingsJSON);
            return;
        }

        transitionSpeed->setValue(transitionSpeedJSON->valueint);
        transitionSpeedValue->setText(QString::number(transitionSpeedJSON->valueint));
    }

    cJSON* colorsJSON = cJSON_GetObjectItemCaseSensitive(settingsJSON, "colors");
    if (colorsJSON == NULL) {
        std::cout << "Error getting colors" << std::endl;
        cJSON_Delete(settingsJSON);
        return;
    }

    if (color1Box->isEnabled()) {
        cJSON* color1 = cJSON_GetArrayItem(colorsJSON, 0);
        if (color1 == NULL) {
            std::cout << "Error getting first color" << std::endl;
            cJSON_Delete(settingsJSON);
            return;
        }

        int* rgb = hexToRGB(cJSON_GetArrayItem(colorsJSON, 0)->valuestring);
        QColor color1RGB = QColor(rgb[0], rgb[1], rgb[2]);
        color1Palette.setColor(QPalette::Window, color1RGB);
        color1Box->setPalette(color1Palette);
    }

    if (color2Box->isEnabled()) {
        cJSON* color2 = cJSON_GetArrayItem(colorsJSON, 0);
        if (color2 == NULL) {
            std::cout << "Error getting second color" << std::endl;
            cJSON_Delete(settingsJSON);
            return;
        }

        int* rgb = hexToRGB(cJSON_GetArrayItem(colorsJSON, 1)->valuestring);
        QColor color2RGB = QColor(rgb[0], rgb[1], rgb[2]);
        color2Palette.setColor(QPalette::Window, color2RGB);
        color2Box->setPalette(color2Palette);
    }

    if (colorHoldDuration->isEnabled()) {
        cJSON* colorHoldJSON = cJSON_GetObjectItemCaseSensitive(settingsJSON, "breathDuration");
        if (colorHoldJSON == NULL) {
            std::cout << "Error getting color hold duration" << std::endl;
            cJSON_Delete(settingsJSON);
            return;
        }

        colorHoldDuration->setValue(colorHoldJSON->valueint);
        colorHoldDurationValue->setText(QString::number(colorHoldJSON->valueint));
    }

    cJSON* brightnessJSON = cJSON_GetObjectItemCaseSensitive(settingsJSON, "brightness");
    if (brightnessJSON == NULL) {
        std::cout << "Error getting brightness" << std::endl;
        cJSON_Delete(settingsJSON);
        return;
    }
    brightness->setValue(brightnessJSON->valueint);
    brightnessValue->setText(QString::number(brightnessJSON->valueint));

    cJSON_Delete(settingsJSON);
}

void gui::saveSettings() {
    std::string animationTypeOut;
    int transitionSpeedOut = -1;
    std::vector<const char*> colorsOut;
    int colorHoldDurationOut = -1;
    int brightnessOut = brightness->value();

    int animationTypeIndex = animationType->currentIndex();

    switch (animationTypeIndex) {
        case AnimationType::RAINBOW:
            animationTypeOut = "rainbow";
            transitionSpeedOut = transitionSpeed->value();
            break;
        case AnimationType::STATIC:
            animationTypeOut = "static";
            colorsOut.push_back(color1Palette.color(QPalette::Window).name().toStdString().c_str());
            break;
        case AnimationType::GRADIENT:
            animationTypeOut = "gradient";
            transitionSpeedOut = transitionSpeed->value();
            colorsOut.push_back(color1Palette.color(QPalette::Window).name().toStdString().c_str());
            colorsOut.push_back(color2Palette.color(QPalette::Window).name().toStdString().c_str());
            break;
        case AnimationType::PULSE:
            animationTypeOut = "pulse";
            transitionSpeedOut = transitionSpeed->value();
            colorsOut.push_back(color1Palette.color(QPalette::Window).name().toStdString().c_str());
            colorHoldDurationOut = colorHoldDuration->value();
            break;
    }

    cJSON* settingsJSON = cJSON_CreateObject();
    if (settingsJSON == NULL) {
        cJSON_Delete(settingsJSON);
        return;
    }

    std::cout << "Created settings json object" << std::endl;

    cJSON* animationTypeJSON = cJSON_CreateString(animationTypeOut.c_str());
    if (animationTypeJSON == NULL) {
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON_AddItemToObject(settingsJSON, "type", animationTypeJSON);

    std::cout << "Created animation type json object" << std::endl;

    cJSON* transitionSpeedJSON = cJSON_CreateNumber(transitionSpeedOut);
    if (transitionSpeedJSON == NULL) {
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON_AddItemToObject(settingsJSON, "transitionSpeed", transitionSpeedJSON);

    std::cout << "Created transition speed json object" << std::endl;

    cJSON* colorsJSON;
    if (colorsOut.empty()) {
        colorsJSON = cJSON_CreateArray();
    } else {
        colorsJSON = cJSON_CreateStringArray(&colorsOut[0], colorsOut.size());
    }

    if (colorsJSON == NULL) {
        std::cout << "Colors object is null" << std::endl;
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON_AddItemToObject(settingsJSON, "colors", colorsJSON);

    std::cout << "Created colors json object" << std::endl;

    cJSON* colorHoldJSON = cJSON_CreateNumber(colorHoldDurationOut);
    if (colorHoldJSON == NULL) {
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON_AddItemToObject(settingsJSON, "breathDuration", colorHoldJSON);

    std::cout << "Created breath json object" << std::endl;

    cJSON* brightnessJSON = cJSON_CreateNumber(brightnessOut);
    if (brightnessJSON == NULL) {
        cJSON_Delete(settingsJSON);
        return;
    }

    cJSON_AddItemToObject(settingsJSON, "brightness", brightnessJSON);

    std::cout << "Created brightness json object" << std::endl;

    char* settingsString = cJSON_Print(settingsJSON);
    std::string settings(settingsString);

    std::ofstream settingsFile("settings.json");
    settingsFile << settings;
    settingsFile.close();

    cJSON_Delete(settingsJSON);

    std::cout << "Saved settings" << std::endl; 
}

void gui::updateSettingsVisibility(std::string animationTypeValue) {
    if (animationTypeValue == "rainbow") {
        animationType->setCurrentIndex(AnimationType::RAINBOW);

        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Disable colors
        color1Label->setDisabled(true);
        color1Box->setDisabled(true);
        color1EditButton->setDisabled(true);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (animationTypeValue == "static") {
        animationType->setCurrentIndex(AnimationType::STATIC);

        // Disable transition speed
        transitionSpeedLabel->setDisabled(true);
        transitionSpeed->setDisabled(true);
        transitionSpeedValue->setDisabled(true);

        // Enable color 1, disable color 2
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (animationTypeValue == "gradient") {
        animationType->setCurrentIndex(AnimationType::GRADIENT);

        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Enable colors
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(false);
        color2Box->setDisabled(false);
        color2EditButton->setDisabled(false);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (animationTypeValue == "pulse") {
        animationType->setCurrentIndex(AnimationType::PULSE);

        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Enable color 1, disable color 2
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    }
}

void gui::updateAnimationType() {
    int currentAnimationIndex = animationType->currentIndex();
    if (currentAnimationIndex == 0) {
        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Disable colors
        color1Label->setDisabled(true);
        color1Box->setDisabled(true);
        color1EditButton->setDisabled(true);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (currentAnimationIndex == 1) {
        // Disable transition speed
        transitionSpeedLabel->setDisabled(true);
        transitionSpeed->setDisabled(true);
        transitionSpeedValue->setDisabled(true);

        // Enable color 1, disable color 2
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (currentAnimationIndex == 2) {
        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Enable colors
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(false);
        color2Box->setDisabled(false);
        color2EditButton->setDisabled(false);

        // Disable color hold duration
        colorHoldLabel->setDisabled(true);
        colorHoldDuration->setDisabled(true);
        colorHoldDurationValue->setDisabled(true);
    } else if (currentAnimationIndex == 3) {
        // Enable transition speed
        transitionSpeedLabel->setDisabled(false);
        transitionSpeed->setDisabled(false);
        transitionSpeedValue->setDisabled(false);

        // Enable color 1, disable color 2
        color1Label->setDisabled(false);
        color1Box->setDisabled(false);
        color1EditButton->setDisabled(false);

        color2Label->setDisabled(true);
        color2Box->setDisabled(true);
        color2EditButton->setDisabled(true);

        // Disable color hold duration
        colorHoldLabel->setDisabled(false);
        colorHoldDuration->setDisabled(false);
        colorHoldDurationValue->setDisabled(false);
    }
}

int* gui::hexToRGB(char* hex) {
    int* rgb = new int[3];
    int hexInt = strtol(&hex[1], NULL, 16);

    rgb[0] = (hexInt >> 16) & 0xFF;
    rgb[1] = (hexInt >> 8) & 0xFF;
    rgb[2] = (hexInt) & 0xFF;

    return rgb;
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
    QColor newColor1 = QColorDialog::getColor(color1Palette.color(QPalette::Window));
    color1Palette.setColor(QPalette::Window, newColor1);
    color1Box->setPalette(color1Palette);
}

void gui::setColor2() {
    QColor newColor2 = QColorDialog::getColor(color2Palette.color(QPalette::Window));
    color2Palette.setColor(QPalette::Window, newColor2);
    color2Box->setPalette(color2Palette);
}

void gui::closeWindow() {
    close();
}