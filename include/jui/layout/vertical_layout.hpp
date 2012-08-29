#ifndef VERTICAL_LAYOUT_HPP
#define VERTICAL_LAYOUT_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/component.hpp"

namespace JUI
{

    enum EHorizontalAlignType {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };

    class VerticalLayout : public Layout
    {

    public:

        __declspec(dllexport) VerticalLayout( unsigned int spacing = 0, EHorizontalAlignType alignType = ALIGN_CENTER );

        // Packs elements into a horizontal layout.
        __declspec(dllexport) virtual void pack( void );
        __declspec(dllexport) void set_minimum_width( int minimumWidth );

        __declspec(dllexport) void set_align_type( EHorizontalAlignType alignType );
        __declspec(dllexport) EHorizontalAlignType get_align_type( void ) const;

    private:

        int minimumWidth_;
        EHorizontalAlignType alignType_;


    };

}

#endif // VERTICAL_LAYOUT_HPP
