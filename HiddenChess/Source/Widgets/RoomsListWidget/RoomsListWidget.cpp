//
// Created by 79140 on 10/27/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RoomsListWidget.h" resolved

#include "RoomsListWidget.h"
#include "ui_RoomsListWidget.h"


RoomsListWidget::RoomsListWidget(QWidget *parent) :
        QWidget(parent) {
    ui.setupUi(this);

    connect(ui.refreshButton, &QPushButton::released, this, [&]() { emit refresh_signal(); });
    connect(ui.listWidget, &QListWidget::itemClicked, this, &RoomsListWidget::emitItemSelectedSignal_slot);
}

RoomsListWidget::~RoomsListWidget() {
    delete rooms;
}

void RoomsListWidget::parseJson_slot(QJsonObject json) {
    if (rooms != nullptr)
        rooms->clear();
    rooms = new QList<RoomData *>;
    auto map = json.toVariantMap();
    for (auto key: map.keys()) {
        rooms->append(new RoomData(map[key].toMap()["isOpen"].toBool(),
                                   map[key].toMap()["room-name"].toString(),
                                   key));
    }
    fillWidgetList();
}

void RoomsListWidget::fillWidgetList() {
    ui.listWidget->clear();
    for (auto room: *rooms) {
        auto item = new QListWidgetItem(
                room->m_roomName + " | " + (room->m_isOpen ? "Open" : "Password required") + " | id: " +
                room->m_roomId, ui.listWidget, QListWidgetItem::UserType);

        QByteArray byteArray; // Used for serialization
        QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
        dataStream << *room;
        item->setData(QListWidgetItem::UserType, byteArray);
    }
}

void RoomsListWidget::emitItemSelectedSignal_slot(QListWidgetItem *item) {
    QByteArray retrievedData = item->data(QListWidgetItem::UserType).toByteArray();

    QDataStream dataStream(&retrievedData, QIODevice::ReadOnly);
    RoomData retrievedRoom;
    dataStream >> retrievedRoom;
    ui.listWidget->clear();
    emit roomListItemSelected_signal(
            retrievedRoom.m_roomName, retrievedRoom.m_roomId
    );
    qDebug()<<retrievedRoom.m_roomName<< retrievedRoom.m_roomId;
    this->hide();
}

