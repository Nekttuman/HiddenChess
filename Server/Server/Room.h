#include <QObject>
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>
#include <utility>


class Room {
    qintptr m_hostSocketDescriptor = -1;
    qintptr m_oponentSocketDescriptor = -1;

    QString m_hostNick;
    QString m_opponentNick;

    QString m_name;
    QString m_pswd;

public:
    Room(qintptr hostSocketDescriptor, QString roomName, QString roomPswd);

    void setHostNick(QString nick) { m_hostNick = nick; }

    void addOpponent(qintptr opponentSocketDescriptor, QString nick);

    QString getHostNick() { return m_hostNick; }

    [[nodiscard]] qintptr getHostSocketDescriptor() const { return m_hostSocketDescriptor; }

    QString getName() { return m_name; }

    bool checkPswd(const QString &pswd) { return m_pswd == pswd; }

    bool hasOpponent() const { return m_oponentSocketDescriptor != -1; }

};
