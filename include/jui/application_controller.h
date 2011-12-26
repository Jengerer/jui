#ifndef APPLICATION_CONTROLLER_H
#define APPLICATION_CONTROLLER_H

#include "jui/application.h"

/*
 * Static application controller.
 */
class ApplicationController
{

public:

	// Set controlled application.
	static __declspec(dllexport) void initialize( Application* application );

	// Enter main loop.
	static __declspec(dllexport) void main_loop();

	// Exit application.
	static __declspec(dllexport) void exit();

	// Get handle.
	static __declspec(dllexport) Application* get_application();

private:

	// Set handle.
	static void set_application( Application* application );

	// Application to be managed.
	static Application* application_;

};

#endif // APPLICATION_CONTROLLER_H