#include "application_controller.h"

// Define static member.
Application* ApplicationController::application_ = nullptr;

/*
 * Initialize application to be managed.
 */
void ApplicationController::initialize( Application* application )
{
	try {
		// Set new handle.
		set_application( application );

		// Initialize application interfaces.
		application->load_interfaces();
	}
	catch (const std::runtime_error& ex) {
		MessageBox( NULL, ex.what(), "Application controller initialization failed!", MB_OK );
	}
}

/*
 * Enter the main program loop.
 */
void ApplicationController::main_loop()
{
	// Enter main program loop.
	MSG msg;
	bool running = true;
	while (running) {
		// Check for Windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Don't dispatch if quitting.
			if (msg.message == WM_QUIT) {
				running = false;
			}
			else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		// Run frame.
		get_application()->run();
	}
}

/*
 * Exit running application.
 */
void ApplicationController::exit()
{
	// Delete application.
	delete get_application();
	set_application( nullptr );
}

/*
 * Get application handle.
 */
Application* ApplicationController::get_application()
{
	return application_;
}

/*
 * Set application handle.
 */
void ApplicationController::set_application( Application* application )
{
	// Can't replace existing with non-null.
	if (get_application() != nullptr && application != nullptr) {
		throw new std::runtime_error( "Another application is already being managed." );
	}

	// Just set.
	application_ = application;
}