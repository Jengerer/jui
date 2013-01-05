#include "jui/layout/horizontal_split_layout.hpp"
#include <memory/base_allocator.hpp>

namespace JUI
{

	/*
	 * Horizontal split layout constructor.
	 */
	HorizontalSplitLayout::HorizontalSplitLayout( int width )
	{
		left_ = nullptr;
		right_ = nullptr;

		// Set width.
		set_size( width, 0 );
	}

	/*
	 * Update size as maximum height.
	 */
	void HorizontalSplitLayout::pack( void )
	{
		// Position left and right.
		set_constraint( left_, 0, 0 );
		int width = get_width();
		int right_position = width - right_->get_width();
		set_constraint( right_, right_position, 0 );

		// Set height as maximum.
		int left_height = left_->get_height();
		int right_height = right_->get_height();
		int max_height = (left_height > right_height ? left_height : right_height);
		set_size( width, max_height );
	}

	/*
	 * Set left component.
	 * Assumes object has final width set before setting.
	 */
	bool HorizontalSplitLayout::set_left( Component* component )
	{
		// Add component.
		JUTIL::JUTILBase::debug_assert( left_ == nullptr );
		if (!add( component )) {
			return false;
		}
		left_ = component;
		return true;
	}

	/*
	 * Set right component.
	 */
	bool HorizontalSplitLayout::set_right( Component* component )
	{
		// Add component.
		JUTIL::JUTILBase::debug_assert( right_ == nullptr );
		if (!add( component )) {
			return false;
		}
		right_ = component;
		return true;
	}

}
