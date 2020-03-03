#include <iostream>
#include "client.h"

using namespace P2P;

thread P2PWSClient::startClient() {
    return thread(&P2P::P2PWSClient::_startClient, this);
}

void P2PWSClient::_startClient() {
    socket = new WebSocket;

    string url("ws://127.0.0.1:12345");
    socket->setUrl(url);
    socket->disableAutomaticReconnection();

    socket->setOnMessageCallback([](const WebSocketMessagePtr &msg) {
        if (msg->type == WebSocketMessageType::Message) {
            cout << msg->str << endl;
        }
    });

    WebSocketInitResult success = socket->connect(5);

    if (success.success) {
        thread setStarted(&P2P::P2PWSClient::setStarted, this);

        socket->run();

        setStarted.join();

        startedClient = false;

        cout << "Client stopped" << endl;
    }
}

void P2PWSClient::setStarted() {
    _sleep(2500);
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