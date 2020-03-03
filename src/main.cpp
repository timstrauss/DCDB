#include <iostream>
#include <thread>
#include <unistd.h>

#include "p2p/websocket/server.h"
#include "p2p/websocket/client.h"


using namespace std;


int main(int argc, char** argv)
{
    P2P::Server server;

    thread t1 = server.startServer(12345);

    while(!server.isStarted()) {}

    P2P::Client client;

    thread t2 = client.startClient();

    while(!client.isStarted()) {}

    client.send("Haha");
    client.send("Läuft");

    client.stopClient();

    while(client.isStarted()) {}

    server.stopServer();

    t1.join();
    t2.join();

    return 0;
}