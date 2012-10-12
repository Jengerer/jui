#ifndef IO_COMMON_HPP
#define IO_COMMON_HPP

namespace JUI
{

    // Result for IO handling event.
    enum IOResult
    {
        IO_RESULT_HANDLED, // Event handled, don't continue propagating.
        IO_RESULT_UNHANDLED, // Event not handled yet, pass on.
        IO_RESULT_ERROR, // Error occurred with handling mouse.
    };

}

#endif // IO_COMMON_HPP