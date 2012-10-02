#include "jui/application/application_controller.hpp"
#include "jui/application/error_stack.hpp"

namespace JUI
{

    // Define static member.
    Application* ApplicationController::application_ = nullptr;

    /*
     * Initialize application to be managed.
     */
    bool ApplicationController::initialize( Application* application )
    {
        // Create error stack for application.
        ErrorStack* error_stack = ErrorStack::get_instance();
        if (error_stack == nullptr) {
            MessageBox( nullptr,
                "Application controller: failed to create error stack.",
                "Application controller failure!",
                MB_ICONERROR | MB_OK );
        }

        // Set application handle.
        set_application( application );

        // Initialize application interfaces.
        Application::ReturnStatus result = application->load_interfaces();
        if (result != Application::Success) {
            JUTIL::ConstantString error( "Application controller: unlogged error." );
            const JUTIL::String* top = error_stack->get_top_error();
            if (top != nullptr) {
                error = *top;
            }
            MessageBox( nullptr,
                top->get_string(),
                "Application controller: initialize failed.",
                MB_ICONERROR | MB_OK );
            set_application( nullptr );
            return false;
        }

        return true;
    }

    /*
     * Enter the main program loop.
     */
    void ApplicationController::main_loop( void )
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

        // Destroy error stack.
        ErrorStack::shut_down();
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
        JUTIL::JUTILBase::debug_assert( application == nullptr || application_ == nullptr );
        application_ = application;
    }

}
