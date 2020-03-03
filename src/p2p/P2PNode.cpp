#include <iostream>
#include "P2PNode.h"

using namespace P2P;

P2PNode::P2PNode(int newPort) {
    port = newPort;
}

bool P2PNode::start() {
    P2PWSServer *newServer;
    newServer = new P2PWSServer(port);
    newServer->start();
    server = newServer;
    for (int i = 0; i < 20; i++) {
        if (newServer->running()) {
            return true;
        }
        _sleep(1000);
    }
    return false;
}

void P2PNode::stop() {
    server->stop();
}
