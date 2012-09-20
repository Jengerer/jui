#include "jui/application/error_stack.hpp"
#include <memory/base_allocator.hpp>
#include <stdarg.h>

namespace JUI
{

    // Singleton instance.
    ErrorStack* ErrorStack::instance_ = nullptr;

    /*
     * Error stack destructor.
     */
    ErrorStack::~ErrorStack( void )
    {
        // Nothing.
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
        
        // Allocate string.
        JUTIL::String* string;
        if (!JUTIL::BaseAllocator::allocate( &string )) {
            return;
        }

        // Build string.
        JUTIL::StringBuilder builder;
        if (!builder.write( format, args )) {
            return;
        }
        string = new (string) JUTIL::String( &builder );
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
     */
    const JUTIL::String* ErrorStack::get_top_error( void ) const
    {
        // Check for empty stack.
        if (errors_.is_empty()) {
            return nullptr;
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