#ifndef ERROR_STACK_HPP
#define ERROR_STACK_HPP

#include "jui/jui_base.hpp"
#include <string/string.hpp>
#include <containers/vector.hpp>

namespace JUI
{

	/*
	 * Singleton class for managing error stack from components.
	 */
	class ErrorStack
	{
	
	public:

		// Public destructor allocator.
		JUI_API ~ErrorStack( void );

		// Singleton instance management.
		static JUI_API ErrorStack* get_instance( void );
		static JUI_API void shut_down( void );

		// Error logging functions.
		JUI_API void log( const char* format, ... );
		JUI_API void clear( void );

		// Stack retrieval.
		JUI_API const JUTIL::String* get_top_error( void ) const;
		JUI_API size_t get_error_count( void ) const;
		JUI_API const JUTIL::String* get_error( size_t index ) const;

	private:

		ErrorStack( void );

	private:

		static ErrorStack* instance_;

	private:

		JUTIL::Vector<JUTIL::String*> errors_;

	};

}

#endif // ERROR_STACK_HPP
