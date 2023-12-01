#include "GameConfirmationWidget.h"


GameConfirmationWidget::GameConfirmationWidget(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
    connect(ui.saveButton, &QPushButton::released, this, &GameConfirmationWidget::saveSettings_slot);
    connect(ui.readyRadioButton, &QRadioButton::clicked, this, [&]() {
        disableRoomSettings();  // TODO: create slot from this lambda
        if (isOpponentReady) {
            this->setDisabled(true);
            this->hide();
            if (isRoomOwner)
                    emit roomSettingsChanged_signal(
                        {(ui.colorComboBox->currentText() == "black") ? FigureColor::black : FigureColor::white, 0});

            emit enableStartGame_signal();

        }
        emit userReady_signal();
    });
    connect(ui.notReadyRadioButton, &QRadioButton::clicked, this, [&]() {
        emit userNotReady_signal();
        if (isRoomOwner)
            enableRoomSettings();
    });
    connect(ui.backToMenuBtn, &QPushButton::released, this, [&]() { emit backToMenu_signal(); });
    connect(ui.backToMenuBtn, &QPushButton::released, this, &GameConfirmationWidget::hide);
}

GameConfirmationWidget::~GameConfirmationWidget() {
}

void GameConfirmationWidget::saveSettings_slot() {
    color = (ui.colorComboBox->currentText() == "black") ? FigureColor::black : FigureColor::white;
    if (ui.infRadioButton->isChecked())
        allowedFakesCount = -1; // inf
    else
        allowedFakesCount = ui.fakesCountSpinBox->value();
    emit roomSettingsChanged_signal({color, allowedFakesCount});
}

void GameConfirmationWidget::userIsRoomOwner_slot() {
    isRoomOwner = true;
    ui.colorComboBox->setCurrentText("white");
    if (ui.notReadyRadioButton->isChecked())
        enableRoomSettings();
}

void GameConfirmationWidget::disableRoomSettings() {

    ui.colorComboBox->setEnabled(false);
    ui.fakesCountSpinBox->setEnabled(false);
    ui.infRadioButton->setEnabled(false);
    ui.saveButton->setEnabled(false);

}

void GameConfirmationWidget::enableRoomSettings() {
    ui.colorComboBox->setEnabled(true);
    ui.fakesCountSpinBox->setEnabled(true);
    ui.infRadioButton->setEnabled(true);
    ui.saveButton->setEnabled(true);
}

void GameConfirmationWidget::opponentReady_slot() {
    ui.opponentStatusLabel->setText("Opponent Ready");

    if (ui.readyRadioButton->isChecked()) {
        this->setDisabled(true);
        if (isRoomOwner)
                emit roomSettingsChanged_signal(
                    {(ui.colorComboBox->currentText() == "black") ? FigureColor::black : FigureColor::white, 0});

        this->hide();
        emit enableStartGame_signal();
    }
    isOpponentReady = true;
}

void GameConfirmationWidget::opponentNotReady_slot() {
    ui.opponentStatusLabel->setText("Waiting opponent");

    this->setDisabled(false);

    isOpponentReady = false;
}