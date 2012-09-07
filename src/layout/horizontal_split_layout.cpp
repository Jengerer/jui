#include "jui/layout/horizontal_split_layout.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

    /*
     * Horizontal split layout constructor.
     */
    HorizontalSplitLayout::HorizontalSplitLayout( int width, unsigned int spacing )
    {
        // Set default size.
        set_size( width, 0 );

        // Create layouts.
        left_ = nullptr;
        right_ = nullptr;
        spacing_ = spacing;
    }

    /*
     * Reserve space for child components.
     */
    bool HorizontalSplitLayout::reserve( void )
    {
        // Allocate left container.
        if (JUTIL::BaseAllocator::allocate( &left_ )) {
            return false;
        }
        left_ = new (left_) HorizontalLayout( spacing_, ALIGN_TOP );
        if (!add( left_ )) {
            JUTIL::BaseAllocator::destroy( left_ );
            return false;
        }

        // Allocate right container.
        if (!JUTIL::BaseAllocator::allocate( &right_ )) {
            return false;
        }
        right_ = new (right_) HorizontalLayout( spacing_, ALIGN_TOP );
        if (!add( right_ )) {
            JUTIL::BaseAllocator::destroy( right_ );
            return false;
        }

        // Reserve constraints.
        Constraint* constraint = set_constraint( right_, 0.0f, 0.0f );
        if (constraint == nullptr) {
            return false;
        }
        constraint = set_constraint( left_, 0.0f, 0.0f );
        if (constraint == nullptr) {
            return false;
        }

        return true;
    }

    /*
     * Pack nested layouts and move to sides.
     */
    void HorizontalSplitLayout::pack( void )
    {
        // Pack left and right.
        left_->pack();
        right_->pack();
        set_constraint( right_, static_cast<float>(get_width() - right_->get_width()), 0.0f );

        // Set height as maximum.
        int left_height = left_->get_height();
        int right_height = right_->get_height();
        int max_height = left_height > right_height ? left_height : right_height;
        set_size( get_width(), max_height );
    }

    /*
     * Add a component to the left child.
     */
    bool HorizontalSplitLayout::add_left( Component* component )
    {
        return left_->add( component );
    }

    /*
     * Add a component to the right child.
     */
    bool HorizontalSplitLayout::add_right( Component* component )
    {
        return right_->add( component );
    }

}
