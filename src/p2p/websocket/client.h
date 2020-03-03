#ifndef DCDB_CLIENT_H
#define DCDB_CLIENT_H

#include "ixwebsocket/IXWebSocket.h"

using namespace ix;
using namespace std;

namespace P2P {
    class Client
    {
    public:
        thread startClient();
        void send(string message);
        bool isStarted();
        void stopClient();

    private:
        void _startClient();
        bool startedClient = false;
        WebSocket *socket;
    };
}

#endif //DCDB_CLIENT_H
