#ifndef DCDB_CLIENT_H
#define DCDB_CLIENT_H

#include "boost/asio.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace P2P {
    class Client
    {
    public:
        Client(string address, int port);
        ~Client();
        bool connect();
        void send(string message);
        bool isStarted();
        void disconnect();

    private:
        bool _startClient();
        tcp::endpoint *endpoint;
        io_service *ioService;
        tcp::socket *socket;
    };
}

#endif //DCDB_CLIENT_H
