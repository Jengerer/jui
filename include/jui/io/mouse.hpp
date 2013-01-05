#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "jui/application/window.hpp"
#include "jui/layout/component.hpp"

namespace JUI
{

	enum MouseEvent {
		MOUSE_EVENT_LEFT_CLICK,
		MOUSE_EVENT_LEFT_RELEASE,
		MOUSE_EVENT_RIGHT_CLICK,
		MOUSE_EVENT_RIGHT_RELEASE,
		MOUSE_EVENT_MOVE
	};

	enum MouseCursor {
		MOUSE_CURSOR_ARROW,
		MOUSE_CURSOR_FINGER,
		MOUSE_CURSOR_HAND
	};

	class Mouse
	{

	public:

		__declspec(dllexport) Mouse( Window* window );

		// Mouse control and settings.
		__declspec(dllexport) void set_window( Window* window );
		__declspec(dllexport) void poll();

		// State getter.
		__declspec(dllexport) void set_pressed( bool is_pressed );
		__declspec(dllexport) bool is_pressed() const;

		// Position functions.
		__declspec(dllexport) int get_x( void ) const;
		__declspec(dllexport) int get_y( void ) const;

		// Call to components.
		__declspec(dllexport) bool is_touching( const Component* component ) const;

	private:

		bool is_pressed_;
		Window* window_;
		POINT   position_;

	};

}

#endif // MOUSE_HPP
