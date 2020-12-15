#include <iostream>
#include <boost/asio.hpp>
#include <string>

/* Manages messages for the server
 */
class ServerMessenger {
    public:
        /* Initialises the server at localhost:1234
         */
        ServerMessenger() {
            // The IO Service is initialised
            io_service = new boost::asio::io_service;

            // A new connection is listed for
            acceptor = new boost::asio::ip::tcp::acceptor(
                *io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)
            );

            // A socket is created
            socket = new boost::asio::ip::tcp::socket(*io_service);

            // A connection is waited for
            acceptor->accept(*socket);

        }

        /* Frees the memory allocated to the socket, acceptor, and IO service
         */
        ~ServerMessenger() {
            delete socket;
            delete acceptor;
            delete io_service;
        }

        /* Reads a message from the client
         */
        std::string read() {
            boost::asio::streambuf buf;
            boost::asio::read_until(*socket, buf, "\0");
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());
            return data;
        }

        /* Sends a message to the client
         */
        void send(std::string message) {
            boost::asio::write(*socket, boost::asio::buffer(message));
        }

    private:
        // Networking objects
        boost::asio::io_service* io_service;
        boost::asio::ip::tcp::acceptor* acceptor;
        boost::asio::ip::tcp::socket* socket;
};

int main() {
    // The messenger is initialised
    ServerMessenger messenger;

    while (true) {
        // The message, from the client, is read
        std::cout << "\nMessage from the client:\n" << messenger.read() << '\n';

        // A message is sent to the client
        std::cout << "\nMessage to the client:\n";
        std::string message;
        std::getline(std::cin, message);
        messenger.send(message);
    }

    return 0;
}