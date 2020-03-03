#include <iostream>
#include <thread>

#include "ixwebsocket/IXNetSystem.h"
#include "p2p/websocket/client.h"
#include "p2p/P2PNode.h"


using namespace std;


int main(int argc, char** argv)
{
#ifdef _WIN32
    ix::initNetSystem();
#endif
    P2P::P2PNode node(12345);

    bool started = node.start();

    if (!started) {
        return -1;
    }
    P2P::P2PWSClient client;

    thread t2 = client.startClient();

    while(!client.isStarted()) {}

    client.send("Haha");
    client.send("Laeuft");

    client.stopClient();

    while(client.isStarted()) {}

    node.stop();

    t2.join();

    return 0;
}