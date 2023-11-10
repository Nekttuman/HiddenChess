#include "JoiningWidget.h"
#include <QDebug>
#include <utility>

JoiningWidget::JoiningWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
}

JoiningWidget::~JoiningWidget() {}


void JoiningWidget::tryJoining_slot() {
    qDebug() << "JoiningWidget tryJoining slot called";
    emit tryJoining_signal(m_currentRoomId, ui.pswdLineEdit->text());
}

void JoiningWidget::clearFields() {
    ui.pswdLineEdit->clear();
}

void JoiningWidget::showSelf_slot(const QString& currentRoomName, QString currentRoomId) {
    m_currentRoomId = std::move(currentRoomId);
    m_currentRoomName = currentRoomName;
    this->show();
    this->ui.roomNameLabel->setText(currentRoomName);
}
