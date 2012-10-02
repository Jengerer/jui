#ifndef RENDERABLE_STRING_HPP
#define RENDERABLE_STRING_HPP

namespace JUI
{

    /*
     * Class for maintaining a generic renderable string.
     */
    class RenderableString
    {

    public:

        RenderableString( void );
        RenderableString( size_t length );

        // String functions.
        virtual unsigned long char_code_at( size_t index ) const = 0;
        size_t get_length( void ) const;

    private:

        size_t length_;

    };

}

#endif // RENDERABLE_STRING_HPP
