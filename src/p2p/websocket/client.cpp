#include <iostream>
#include "client.h"

using namespace P2P;

thread P2PWSClient::startClient() {
    return thread(&P2P::P2PWSClient::_startClient, this);
}

void P2PWSClient::_startClient() {
    WebSocket newSocket;

    string url("ws://localhost:12345/");
    newSocket.setUrl(url);
    newSocket.disableAutomaticReconnection();

    newSocket.setOnMessageCallback([](const WebSocketMessagePtr &msg) {
        if (msg->type == WebSocketMessageType::Message) {
            cout << msg->str << endl;
        }
    });

    WebSocketInitResult success = newSocket.connect(1);

    socket = &newSocket;
    thread setStarted(&P2P::P2PWSClient::setStarted, this);

    newSocket.run();

    setStarted.join();

    startedClient = false;

    cout << "Client stopped" << endl;
}

void P2PWSClient::setStarted() {
    _sleep(1500);
    startedClient = true;
}

bool P2PWSClient::isStarted() {
    return startedClient;
}

void P2PWSClient::send(string message) {
    if (startedClient) {
        socket->send(message);
    }
}

void P2PWSClient::stopClient() {
    socket->stop();
}