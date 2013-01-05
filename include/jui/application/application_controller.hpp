#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "jui/application/application.hpp"
#include "jui/application/error_stack.hpp"

namespace JUI
{

	/*
	 * Static application controller.
	 */
	class __declspec(dllexport) ApplicationController
	{

	public:

		// Set controlled application.
		template <class Type>
		static bool initialize( HINSTANCE instance );

		// Enter main loop.
		static void main_loop();

		// Exit application.
		static void exit();

		// Get handle.
		static Application* get_application();

	private:

		// Set handle.
		static void set_application( Application* application );

		// Application to be managed.
		static Application* application_;

	};

	/*
	 * Initialize application to be managed.
	 */
	template <class Type>
	bool ApplicationController::initialize( HINSTANCE instance )
	{
#if defined( _DEBUG )
		// Make sure allocation manager is set up.
		JUTIL::AllocationManager* allocation_manager = JUTIL::AllocationManager::get_instance();
		if (allocation_manager == nullptr) {
			MessageBox( nullptr,
				"Failed to create allocation manager!",
				"Application Controller Failure",
				MB_ICONERROR | MB_OK );
		}
#endif

		// Create error stack for application.
		ErrorStack* error_stack = ErrorStack::get_instance();
		if (error_stack == nullptr) {
			MessageBox( nullptr,
				"Failed to create error stack!",
				"Application Controller Failure",
				MB_ICONERROR | MB_OK );
			return false;
		}

		// Create application.
		Type* application;
		if (!JUTIL::BaseAllocator::allocate( &application )) {
			MessageBox( nullptr,
				"Failed to allocate application instance!",
				"Application Controller Failure",
				MB_ICONERROR | MB_OK );
			return false;
		}
		application = new (application) Type( instance );

		// Set application handle.
		set_application( application );

		// Initialize application interfaces.
		Application::ReturnStatus result = application->initialize();
		if (result != Application::Success) {
			const JUTIL::String* top = error_stack->get_top_error();
			MessageBox( nullptr,
				top->get_string(),
				"Application Initialization Failure",
				MB_ICONERROR | MB_OK );
			set_application( nullptr );
			return false;
		}

		return true;
	}

}

#endif // APPLICATION_CONTROLLER_H
