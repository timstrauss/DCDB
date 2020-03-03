#include <iostream>
#include "server.h"

using namespace P2P;
using namespace std;

P2PWSServer::P2PWSServer(int port) {
    this->port = port;
    server = new WebSocketServer(port, "127.0.0.1");
}

P2PWSServer::~P2PWSServer() {
    this->stop();
}

void P2PWSServer::stop() {
    while(server->getClients().size() > 0) {
        _sleep(200);
    }
    server->stop();
    serverStarted = false;

    cout << "Server stopped" << endl;
}

void P2PWSServer::privateStart() {
    if(!serverStarted) {
        run();
    }
}

void P2PWSServer::run() {
    server->setOnConnectionCallback(
            [this](shared_ptr<WebSocket> webSocket,
                         shared_ptr<ConnectionState> connectionState) {
                cout << "Message";
                webSocket->setOnMessageCallback(
                        [webSocket, connectionState, this](const WebSocketMessagePtr msg) {
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
                            }
                        });
            }
    );

    auto res = server->listen();

    if (res.first) {
        server->start();
        serverStarted = true;
    }
}

void P2PWSServer::start() {
    privateStart();
}

bool P2PWSServer::running() {
    return serverStarted;
}
