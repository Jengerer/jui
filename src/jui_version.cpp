#include "jui/jui_version.hpp"

namespace JUI
{

	// Version string to share with callers.
	const JUTIL::ConstantString JUI_VERSION( "0.1.6" );

	// Return thet version string.
	const JUTIL::String* get_version_string( void )
	{
		return &JUI_VERSION;
	}

}