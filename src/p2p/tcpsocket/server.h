#ifndef DCDB_SERVER_H
#define DCDB_SERVER_H

#include <iostream>
#include "boost/asio.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace P2P {
    class Server
    {
    public:
        Server(int port);
        ~Server();
        template <class T> bool start(void (T::*onAccept)(string address, int port, string message), T *onInstance) {
            try {
                if (!listening) {
                    acceptor->listen();
                    listening = true;
                }
                acceptor->async_accept([this, onAccept, onInstance](error_code ec, tcp::socket &&new_socket) {
                    if (!ec) {
                        int port = new_socket.remote_endpoint().port();
                        string address = new_socket.remote_endpoint().address().to_string();
                        thread(onAccept, onInstance, address, port, "").detach();
                    }
                    start(onAccept, onInstance);
                });
                socket->async_read_some(buffer(bytes), [this, onAccept, onInstance](const error_code &ec, size_t bytes_transferred){
                    cout.write(bytes.data(), bytes_transferred);
                });
            } catch (const std::exception &e) {
                listening = false;
                cerr << e.what() << endl;
                return false;
            }
            return true;
        }
        void stop();


    private:
        std::array<char, 4096> bytes;
        io_service *ioService;
        tcp::endpoint *endpoint;
        tcp::acceptor *acceptor;
        tcp::socket *socket;
        io_service::work *work;
        thread ioThread;
        bool listening = false;
    };
}

#endif //DCDB_SERVER_H
