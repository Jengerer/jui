#ifndef IKEYBOARD_HANDLER_HPP
#define IKEYBOARD_HANDLER_HPP

#include "jui/io/io_common.hpp"

namespace JUI
{

	class KeyboardHandlerInterface
	{

	public:

		virtual IOResult on_key_pressed( int key ) = 0;
		virtual IOResult on_key_released( int key ) = 0;

	};

}

#endif // IKEYBOARD_HANDLER_HPP
