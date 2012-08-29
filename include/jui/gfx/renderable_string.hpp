#ifndef IRENDERABLE_STRING_HPP
#define IRENDERABLE_STRING_HPP

namespace JUI
{

    class RenderableString
    {

    public:

        // Constructor.
        RenderableString( size_t length );

        // Get character code.
        virtual unsigned long char_code_at( size_t index ) const = 0;

        // Get string length.
        size_t length() const;

    private:

        size_t length_;

    };

}

#endif // IRENDERABLE_STRING_HPP
