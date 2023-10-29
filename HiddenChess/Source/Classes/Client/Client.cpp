#include <QJsonObject>
#include "Client.h"


Client::Client(QObject *parent)
        : QObject(parent) {
    manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, this, &Client::responseHandler);
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
        emit roomCreated_signal(jsonObject["room-id"].toString());
    } else if (jsonObject["message"] == "Rooms list") {
        qDebug() << jsonObject["rooms"].toString();
        emit roomsList_signal(jsonObject["rooms"].toObject());
    } else if (jsonObject["message"] == "Connection available") {
        emit connected_signal();
    } else if (jsonObject["message"] == "Successfully joined") {
        emit joinedToRoom_signal();
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
    qDebug() << "Client::sendJoiningRequest_slot(QString roomId, QString roomPasswd)slot called";

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

