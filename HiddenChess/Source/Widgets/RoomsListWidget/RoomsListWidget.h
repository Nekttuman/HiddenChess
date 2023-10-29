#pragma once

#include <QWidget>
#include "QJsonObject"
#include "ui_RoomsListWidget.h"

class RoomData {
public:
    bool m_isOpen;
    QString m_roomName;
    QString m_roomId;

    RoomData() {}

    RoomData(bool isOpen, QString roomName, QString roomId) :
            m_roomId(roomId), m_roomName(roomName), m_isOpen(isOpen) {}

    friend QDataStream &operator<<(QDataStream &out, const RoomData &roomData) {
        out << roomData.m_isOpen << roomData.m_roomName << roomData.m_roomId;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, RoomData &roomData) {
        in >> roomData.m_isOpen >> roomData.m_roomName >> roomData.m_roomId;
        return in;
    }
};

class RoomsListWidget : public QWidget {
Q_OBJECT

public:
    explicit RoomsListWidget(QWidget *parent = nullptr);

    ~RoomsListWidget() override;

signals:

    void refresh_signal();

    void roomListItemSelected_signal(QString roomName, QString roomId);

public slots:

    void parseJson_slot(QJsonObject json);

    void emitItemSelectedSignal_slot(QListWidgetItem *item);

private:
    Ui::RoomsListWidgetClass ui;
    QList<RoomData *> *rooms = nullptr;

    void fillWidgetList();
};

