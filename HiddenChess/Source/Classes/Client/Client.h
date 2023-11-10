#pragma once

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrlQuery>
#include <QtCore/QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QTimer>


const QString DOMEN_API_URL = "http://127.0.0.1:8000/api/";

const QString CHECK_CONNECTION_URL = DOMEN_API_URL + "check-connection/";


class Client : public QObject {
Q_OBJECT

public:
    Client(QObject *parent);

    ~Client();


signals:

    void clientErr_signal(QString);

    void authFaild_signal(QString);

    void connected_signal();

    void roomsList_signal(QJsonObject rooms);

    void roomNameUniqConfirmed_signal();

    void roomNameUniqNotConfirmed_signal();

    void roomCreated_signal(QString roomId);

    void joinedToRoom_signal();

    void loginSuccess_signal();

    void opponentMadeMove_signal(QPoint prevPoint, QPoint point);

    void opponentNickReceived_signal(QString opponentNick);

public slots:

    void tryCreateRoom_slot(QString roomName, QString pswd);

    void tryLoggin_slot(QString login, QString pswd);

    void connectToHost_slot();

    void getRoomsList_slot();

    void sendMove_slot(QPoint prevPoint, QPoint nextPoint);

    void checkOpponentMove_slot();

    void checkRoomNameUniq_slot(QString roomName); //for creating
    void sendJoiningRequest_slot(QString roomId, QString roomPasswd); // for Joining

private:

    void responseHandler(QNetworkReply *reply);

    QByteArray m_data;

    const QUrl loginUrl = QUrl(DOMEN_API_URL + "login/");
    const QUrl roomJoinUrl = QUrl(DOMEN_API_URL + "gameroom/join/");
    const QUrl roomCreationUrl = QUrl(DOMEN_API_URL + "gameroom/create/");
    const QUrl roomsListUrl = QUrl(DOMEN_API_URL + "gameroom/list/");
    const QUrl moveUrl = QUrl(DOMEN_API_URL + "gameroom/move/");
    const QUrl checkMoveUrl = QUrl(DOMEN_API_URL + "gameroom/check-move/");
    bool connectionAvailable = false;

    QString sessionId; // Cookie
    QString csrfToken; // Cookie
    QString m_roomId;
    bool isRoomOwner = false;

    void getCookieData(QList<QNetworkReply::RawHeaderPair> headers);

    QNetworkAccessManager *manager;

    void SendToServer(QString str);

    bool m_waitMove = true;


    QTimer* timer;
};
