#ifndef WINDOW_HPP
#define WINDOW_HPP

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string/string.hpp>
#include "jui/jui_base.hpp"

namespace JUI
{

	// Prototype for window handling.
	LRESULT CALLBACK wnd_proc( HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam );

	class JUI_API Window
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
		ReturnStatus create_window( void );
		
		// Get window external parameters.
		HWND get_handle( void ) const;
		const JUTIL::String* get_title( void ) const;

		// Setting window display parameters.
		void set_title( const JUTIL::String* title );
		void set_size( int width, int height );
		void set_fullscreen( bool is_fullscreen );
		void set_border( bool has_border );
		void set_icon( WORD icon );

		// Get window display parameters.
		int get_width( void ) const;
		int get_height( void ) const;
		bool is_fullscreen( void ) const;
		bool has_border( void ) const;

		// Window status parameters.
		bool is_active( void );

	private:

		// Creating window class.
		bool register_class( void );

		// Setting window external parameters.
		void set_handle( HWND hwnd );
		void set_instance( HINSTANCE instance );
		HINSTANCE get_instance( void ) const;

	private:

		// Window handle.
		HWND wnd_;

		// Icon data
		WORD icon_;
		bool default_icon_;

		// Window external parameters.
		JUTIL::ConstantString title_;
		HINSTANCE instance_;

		// Window display parameters.
		int width_;
		int height_;
		bool is_fullscreen_;
		bool has_border_;

	};

}

#endif // WINDOW_HPP
