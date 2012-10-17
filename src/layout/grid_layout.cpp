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

        // Constants for multiplying.
        const int TOTAL_X_SPACING = component_width + spacing;
        const int TOTAL_Y_SPACING = component_height + spacing;

        // Position all elements.
        int x;
        int y;
        size_t i;
        for (i = 0; i < num_components; ++i) {
            Component* current = components_.get( i );
            x = (i % grid_width_) * TOTAL_X_SPACING;
            y = (i / grid_width_) * TOTAL_Y_SPACING;
            set_constraint( current, x, y );
        }
    }

}
