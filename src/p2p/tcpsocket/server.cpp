#include "server.h"

using namespace P2P;

Server::~Server() {
    stop();
}

void Server::stop() {
    ioService->stop();
    ioThread.join();
    listening = false;
}

Server::Server(int port) {
    ioService = new io_service();
    endpoint = new tcp::endpoint(tcp::v4(), port);
    acceptor = new tcp::acceptor(*ioService, *endpoint);
    socket = new tcp::socket(*ioService);
    work = new io_service::work(*ioService);
    ioThread = std::thread([&]{ ioService->run(); });
}
