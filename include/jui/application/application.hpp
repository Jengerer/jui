#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "jui/layout/container.hpp"
#include "jui/gfx/graphics_2d.hpp"
#include "jui/io/mouse_handler_interface.hpp"
#include "jui/io/keyboard_handler_interface.hpp"
#include "jui/io/keyboard.hpp"
#include "jui/io/mouse.hpp"
#include "jui/application/window.hpp"

namespace JUI
{

	// Main class that's the base of all applications.
	class Application: public Container, public MouseHandlerInterface, public KeyboardHandlerInterface
	{

	public:

		// Return code for application functions.
		enum ReturnStatus
		{
			Success = 0,

			// Notice to exit without error.
			EarlyExit,

			// Initialization/loading results.
			WindowCreateFailure,
			GraphicsInitializeFailure,
			PrecacheResourcesFailure,

			// Input handling results.
			MouseHandlingFailure,
			KeyboardHandlingFailure,

			// Generic running results.
			NoMemoryFailure,
			RunFailure,
		};

	public:

		__declspec(dllexport) Application( HINSTANCE instance );
		__declspec(dllexport) virtual ~Application( void );

		// Create interfaces.
		__declspec(dllexport) virtual ReturnStatus initialize( void );
		__declspec(dllexport) virtual void clean_up( void );
		__declspec(dllexport) virtual void exit_application( void );

		// Application singularity/dependency checks.
		static __declspec(dllexport) unsigned int get_process_count( const char* process_name );

		// Drawing functions.
		__declspec(dllexport) void draw_frame( void );
		__declspec(dllexport) void swap_buffers( void );
		__declspec(dllexport) Window* get_window( void );

		// Main running functions.
		__declspec(dllexport) virtual ReturnStatus run( void );

		// Input event triggers.
		bool trigger_mouse_moved( void );
		bool trigger_mouse_clicked( void );
		bool trigger_mouse_released( void );
		bool trigger_key_pressed( int key );
		bool trigger_key_released( int key );

	protected:

		Graphics2D graphics_;
		Window window_;
		Mouse mouse_;
		Keyboard keyboard_;

	};

}

#endif // APPLICATION_HPP
