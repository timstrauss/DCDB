#include <iostream>
#include "client.h"
#ifdef _WIN32
#else
#include <unistd.h>
#endif

using namespace P2P;

Client::Client(string address, int port) {
    io_service ios;
    tcp::resolver resolver(ios);
    tcp::resolver::query query(address, std::to_string(port));
    tcp::resolver::iterator it = resolver.resolve(query);
    string ip = it->endpoint().address().to_string();
    endpoint = new tcp::endpoint(address::from_string(ip), port);
    ioService = new io_service();
    socket = new tcp::socket(*ioService);
    ioService->run();
}

Client::~Client() {
}

bool Client::connect() {
    try {
        socket->connect(*endpoint);
        socket->con
    } catch(const std::exception& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

bool Client::_startClient() {
}

bool Client::isStarted() {
}

void Client::send(string message) {
}

void Client::disconnect() {
}
