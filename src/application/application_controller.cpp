#include "jui/application/application_controller.hpp"
#include "jui/application/error_stack.hpp"

const JUTIL::ConstantString DEFAULT_LEAKS_OUTPUT_FILE = "memory_leaks.txt";

namespace JUI
{

	// Define static member.
	Application* ApplicationController::application_ = nullptr;

	/*
	 * Enter the main program loop.
	 */
	void ApplicationController::main_loop( void )
	{
		// Error stack for reporting.
		ErrorStack* stack = ErrorStack::get_instance();

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
			Application::ReturnStatus status = application_->run();
			if (status != Application::Success) {
				const JUTIL::String* error = stack->get_top_error();
				MessageBox( NULL, error->get_string(), "Application Error", MB_OK | MB_ICONERROR );
			}
		}
	}

	/*
	 * Exit running application.
	 */
	void ApplicationController::exit()
	{
		// Kill application.
		JUTIL::BaseAllocator::destroy( application_ );
		set_application( nullptr );

		// Destroy error stack.
		ErrorStack::shut_down();

		// Write leaks to file.
		JUTIL::AllocationManager* allocation_manager = JUTIL::AllocationManager::get_instance();
		if (allocation_manager != nullptr) {
			allocation_manager->dump_leaks( DEFAULT_LEAKS_OUTPUT_FILE.get_string() );
			JUTIL::AllocationManager::shut_down();
		}
	}

	/*
	 * Get application handle.
	 */
	Application* ApplicationController::get_application( void )
	{
		return application_;
	}

	/*
	 * Set application handle.
	 */
	void ApplicationController::set_application( Application* application )
	{
		JUTIL::JUTILBase::debug_assert( application == nullptr || application_ == nullptr );
		application_ = application;
	}

}
