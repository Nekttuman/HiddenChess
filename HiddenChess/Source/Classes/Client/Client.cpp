#include <QJsonObject>
#include "Client.h"


Client::Client(QObject *parent)
        : QObject(parent) {
    manager = new QNetworkAccessManager();

    moveTimer = new QTimer(this);
    readyTimer = new QTimer(this);

    connect(moveTimer, &QTimer::timeout, this, &Client::checkOpponentMove_slot);
    QObject::connect(manager, &QNetworkAccessManager::finished, this, &Client::responseHandler);
    connect(readyTimer, &QTimer::timeout, this, &Client::checkOpponentReady_slot);
}

Client::~Client() {}


void Client::responseHandler(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
        emit authFaild_signal(reply->errorString());
        qDebug() << "NOT AUTH" << reply->error();//<<reply->errorString();
    } else if (reply->error()) {
        qDebug() << "ERRRR" << reply->error();//<<reply->errorString();
        emit clientErr_signal(QString("Error %1").arg(reply->errorString()));
        connectionAvailable = false;
        reply->deleteLater();
        return;
    } else {
        connectionAvailable = true;
    }

    // get csrf and token session
    getCookieData(reply->rawHeaderPairs());

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonDocument.object();

    if (jsonObject["message"] == "Login successful") {
        emit loginSuccess_signal();
        // todo: save login and passwd to settings or session token
    } else if (jsonObject["message"] == "Room created") {
        m_roomId = jsonObject["room-id"].toString();
        qDebug() << m_roomId << jsonObject["room-id"];
        emit roomCreated_signal(jsonObject["room-id"].toString());
        isRoomOwner = true;
    } else if (jsonObject["message"] == "Rooms list") {
        qDebug() << jsonObject["rooms"].toString();
        emit roomsList_signal(jsonObject["rooms"].toObject());
    } else if (jsonObject["message"] == "Connection available") {
        emit connected_signal();
    } else if (jsonObject["message"] == "Successfully joined") {
        m_roomId = jsonObject["room-id"].toString();
        qDebug() << m_roomId << jsonObject["room-id"];
        emit joinedToRoom_signal();
        isRoomOwner = false;
    } else if (jsonObject["message"] == "new move") {
        QPoint from = QPoint{jsonObject["prev-pos-x"].toString().toInt(), jsonObject["prev-pos-y"].toString().toInt()};
        QPoint two = QPoint{jsonObject["next-pos-x"].toString().toInt(), jsonObject["next-pos-y"].toString().toInt()};

        qDebug() << "yeeeee" << from << two;
        emit opponentMadeMove_signal(from, two);
        moveTimer->stop();
    } else if (jsonObject["message"] == "opponent ready"){
        emit opponentReady_signal();

        readyTimer->stop();
    } else if (jsonObject["message"] == "opponent not ready"){
        emit opponentNotReady_signal();
    }

        qDebug() << QJsonDocument::fromJson(responseData);

    reply->deleteLater();
}


void Client::connectToHost_slot() {
    //send test request
    QNetworkRequest request((QUrl(CHECK_CONNECTION_URL)));
    manager->get(request);

}


void Client::tryCreateRoom_slot(QString roomName, QString pswd) {
    qDebug() << "Client::tryCreateRoom_slot(QString Login, QString pswd) slot called";

    QNetworkRequest request(roomCreationUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;

    postData.addQueryItem("room-name", roomName);
    postData.addQueryItem("room-password", pswd);
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}


void Client::checkRoomNameUniq_slot(QString roomName) {

}

void Client::sendJoiningRequest_slot(QString roomId, QString roomPasswd) {
    qDebug() << "Client::sendJoiningRequest_slot(QString roomId, QString roomPasswd)slot called" << roomPasswd;

    QNetworkRequest request(roomJoinUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", roomId);
    postData.addQueryItem("room-password", roomPasswd);
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Client::tryLoggin_slot(QString login, QString pswd) {
    qDebug() << "Client::tryLoggin_slot(QString Login, QString pswd) slot called";

    QNetworkRequest request(loginUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("username", login);
    postData.addQueryItem("password", pswd);
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Client::getCookieData(QList<QNetworkReply::RawHeaderPair> headers) {
    QStringList cookieHeaderList;

    // Find the "Set-Cookie" headers and collect them in a list
    for (const QNetworkReply::RawHeaderPair &pair: headers) {
        if (pair.first == "Set-Cookie") {
            cookieHeaderList.append(pair.second + ";");
        }
    }

    // Split each cookie header into individual cookies
    for (const QString &cookieHeader: cookieHeaderList) {
        QStringList cookies = cookieHeader.split(';');

        if (cookieHeader.contains("sessionid")) {
            int n = cookieHeader.indexOf("sessionid=") + QString("sessionid=").length();
            QString s = cookieHeader.mid(n, -1);
            sessionId = s.split(';')[0];
        }
        if (cookieHeader.contains("csrftoken")) {
            int n = cookieHeader.indexOf("csrftoken=") + QString("csrftoken=").length();
            QString s = cookieHeader.mid(n, -1);
            csrfToken = s.split(';')[0];
        }
        qDebug() << sessionId << csrfToken;


    }
}

void Client::getRoomsList_slot() {
    qDebug() << "Client::getRoomsList_slot() slot called";

    QNetworkRequest request(roomsListUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request, "");
}

void Client::sendMove_slot(QPoint prevPoint, QPoint nextPoint) {
    qDebug() << "Client::sendMove_slot(QPoint prevPoint, QPoint nextPoint) slot called" << prevPoint << nextPoint
             << m_roomId;

    QNetworkRequest request(moveUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", m_roomId);
    postData.addQueryItem("prev-pos-x", QString::number(prevPoint.x()));
    postData.addQueryItem("prev-pos-y", QString::number(prevPoint.y()));
    postData.addQueryItem("next-pos-x", QString::number(nextPoint.x()));
    postData.addQueryItem("next-pos-y", QString::number(nextPoint.y()));
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());


    moveTimer->start(3000); // Start the moveTimer with a 3-second interval (3000 ms)

}

void Client::checkOpponentMove_slot() {
    qDebug() << "checkOpponentMove_slot() slot called" << m_roomId;

    QNetworkRequest request(checkMoveUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", m_roomId);
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void Client::sendUserReady_slot() {
    qDebug() << "sendUserReady_slot() slot called" << m_roomId;

    QNetworkRequest request(userReadyUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", m_roomId);
    postData.addQueryItem("user-ready", "true");
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    readyTimer->start(3000); // Start the moveTimer with a 3-second interval (3000 ms)
}

void Client::sendUserNotReady_slot() {
    qDebug() << "sendUserNotReady_slot slot called" << m_roomId;

    QNetworkRequest request(userReadyUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", m_roomId);
    postData.addQueryItem("user-ready", "false");
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    readyTimer->stop();
}

void Client::checkOpponentReady_slot() {
    qDebug() << "checkOpponentMove_slot() slot called" << m_roomId;

    QNetworkRequest request(checkReadyUrl);

    request.setRawHeader("X-CSRFToken", csrfToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("room-id", m_roomId);
    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

