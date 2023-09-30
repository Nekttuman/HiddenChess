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
    Room(qintptr hostSocketDescriptor, QString roomName, QString roomPswd) : m_name(std::move(roomName)),
                                                                             m_pswd(std::move(roomPswd)) {
        m_hostSocketDescriptor = hostSocketDescriptor;
    }

    void setHostNick(QString nick) {
        m_hostNick = nick;
    }

    QString getHostNick() { return m_hostNick; }

    [[nodiscard]] qintptr getHostSocketDescriptor() const {
        return m_hostSocketDescriptor;
    }

    void setOpponentNick(QString nick) {
        m_opponentNick = std::move(nick);
    }

    QString getName() { return m_name; }

    bool checkPswd(const QString &pswd) { return m_pswd == pswd; }

    bool hasOpponent() const { return m_oponentSocketDescriptor != -1; }

    void addOpponent(qintptr opponentSocketDescriptor, QString nick) {
        m_oponentSocketDescriptor = opponentSocketDescriptor;
        m_opponentNick = std::move(nick);
    }

    QString getOpponentNick(qintptr requesterSocketDescriptor) {
        if (requesterSocketDescriptor == m_hostSocketDescriptor)
            return m_opponentNick;
        return m_hostNick;
    }

};
