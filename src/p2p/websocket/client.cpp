#include <iostream>
#include "client.h"
#include <unistd.h>

using namespace P2P;

thread Client::startClient() {
    return thread(&P2P::Client::_startClient, this);
}

void Client::_startClient() {
    WebSocket newSocket;

    string url("ws://localhost:12345/");
    newSocket.setUrl(url);

    newSocket.setOnMessageCallback([](const WebSocketMessagePtr &msg) {
        if (msg->type == WebSocketMessageType::Message) {
            cout << msg->str << endl;
        }
    });

    WebSocketInitResult success = newSocket.connect(1);

    sleep(2);

    socket = &newSocket;
    startedClient = true;

    newSocket.run();

    startedClient = false;

    cout << "Client stopped" << endl;
}

bool Client::isStarted() {
    return startedClient;
}

void Client::send(string message) {
    if (startedClient) {
        WebSocketSendInfo success = socket->send(message);
    }
}

void Client::stopClient() {
    socket->close();
    socket->stop();
}