#ifndef DCDB_SERVER_H
#define DCDB_SERVER_H

#include "ixwebsocket/IXWebSocketServer.h"

using namespace ix;

namespace P2P
{
    class Server
    {
    public:
        std::thread startServer(int port);
        bool isStarted();
        void stopServer();

    private:
        WebSocketServer *server;
        void _startServer(int port);
        bool serverStarted = false;
    };

}

#endif
