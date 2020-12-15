// This is a subset of sdlandnet.hpp for networking only.
#include <string>
#include <sstream>
#include <ctime>
#include <SDL.h>
#include <SDL_net.h>

/**
 * A namespace for initialisation and shutdown functions.
 */
namespace System {
	// The current version of the library.
	constexpr int VERSION[] = {1, 1, 4, 0};
	constexpr int VERSION_LENGTH = 4;
	
	// BasicRenderer::LETTERS + BasicRenderer::NUMBERS
	constexpr int RENDERER = 36;
	
	// For use with the initialise() function
	constexpr int NONE = 0;
	constexpr int VIDEO = SDL_INIT_VIDEO;
	constexpr int AUDIO = SDL_INIT_AUDIO;
	constexpr bool NET = true;
	
	/**
	 * Returns the version in string form.
	 */
	std::string version(
		const int* version = VERSION,
		int version_length = VERSION_LENGTH
	) noexcept {
		std::stringstream stream;
		
		for (int i = 0; i < version_length; i++) {
			stream << version[i];
			
			if (i < version_length - 1) {
				stream << '.';
			}
		}
		
		return stream.str();
	}
	
	/**
	 * Returns a string of information about this library.
	 */
	std::string info() noexcept {
		std::stringstream stream;
		stream
			<< "SDL and SDL Net utilities by Chigozie Agomo.\nVersion: "
			<< version()
		;
		
		return stream.str();
	}
	
	/**
	 * Initialises SDL with the given flags.
	 * Optionally intialises SDL_net.
	 */
	void initialise(int flags = VIDEO, bool init_net = false) noexcept {
		SDL_Init(flags);
		
		if (init_net) {
			SDLNet_Init();
		}
	}

	/**
	 * Shutdowns SDL_net and SDL.
	 */
	void terminate() noexcept {
		SDLNet_Quit();
		SDL_Quit();
	}

	/**
	 * Sends the given command to the command line.
	 */
	void command(const std::string& command_string) noexcept {
		system(command_string.c_str());
	}
}

/**
 * A namespace for time related functions.
 */
namespace Timer {
	/**
	 * Returns the time in seconds elapsed since the epoch.
	 */
	int current() noexcept {
		return time(NULL);
	}
	
	/**
	 * Returns the time in seconds.
	 * All times returned are relative to each other.
	 */
	double time() noexcept {
		return static_cast<double>(clock()) / CLOCKS_PER_SEC;
	}

	/**
	 * Halts all functionality in the thread for the
	 *   specified amount of time (in seconds).
	 */
	void wait(double seconds) noexcept {
		double now = time();
		while (time() < now + seconds);
	}
}

/**
 * An abstract class for the two types of TCP messengers
 *   to inherit from.
 * This class cannot and should not be instantiated.
 */
class Messenger {
	public:
		/**
		 * Sends the string passed to the other messenger.
		 */
		void send(const std::string& message) const noexcept {
			SDLNet_TCP_Send(socket, message.c_str(), message.length() + 1);
		}
		
		/**
		 * Receives a string from the other messenger.
		 * A maximum number of bytes, equal to buffer_size, is read.
		 * Uses C-style strings internally, so buffer_size,
		 *   should be one greater than the length of the string sent.
		 */
		std::string read(int buffer_size = 1000) const noexcept {
			char* buffer = new char[buffer_size];
			SDLNet_TCP_Recv(socket, buffer, buffer_size);
			std::string message(buffer);
			delete[] buffer;
			return message;
		}

	protected:
		Messenger() {}    // This is an abstract base class.
		TCPsocket socket; // The TCP socket used for the connection.
};

/**
 * A Messenger subclass for the server.
 */
class Server: public Messenger {
	public:
		/**
		 * Constructs a new TCP messenger for the server.
		 * The server is hosted at localhost:[port].
		 */
		Server(int port) noexcept {
			IPaddress ip_address;
			SDLNet_ResolveHost(&ip_address, nullptr, port);
			server = SDLNet_TCP_Open(&ip_address);
			while (!(socket = SDLNet_TCP_Accept(server)));
		}
		
		/**
		 * Closes the TCP sockets associated with the messenger.
		 */
		~Server() noexcept {
			SDLNet_TCP_Close(socket);
			SDLNet_TCP_Close(server);
		}
		
	private:
		TCPsocket server; // The TCP socket used for to accept the client.
};

/**
 * A Messenger subclass for the client.
 */
class Client: public Messenger {
	public:
		/**
		 * Constructs a new TCP messenger for the client.
		 * The client connects to the server at [address]:[port].
		 */
		Client(const std::string& address, int port) {
			IPaddress ip_address;
			
			// The constructor throws if the the server cannot be connected to.
			if (
				SDLNet_ResolveHost(&ip_address, address.c_str(), port)
				|| !(socket = SDLNet_TCP_Open(&ip_address))
			) {
				throw std::runtime_error("The host address could not be resolved.");
			}
		}
		
		/**
		 * Closes the TCP socket associated with the messenger.
		 */
		~Client() noexcept {
			SDLNet_TCP_Close(socket);
		}
};

/* CHANGELOG
     v0.1:
	   Added the Messenger, Server, Client, Sprite, Display, and Audio classes.
	   Added the Colour enumeration.
	   Added the sdl_init(), sdl_quit(), get_time(), and wait() functions.
	 v0.2:
	   Added the System, Timer, and Events namespaces.
	   Renamed sdl_init() to initialised() and moved it to the System namespace.
	   Renamed sdl_quit() to terminate() and moved it to the System namespace.
	   Renamed get_time() to time() and moved to to the Timer namespace.
	   Moved wait() to the Timer namespace.
	 v0.3:
	   Added the Point and Rectangle classes.
	   Changed Sprite::fill() from using SDL_Rect to using Rectangle.
	 v0.3.2:
	   Added the System::version() and System::info() methods.
	 v0.4:
	   Added the Thread class.
	 v0.5:
		Added the Shape, Circle, and Button classes.
		Made Rectangle a derived class of Shape.
		Moved Rectangle::click() and Rectangle::unclick() to Shape.
		Added the Circle overloads of the Sprite::fill() methods.
		Deprecated the Thread class.
	 v0.6:
	   Added the Renderer class.
	 v0.6.1:
	   Changed the Sprite and Display classes to no longer be copiable.
	 v0.6.1.1:
	   Fixed Renderer::render().
	 v0.6.2:
	   Added Sprite::destroy_surface() and Display::destroy_window().
	   Fixed a memory leak in move assignment and construction of Sprite and Display objects.
	 v0.6.3:
	   Added the changelog.
	 v0.6.4:
	   Added the System::command() function.
	 v0.6.4.1:
	   Changed LETTERS and NUMBERS from macros to constant expressions.
	 v0.6.4.2:
	   Added warnings for Events::unclick() and Shape::unclick().
	 v.0.6.4.3:
	   Changed SDL_AND_NET_VERSION from const to constexpr.
	   Changed Sprite::BYTE_ORDER from const to constexpr.
	   Change Sprite::SURFACE_DEPTH from const to constexpr.
	 v0.6.5:
	   Changed the Renderer class to use std::array.
	   Changed the Renderer class to be templated.
	   Made Renderer::load_sprites() private.
	   Added the const version of Display::get_sprite().
	 v0.6.5.1:
	   Fixed Renderer::load_numbers() and Renderer::load_letters().
	 v0.6.6:
	   Added a Sprite::blit() overload for Rectangle.
	   Added the const version of Button::get_sprite().
	 v0.6.7:
	   Added the Rectangle::set() method that uses a sprite template.
	 v0.7:
	   Removed the Thread class.
	   Made Audio instances non-copiable, but movable.
	   Added Audio::queuable().
	 v0.8:
	   Restored the Thread class with no deprecation status.
	   Made the Thread class non-copiable, but movable.
	 v0.8.1:
	   Added the Rectangle default constructor.
	 v0.8.2:
	   Added the Timer::cureent() function.
	 v0.8.3:
	   Added the const version of Button::get_rectangle().
	 v0.8.4:
	   Added aliases for common scancodes in Events.
	   Converted System::VIDEO and System::AUDIO to constant expressions.
	   Converted Events::LEFT_CLICK, Events::MIDDLE_CLICK,
	     and Events::RIGHT_CLICK to constant expressions.
	 v0.8.5:
	   Made System::version() generic.
	 v1:
	   Added default arguments to multiple class constructors.
	   Added default arguments to some functions and methods.
	   Display's constructors no longer produce fullscreen windows.
	   Renderer now simply ignores invalid characters.
	   All functions and methods have been marked as noexcept.
	 v1.0.0.1:
	   Fixed a typo in System::info().
	 v1.0.0.2:
	   Fixed Point and Rectangle's integer constructors.
	 v1.0.1:
	   Moved SDL_AND_NET_VERSION and SDL_AND_NET_VERSION_LENGTH to System.
	   Renamed SDL_AND_NET_VERSION to VERSION.
	   Renamed SDL_AND_NET_VERSION_LENGTH to VERSION_LENGTH.
	   Moved LETTERS and NUMBERS to Renderer.
	   Added the Point::click() and Point::unclick() methods.
	   Changed the functionality of Shape::unclick() to be more intuitive.
	   Added the System::RENDERER constant.
	 v1.1:
	   Renamed Renderer to BasicRenderer.
	   Added the Renderer Abstract Base Class.
	   BasicRenderer inherits from Renderer.
	   Added the FullRenderer subclass of Renderer.
	   Added the Renderer::lined_render() method.
	   Renderer::render() can now optionally specify the
	     separation between characters.
	   Added GREY to Colour.
	   Updated Sprite::fill() methods to use GREY.
	 v1.1.1:
	   Moved Colour into Sprite.
	   Added the Sprite copy constructor and assignment operator.
	 v1.1.2:
	   Added Display constructors for ratios of the display size.
	 v1.1.3:
	   The constructor of the Client class can now throw,
	     if the host address could not be resolved.
	   System::info() is no longer prepended and terminated with a new line.
	   Add the System::NONE and System::NET constant expressions.
	   Sprite::operator=() now correctly returns the sprite.
	 v1.1.4:
	   Added Audio::dequeue().
 */