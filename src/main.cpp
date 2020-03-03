#include <iostream>
#include <thread>

#include "ixwebsocket/IXNetSystem.h"
#include "p2p/websocket/server.h"
#include "p2p/websocket/client.h"


using namespace std;


int main(int argc, char** argv)
{
#ifdef _WIN32
    ix::initNetSystem();
#endif

    P2P::P2PWSServer server;

    thread t1 = server.startServer(12345);

    while(!server.isStarted()) {}

    P2P::P2PWSClient client;

    thread t2 = client.startClient();

    while(!client.isStarted()) {}

    client.send("Haha");
    client.send("Laeuft");


    client.stopClient();

    while(client.isStarted()) {}

    server.stopServer();

    t1.join();
    t2.join();

    return 0;
}