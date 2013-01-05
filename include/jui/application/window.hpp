#ifndef WINDOW_HPP
#define WINDOW_HPP

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string/constant_string.hpp>

namespace JUI
{

	// Prototype for window handling.
	LRESULT CALLBACK wnd_proc( HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam );

	class Window
	{

	public:

		// Window return status.
		enum ReturnStatus
		{
			Success = 0,            // No error.
			RegisterClassFailure,   // Failed to register window class.
			DuplicateWindowFailure, // Window already exists.
			AdjustSizeFailure,      // Failed to adjust window rect.
			CreateWindowFailure,    // Failed to create window.
		};

	public:

		//Class constructor.
		Window( HINSTANCE hInstance );
		~Window( void );

		// Window creation.
		ReturnStatus  create_window( void );
		
		// Get window external parameters.
		HWND		get_handle( void ) const;
		const JUTIL::ConstantString* get_title( void ) const;

		// Setting window display parameters.
		__declspec(dllexport) void set_title( const JUTIL::ConstantString& title );
		__declspec(dllexport) void set_size( int width, int height );
		__declspec(dllexport) void set_fullscreen( bool is_fullscreen );
		__declspec(dllexport) void set_border( bool has_border );

		// Get window display parameters.
		int         get_width( void ) const;
		int         get_height( void ) const;
		bool        is_fullscreen( void ) const;
		bool        has_border( void ) const;

		// Window status parameters.
		bool        is_active( void );

	private:

		// Creating window class.
		bool        register_class( void );

		// Setting window external parameters.
		void        set_handle( HWND hwnd );
		void        set_instance( HINSTANCE instance );
		HINSTANCE   get_instance( void ) const;

	private:

		// Window handle.
		HWND        wnd_;

		// Window external parameters.
		JUTIL::ConstantString title_;
		HINSTANCE instance_;

		// Window display parameters.
		int         width_;
		int         height_;
		bool        is_fullscreen_;
		bool        has_border_;

	};

}

#endif // WINDOW_HPP
