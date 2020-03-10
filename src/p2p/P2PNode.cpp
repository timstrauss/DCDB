#include "P2PNode.h"

using namespace P2P;

P2PNode::P2PNode(int port) {
    server = new Server(port);
}
