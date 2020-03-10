#ifndef DCDB_P2PNODE_H
#define DCDB_P2PNODE_H

#include "tcpsocket/server.h"

using namespace std;

namespace P2P {
    class P2PNode {
    public:
        P2PNode(int port);

    private:
        P2P::Server *server;
    };
}

#endif //DCDB_P2PNODE_H
