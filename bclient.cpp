#include "client.hpp"

/* Broadcasting Client
 */
int main(int argc, char* argv[]) {
	// The server's IP address and port
	std::string ip_address;
	int port;

	// If commandline arguments were passed, they are used
	if (argc > 1) {
		// The IP address is set
		ip_address = argv[1];

		// If the port was also specified through the command line, it is used
		if (argc == 3) {
			std::string port_string = argv[2];
			port = std::stoi(port_string);
		}

		// Else, the port is requested
		else {
			std::cout << "Port: ";
			std::cin >> port;
			std::cin.clear();
			std::cin.ignore(9999, '\n');
		}
	}

	// Else, the IP address and port are prompted for
	else {
		std::cout << "IP address: ";
		std::getline(std::cin, ip_address);
		std::cout << "Port: ";
		std::cin >> port;
		std::cin.clear();
		std::cin.ignore(9999, '\n');
	}

	ClientMessenger messenger(ip_address, port);

	messenger.send("ok");

	// The server continuously broadcasts messages to the client
	while (true) {
		std::cout << "\nMessage for broadcast:\n";
		std::string broadcast;
		std::getline(std::cin, broadcast);
		messenger.send(broadcast);
	}

	return 0;
}