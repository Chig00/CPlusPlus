#include <iostream>
#include <limits>
#include "sdlnet.hpp"

// The message that indicates that the connection should be closed.
constexpr const char* QUIT_COMMAND = "/quit";

/**
 * Broadcasts or listens to the other messenger.
 */
void communicate(const Messenger& messenger, bool mode) noexcept {
	// Broadcast
	if (mode) {
		std::cout
			<< "\nBroadcast ("
			<< QUIT_COMMAND
			<< " to quit):\n"
		;
		
		// Loop to continuously send input.
		while (true) {
			// The message is formed from user input.
			std::string message;
			std::getline(std::cin, message);
			
			// The message is sent.
			messenger.send(message);
			
			// If the quit command was inputted, the program terminates.
			if (message == QUIT_COMMAND) {
				return;
			}
		}
	}
	
	// Receive
	else {
		std::cout << "\nReceived:\n";
		
		// Loop to continuously receive input.
		while (true) {
			// The message is received.
			std::string message(messenger.read());
			
			// If the quit command was received, the program terminates.
			if (message == QUIT_COMMAND) {
				std::cout << "\nConnection Terminated.\n";
				return;
			}
		
			// Else, the message is displayed.
			else {
				std::cout << message << std::endl;
			}
		}
	}
}

/**
 * Allows one to message another device using a TCP connection.
 */
int main(int argc, char** argv) noexcept {
	// Initialises SDL and Net Utilities for networking.
	System::initialise(System::NONE, System::NET);
	
	// Displays the SDL and Net Utilities version used.
	std::cout
		<< std::endl
		<< System::info()
		<< std::endl
	;
	
	// The address and port.
	std::string address;
	int port = -1;
	int broadcast = -1;
	
	// The server host was given.
	if (argc > 1) {
		address = argv[1];
		
		// The port number was given.
		if (argc > 2) {
			port = std::stoi(argv[2]);
			
			// The mode was given.
			if (argc > 3) {
				// Broadcast
				if (std::string(argv[3]) == "b") {
					broadcast = 1;
				}
				
				// Receive
				else if (std::string(argv[3]) == "r") {
					broadcast = 0;
				}
				
				// Invalid
				else {
					std::cerr << "\nInvalid mode.\n";
					
					return -1;
				}
			}
		}
	}
	
	// No address was passed as a command line argument.
	if (address == "") {
		// The mode is prompted for.
		std::cout << "\nServer (s) or Client (c)? ";
		std::getline(std::cin, address);
		
		// Server
		if (address == "s") {
			address = "server";
		}
		
		// Client
		else if (address == "c") {
			std::cout << "\nHost Address: ";
			std::getline(std::cin, address);
		}
		
		// Invalid
		else {
			std::cerr << "\nInvalid mode.\n";
			
			return -1;
		}
	}
	
	// No port number was passed as a command line argument.
	if (port < 0) {
		// The port number is prompted for.
		std::cout << "\nPort: ";
		std::cin >> port;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	// No mode was passed as a command line argument.
	if (broadcast < 0) {
		// The port number is prompted for.
		std::cout << "\nBroadcast (b) or Receive (r): ";
		std::string mode;
		std::getline(std::cin, mode);
		
		// Broadcast
		if (mode == "b") {
			broadcast = 1;
		}
		
		// Receive
		else if (mode == "r") {
			broadcast = 0;
		}
		
		// Invalid
		else {
			std::cerr << "\nInvalid mode.\n";
			
			return -1;
		}
	}
	
	// Server
	if (address == "server") {
		std::cout << "\nWaiting for the client...\n";
		communicate(Server(port), broadcast);
	}
	
	// Client
	else {
		try {
			communicate(Client(address, port), broadcast);
		}
		
		catch (const std::exception& exception) {
			std::cerr
				<< std::endl
				<< exception.what()
				<< std::endl
			;
		}
	}
	
	// Terminates SDL and Net Utilities.
	System::terminate();
	return 0;
}