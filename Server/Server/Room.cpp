#include "Room.h"


Room::Room(qintptr hostSocketDescriptor, QString roomName, QString roomPswd) : m_name(std::move(roomName)),
                                                                               m_pswd(std::move(roomPswd)) {
    m_hostSocketDescriptor = hostSocketDescriptor;
}

void Room::addOpponent(qintptr opponentSocketDescriptor, QString nick) {
    m_oponentSocketDescriptor = opponentSocketDescriptor;
    m_opponentNick = std::move(nick);
}
