#pragma once

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