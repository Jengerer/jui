#include "jui/application/error_stack.hpp"
#include <memory/base_allocator.hpp>
#include <stdarg.h>

namespace JUI
{

	// Singleton instance.
	ErrorStack* ErrorStack::instance_ = nullptr;

	// Fallback error string.
	const JUTIL::ConstantString DEFAULT_ERROR_MESSAGE = "Encountered unknown/unreported error! Jengerer stinks at this!";

	/*
	 * Error stack destructor.
	 */
	ErrorStack::~ErrorStack( void )
	{
		clear();
	}

	/*
	 * Get instance of error stack.
	 */
	ErrorStack* ErrorStack::get_instance( void )
	{
		// Create instance if missing.
		if (instance_ == nullptr) {
			if (!JUTIL::BaseAllocator::allocate( &instance_ )) {
				return nullptr;
			}
			instance_ = new (instance_) ErrorStack();
		}

		return instance_;
	}

	/*
	 * Destroy instance of error stack.
	 */
	void ErrorStack::shut_down( void )
	{
		if (instance_ != nullptr) {
			JUTIL::BaseAllocator::destroy( instance_ );
		}
	}

	/*
	 * Log an error message.
	 */
	void ErrorStack::log( const char* format, ... )
	{
		va_list args;
		va_start( args, format );
		
		// Build message.
		JUTIL::DynamicString* string;
		if (!JUTIL::BaseAllocator::allocate( &string )) {
			return;
		}
		string = new (string) JUTIL::DynamicString();
		if (!string->write( format, args )) {
			return;
		}

		// Add to stack.
		if (!errors_.push( string )) {
			JUTIL::BaseAllocator::destroy( &string );
			return;
		}
		va_end( args );
	}

	/*
	 * Clear all messages.
	 */
	void ErrorStack::clear( void )
	{
		// Destroy strings.
		unsigned int i;
		for (i = 0; i < errors_.get_length(); ++i) {
			JUTIL::String* error = errors_.get( i );
			JUTIL::BaseAllocator::destroy( error );
		}
		errors_.clear();
	}

	/*
	 * Get error on the top of the stack.
	 * Returns a fallback error message if none is found.
	 */
	const JUTIL::String* ErrorStack::get_top_error( void ) const
	{
		// Check for empty stack.
		if (errors_.is_empty()) {
			return &DEFAULT_ERROR_MESSAGE;
		}

		size_t last_index = errors_.get_length() - 1;
		return errors_.get( last_index );
	}

	/*
	 * Error stack constructor.
	 */
	ErrorStack::ErrorStack( void )
	{
		// Nothing.
	}

}