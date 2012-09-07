#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

    HorizontalLayout::HorizontalLayout( unsigned int spacing, EVerticalAlignType align_type ) : Layout( spacing )
    {
        // HorizontalLayout created.
        set_align_type( align_type );
        SetMinimumHeight( 0 );
    }

    void HorizontalLayout::pack( void )
    {
        // First get maximum height.
        int max_height = 0;
        size_t i;
        size_t length = components_.get_length();
        for (i = 0; i < length; ++i) {
            Component* component = components_.get( i );
            int height = component->get_height();
            if (height > max_height) {
                max_height = height;
            }
        }
        if (max_height < minimum_height_) {
            max_height = minimum_height_;
        }

        // Now pack.
        float width = 0.0f;
        for (i = 0; i < length; ++i) {
            Component* component = components_.get( i );

            // Push by spacing if not first.
            if (i != 0) {
                width += get_spacing();
            }

            // Set position aligned vertically.
            float y;
            switch (get_align_type()) {
            case ALIGN_TOP:
                y = 0.0f;
                break;
            case ALIGN_MIDDLE:
                y = static_cast<float>(max_height - component->get_height()) / 2.0f;
                break;
            case ALIGN_BOTTOM:
                y += static_cast<float>(max_height - component->get_height());
                break;
            }
            set_constraint( component, width, y );

            // Push width by component width.
            width += static_cast<float>(component->get_width());
        }

        // Update size.
        set_size( static_cast<int>(width), max_height );
    }

    void HorizontalLayout::SetMinimumHeight( int minimumHeight )
    {
        minimum_height_ = minimumHeight;
    }

    void HorizontalLayout::set_align_type( EVerticalAlignType align_type )
    {
        align_type_ = align_type;
    }

    EVerticalAlignType HorizontalLayout::get_align_type( void ) const
    {
        return align_type_;
    }

}
