#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "jui/jui_base.hpp"
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

		JUI_API Application( HINSTANCE instance );
		JUI_API virtual ~Application( void );

		// Create interfaces.
		JUI_API virtual ReturnStatus initialize( void );
		JUI_API virtual void clean_up( void );
		JUI_API virtual void exit_application( void );

		// Application singularity/dependency checks.
		JUI_API static unsigned int get_process_count( const char* process_name );

		// Drawing functions.
		JUI_API void draw_frame( void );
		JUI_API void swap_buffers( void );
		JUI_API Window* get_window( void );

		// Main running functions.
		JUI_API virtual ReturnStatus run( void );

		// Input event triggers.
		JUI_API bool trigger_mouse_moved( void );
		JUI_API bool trigger_mouse_clicked( void );
		JUI_API bool trigger_mouse_released( void );
		JUI_API bool trigger_key_pressed( int key );
		JUI_API bool trigger_key_released( int key );

	protected:

		Graphics2D graphics_;
		Window window_;
		Mouse mouse_;
		Keyboard keyboard_;

	};

}

#endif // APPLICATION_HPP
