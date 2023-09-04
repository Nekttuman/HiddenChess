#include "Server.h"

Server::Server(QObject *parent)
	: QTcpServer(parent)
{}

Server::~Server()
{}
