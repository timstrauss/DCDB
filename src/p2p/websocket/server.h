#ifndef DCDB_SERVER_H
#define DCDB_SERVER_H

#include "ixwebsocket/IXWebSocketServer.h"

using namespace ix;

namespace P2P
{
    class P2PWSServer
    {
    public:
        P2PWSServer(int port);
        ~P2PWSServer();
        void start();
        void stop();
        bool running();

    private:
        void privateStart();
        void run();
        int port;
        std::thread runningThread;
        WebSocketServer *server;
        bool serverStarted = false;
    };

}

#endif
