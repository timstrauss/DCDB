#include "P2PNode.h"

P2P::P2PNode::P2PNode(int port) {
    P2PWSServer newServer;
    server = &newServer;
    server->startServer(port);
}
