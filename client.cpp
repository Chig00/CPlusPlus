#include <iostream>
#include <boost/asio.hpp>
#include <string>

/* Manages the messages for the client
 */
class ClientMessenger {
    public:
        /* Initialises the messenger
         */
        ClientMessenger(std::string ip_address) {
            io_service = new boost::asio::io_service;
            socket = new boost::asio::ip::tcp::socket(*io_service);
            socket->connect(
                boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::address::from_string(ip_address), 1234
                )
            );
        }

        /* Frees the memory allocated for the socket and IO service
         */
        ~ClientMessenger() {
            delete socket;
            delete io_service;
        }

        /* Reads a message from the server
         */
        std::string read() {
            boost::asio::streambuf buf;
            boost::asio::read_until(*socket, buf, "\0");
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());
            return data;
        }

        /* Sends a message to the server
         */
        void send(std::string message) {
            boost::asio::write(*socket, boost::asio::buffer(message));
        }

    private:
        // Objects for networking
        boost::asio::io_service* io_service;
        boost::asio::ip::tcp::socket* socket;
        // Stores the error code for operations
        boost::system::error_code error;
};

int main(int argc, char* argv[]) {
    std::string* ip_address;

    if (argc == 2) {
        ip_address = new std::string(argv[1]);
    }

    else {
        ip_address = new std::string;
        std::cout << "Server's IP address: ";
        std::getline(std::cin, *ip_address);
    }

    // The messenger is initialised
    ClientMessenger messenger(*ip_address);

    while (true) {
        // A message is sent to the server
        std::cout << "\nMessage to the server:\n";
        std::string message;
        std::getline(std::cin, message);
        messenger.send(message);

        // A message, from the server, is read
        std::cout << "\nMessage from the server:\n" << messenger.read() << '\n';
    }

    delete ip_address;

    return 0;
}