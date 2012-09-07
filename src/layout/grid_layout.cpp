#include "jui/layout/grid_layout.hpp"

namespace JUI
{

    GridLayout::GridLayout( int grid_width, unsigned int spacing )
    {
        grid_width_ = grid_width;
        set_spacing( spacing );
    }

    GridLayout::~GridLayout( void )
    {
        // GridLayout destroyed.
    }

    void GridLayout::pack( void )
    {
        if (components_.is_empty()) {
            set_size( 0, 0 );
            return;
        }

        // Base component sizes on first element.
        Component *first = components_.get( 0 );
        int component_width = first->get_width();
        int component_height = first->get_height();
        int spacing = get_spacing();

        // Grid height is components / width, + 1 if remainder.
        size_t num_components = components_.get_length();
        int grid_height = num_components / grid_width_ + (num_components % grid_width_ == 0 ? 0 : 1);

        // Calculate width and height.
        int total_width = grid_width_ * (component_width + spacing) - spacing;
        int total_height = grid_height * (component_height + spacing) - spacing;
        set_size( total_width, total_height );

        size_t index = 0;
        float x, y;
        size_t i;
        for (i = 0; i < num_components; ++i) {
            Component* current = components_.get( i );
            x = static_cast<float>((index % grid_width_) * (component_width + spacing));
            y = static_cast<float>((index / grid_width_) * (component_height + spacing));
            set_constraint( current, x, y );

            ++index;
        }
    }

}
