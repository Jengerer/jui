#ifndef APPLICATION_H
#define APPLICATION_H

#include "jui/container.h"
#include "jui/graphics_2d.h"
#include "jui/imouse_handler.h"
#include "jui/ikeyboard_handler.h"
#include "jui/keyboard.h"
#include "jui/mouse.h"
#include "jui/window.h"

// Main class that's the base of all applications.
class Application: public Container, public IMouseHandler, public IKeyboardHandler
{
public:

	__declspec(dllexport) Application( HINSTANCE instance );
	__declspec(dllexport) virtual ~Application( void );

	// Create interfaces.
	__declspec(dllexport) virtual void	load_interfaces( void );
	__declspec(dllexport) virtual void	close_interfaces( void );
	__declspec(dllexport) void			exit_application( void );

	// Application singularity/dependency checks.
	static __declspec(dllexport) unsigned int get_process_count( const char* process_name );

	// Drawing functions.
	__declspec(dllexport) void			draw_frame( void );
	__declspec(dllexport) Window*		get_window( void ) const;

	// Main running functions.
	__declspec(dllexport) virtual void	run( void );

	// Input event triggers.
	void			trigger_mouse_events( void );
	void			trigger_mouse_moved( void );
	void			trigger_mouse_clicked( void );
	void			trigger_mouse_released( void );
	void			trigger_key_pressed( int key );
	void			trigger_key_released( int key );

protected:

	Graphics2D*		graphics_;
	Window*			window_;
	Mouse*			mouse_;
	Keyboard		keyboard_;

};

#endif // APPLICATION_H