#include <iostream>
#include "sdlandnet.hpp"

// The number of arguments that should be passed.
constexpr int ARGUMENTS = 4;

/**
 * Hosts a one-way server bridge at two ports for connecting two clients.
 * Takes 3 command line arguments.
 * The first should be the port that the source client should connect to.
 * The second should be the port that the destination client should connect to.
 * The third should be the string that, when sent, terminates this program.
 */
int main(int argc, char** argv) {
	// The program will not run, unless the command line argument are passed.
	if (argc != ARGUMENTS) {
		std::cerr << "\nInvalid argument count.\n";
		return -1;
	}
	
	// The system is intialised for networking.
	System::initialise(System::NET);
	
	{
		// The source and destination servers are intialised in another
		//   thread, such that the clients may connect in any order.
		bool dummy = false;
		std::unique_ptr<Server> source;
		std::unique_ptr<Server> destination;
		ServerPackage source_package(source, dummy, std::stoi(argv[1]));
		ServerPackage destination_package(destination, dummy, std::stoi(argv[2]));
		Thread source_thread(ServerPackage::make_server, &source_package);
		Thread destination_thread(ServerPackage::make_server, &destination_package);
		
		// Waits for both clients to connect.
		while (!source || !destination);
		
		// The one way bridge is formed and will last until
		//   the terminator string is sent from the source.
		// The terminator string is still sent to the destination before termination.
		ClientPackage package(*source, *destination, argv[3]);
		Thread thread(ClientPackage::make_bridge, &package);
	}
	
	// The sytem is terminated.
	System::terminate();
	return 0;
}