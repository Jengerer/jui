#include "jui/application/window.hpp"
#include "jui/application/application_controller.hpp"
#include "jui/application/error_stack.hpp"

namespace JUI
{

	// Default window parameters.
	const JUTIL::ConstantString DEFAULT_TITLE = "Default Application";
	const int DEFAULT_WIDTH = 640;
	const int DEFAULT_HEIGHT = 480;
	const bool DEFAULT_FULLSCREEN = false;
	const bool DEFAULT_BORDER = true;

	/*
	 * Handles window messages.
	 */
	LRESULT CALLBACK wnd_proc( HWND wnd, UINT message, WPARAM wparam, LPARAM lparam )
	{
		// Get application handle.
		Application* application = ApplicationController::get_application();

		switch (message) {
		case WM_KEYDOWN:
			application->trigger_key_pressed( LOWORD( wparam ) );
			break;

		case WM_KEYUP:
			application->trigger_key_released( LOWORD( wparam ) );
			break;

		case WM_LBUTTONDOWN:
			application->trigger_mouse_clicked();
			break;

		case WM_LBUTTONUP:
			application->trigger_mouse_released();
			break;

		case WM_CLOSE:
		case WM_DESTROY:
			application->exit_application();
			return 0;
			break;
		}

		return DefWindowProc( wnd, message, wparam, lparam );
	}

	/*
	 * Window constructor.
	 */
	Window::Window( HINSTANCE instance )
	{
		// Null window handle.
		set_handle( nullptr );

		// Set default parameters.
		set_title( &DEFAULT_TITLE );
		set_instance( instance );
		set_size( DEFAULT_WIDTH, DEFAULT_HEIGHT );
		set_fullscreen( DEFAULT_FULLSCREEN );
		set_border( DEFAULT_BORDER );
		default_icon_ = true;
	}

	/*
	 * Window destructor.
	 */
	Window::~Window( void )
	{
		// Window has been destroyed.
	}

	/*
	 * Registers and creates the window.
	 */
	Window::ReturnStatus Window::create_window( void )
	{
		// Check for repeated creations.
		if (get_handle() != nullptr) {
			ErrorStack::get_instance()->log( "Window: window already created." );
			return DuplicateWindowFailure;
		}

		// Register window class.
		if (!register_class()) {
			ErrorStack::get_instance()->log( "Window: failed to register window class." );
			return RegisterClassFailure;
		}

		// Get screen resolution to center window.
		RECT screen;
		GetWindowRect( GetDesktopWindow(), &screen );

		// Adjust bounds based on style.
		RECT windowRect;
		windowRect.left	= 0;
		windowRect.top = 0;
		windowRect.right = get_width();
		windowRect.bottom = get_height();

		// Adjust size for style.
		DWORD display_style = (is_fullscreen() || !has_border() ? WS_POPUP : WS_CAPTION | WS_SYSMENU);
		if (!AdjustWindowRect( &windowRect, display_style, false )) {
			ErrorStack::get_instance()->log( "Window: failed to adjust window rectangle." );
			return AdjustSizeFailure;
		}

		// Create window.
		HWND wnd = CreateWindow(
			title_.get_string(), title_.get_string(),
			display_style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowRect.right - windowRect.left, 
			windowRect.bottom - windowRect.top,
			NULL, NULL,
			get_instance(),
			NULL );
		if (wnd == nullptr) {
			ErrorStack::get_instance()->log( "Window: failed to create window." );
			return CreateWindowFailure;
		}

		// Display window.
		ShowWindow( wnd, SW_NORMAL );
		UpdateWindow( wnd );

		// Set window handle.
		set_handle( wnd );
		return Success;
	}

	/*
	 * Sets the window handle.
	 */
	HWND Window::get_handle( void ) const
	{
		return wnd_;
	}

	/*
	 * Gets the window title.
	 */
	const JUTIL::String* Window::get_title( void ) const
	{
		return &title_;
	}

	/*
	 * Sets the window title.
	 */
	void Window::set_title( const JUTIL::String* title )
	{
		title_.set_string( title );
	}

	/*
	 * Sets the window size.
	 */
	void Window::set_size( int width, int height )
	{
		width_ = width;
		height_ = height;
	}

	/*
	 * Sets the window fullscreen mode.
	 */
	void Window::set_fullscreen( bool is_fullscreen )
	{
		is_fullscreen_ = is_fullscreen;
	}

	/*
	 * Sets the window border mode.
	 */
	void Window::set_border( bool has_border )
	{
		has_border_ = has_border;
	}
		
	/*
	 * Sets the window icon.
	 */
	void Window::set_icon( WORD icon )
	{
		icon_ = icon;
		default_icon_ = false;
	}

	/*
	 * Gets the width of the window.
	 */
	int Window::get_width( void ) const
	{
		return width_;
	}

	/*
	 * Gets the height of the window.
	 */
	int Window::get_height( void ) const
	{
		return height_;
	}

	/*
	 * Checks if the window is in fullscreen mode.
	 */
	bool Window::is_fullscreen( void ) const
	{
		return is_fullscreen_;
	}

	/*
	 * Checks if the window has a border.
	 */
	bool Window::has_border( void ) const
	{
		return has_border_;
	}

	/*
	 * Returns if the window is currently in user focus.
	 */
	bool Window::is_active( void )
	{
		return GetFocus() == get_handle();
	}

	/*
	 * Register the window class.
	 */
	bool Window::register_class( void )
	{
		WNDCLASS wnd_class;
		wnd_class.hInstance     = get_instance();
		if( default_icon_ ){
			wnd_class.hIcon     = NULL;
		}else{
			wnd_class.hIcon     = LoadIcon( get_instance(), MAKEINTRESOURCE(101) );
		}
		wnd_class.hCursor       = LoadCursor( NULL, IDC_ARROW );
		wnd_class.hbrBackground = NULL;
		wnd_class.cbWndExtra    = 0;
		wnd_class.cbClsExtra    = 0;
		wnd_class.lpfnWndProc   = wnd_proc;
		wnd_class.lpszClassName = title_.get_string();
		wnd_class.lpszMenuName  = NULL;
		wnd_class.style         = CS_OWNDC;

		return RegisterClass( &wnd_class ) != 0;
	}

	void Window::set_handle( HWND hwnd )
	{
		wnd_ = hwnd;
	}

	void Window::set_instance( HINSTANCE instance )
	{
		instance_ = instance;
	}

	HINSTANCE Window::get_instance( void ) const
	{
		return instance_;
	}

}
