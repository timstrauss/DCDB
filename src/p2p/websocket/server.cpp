#include <iostream>
#include "server.h"

using namespace P2P;
using namespace std;

thread Server::startServer(int port) {
    return thread(&Server::_startServer, this, port);
}

void Server::_startServer(int port) {
    WebSocketServer newServer(port, "127.0.0.1");

    newServer.setOnConnectionCallback(
            [&newServer](shared_ptr<WebSocket> webSocket,
                         shared_ptr<ConnectionState> connectionState) {
                webSocket->setOnMessageCallback([webSocket, connectionState, &newServer](const WebSocketMessagePtr msg) {
                    if (msg->type == ix::WebSocketMessageType::Open) {
                        cerr << "New connection" << endl;

                        cerr << "id: " << connectionState->getId() << endl;

                        cerr << "Uri: " << msg->openInfo.uri << endl;

                        cerr << "Headers:" << endl;
                        for (auto it : msg->openInfo.headers) {
                            cerr << it.first << ": " << it.second << endl;
                        }
                    } else if (msg->type == ix::WebSocketMessageType::Message) {
                        webSocket->send(msg->str, msg->binary);
                    } else if (msg->type == WebSocketMessageType::Close) {
                        cerr << connectionState->getId() << endl;
                    }
                });
            }
    );

    auto res = newServer.listen();
    newServer.start();

    server = &newServer;
    serverStarted = true;

    newServer.wait();

    serverStarted = false;

    cout << "Server stopped" << endl;
}

bool Server::isStarted() {
    return serverStarted;
}

void Server::stopServer() {
    server->stop();
}
