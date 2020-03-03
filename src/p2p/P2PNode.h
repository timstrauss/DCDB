#ifndef DCDB_P2PNODE_H
#define DCDB_P2PNODE_H

#include "websocket/server.h"

using namespace std;

namespace P2P {
    class P2PNode {
    public:
        P2PNode(int);
        bool start();
        void stop();

    private:
        int port;
        P2PWSServer *server;
    };
}

#endif //DCDB_P2PNODE_H
