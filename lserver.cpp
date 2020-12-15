#include "server.hpp"

/* Listening Server
 */
int main(int argc, char* argv[]) {
	// The port number
	int port;

	// If the port was passed throught the command line, it is used
	if (argc == 2) {
		std::string port_string = argv[1];
		port = std::stoi(port_string);
	}

	// Else, the port is prompted for
	else {
		std::cout << "Port: ";
		std::cin >> port;
		std::cin.clear();
		std::cin.ignore(9999, '\n');
	}

	// The server's messenger is initialised
	ServerMessenger messenger(port);

	// The client is waited for
	while (messenger.read() != "ok");

	while (true) {
		std::cout << messenger.read() << '\n';
	}

	return 0;
}