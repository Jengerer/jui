#ifndef ERROR_STACK_HPP
#define ERROR_STACK_HPP

#include <string/string.hpp>
#include <containers/vector.hpp>

namespace JUI
{

	/*
	 * Singleton class for managing error stack from components.
	 */
	class __declspec(dllexport) ErrorStack
	{
	
	public:

		// Public destructor allocator.
		~ErrorStack( void );

		// Singleton instance management.
		static ErrorStack* get_instance( void );
		static void shut_down( void );

		// Error logging functions.
		void log( const char* format, ... );
		void clear( void );

		// Stack retrieval.
		const JUTIL::String* get_top_error( void ) const;

	private:

		ErrorStack( void );

	private:

		static ErrorStack* instance_;

	private:

		JUTIL::Vector<JUTIL::String*> errors_;

	};

}

#endif // ERROR_STACK_HPP
