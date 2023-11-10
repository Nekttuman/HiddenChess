#include "GameConfirmationWidget.h"


GameConfirmationWidget::GameConfirmationWidget(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
    connect(ui.saveButton, &QPushButton::released, this, &GameConfirmationWidget::saveSettings_slot);
    connect(ui.readyRadioButton, &QRadioButton::clicked, this, [&]() {
        emit userReady_signal();
        disableSettings();
    });
    connect(ui.notReadyRadioButton, &QRadioButton::clicked, this, [&]() {
        emit userReady_signal();
        if (isRoomOwner)
            enableSettings();
    });
}

GameConfirmationWidget::~GameConfirmationWidget() {
}

void GameConfirmationWidget::saveSettings_slot() {
    color = ui.colorComboBox->currentText();
    if (ui.infRadioButton->isChecked())
        allowedFakesCount = -1; // inf
    else
        allowedFakesCount = ui.fakesCountSpinBox->value();
    emit roomSettingsChanged_signal(color, allowedFakesCount);
}

void GameConfirmationWidget::userIsRoomOwner_slot() {
    isRoomOwner = true;
    enableSettings();
}

void GameConfirmationWidget::disableSettings() {

    ui.colorComboBox->setEnabled(false);
    ui.fakesCountSpinBox->setEnabled(false);
    ui.infRadioButton->setEnabled(false);
    ui.saveButton->setEnabled(false);

}

void GameConfirmationWidget::enableSettings() {
    ui.colorComboBox->setEnabled(true);
    ui.fakesCountSpinBox->setEnabled(true);
    ui.infRadioButton->setEnabled(true);
    ui.saveButton->setEnabled(true);
}
