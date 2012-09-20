#include "jui/layout/horizontal_split_layout.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

    /*
     * Create an instance of the split layout.
     */
    HorizontalSplitLayout* HorizontalSplitLayout::create( int width, int spacing )
    {
        // Allocate objects.
        HorizontalSplitLayout* layout;
        HorizontalLayout* left;
        HorizontalLayout* right;
        if (!JUTIL::BaseAllocator::allocate( &layout )) {
            return nullptr;
        }
        else if (!JUTIL::BaseAllocator::allocate( &left )) {
            JUTIL::BaseAllocator::destroy( layout );
            return nullptr;
        }
        else if (!JUTIL::BaseAllocator::allocate( &right )) {
            JUTIL::BaseAllocator::destroy( left );
            JUTIL::BaseAllocator::destroy( layout );
            return nullptr;
        }

        // Create left.
        left = new (left) HorizontalLayout( spacing, ALIGN_TOP );
        right = new (right) HorizontalLayout( spacing, ALIGN_TOP );

        // Create layout.
        layout = new (layout) HorizontalSplitLayout();
        if (!layout->add( left )) {
            JUTIL::BaseAllocator::destroy( left );
            JUTIL::BaseAllocator::destroy( right );
            JUTIL::BaseAllocator::destroy( layout );
            return nullptr;
        }
        else if (!layout->add( right )) {
            // Left will be destroyed with layout.
            JUTIL::BaseAllocator::destroy( right );
            JUTIL::BaseAllocator::destroy( layout );
            return nullptr;
        }
        
        // Initialize layout.
        layout->set_size( width, 0 );
        layout->left_ = left;
        layout->right_ = right;
        return layout;
    }

    /*
     * Horizontal split layout constructor.
     */
    HorizontalSplitLayout::HorizontalSplitLayout( void )
    {
        // Nothing, done in create.
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
