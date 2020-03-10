#include <iostream>
#include <p2p/tcpsocket/server.h>
#include "p2p/tcpsocket/client.h"

void onAccpet(string address, int port, string message);

using namespace std;

class test {
public:
    void onAccpet(string address, int port, string message) {
        cout << "New Connection:\n\tPort: " << port << "\n\tAddress: " << address << endl;
        //boost::asio::streambuf buf;
        //boost::asio::read(new_socket, buf);
        //string data = boost::asio::buffer_cast<const char*>(buf.data());
        //cout << data;
    }
};

int main(int argc, char **argv) {
    test *t = new test();
    P2P::Server server(12345);
    P2P::Client client("0.0.0.0", 12345);
    P2P::Client client2("0.0.0.0", 12345);
    bool serverStarted = server.start(&test::onAccpet, t);
    bool success = client.connect();
    bool success2 = client2.connect();
    sleep(2);
}