#include "jui/layout/horizontal_layout.hpp"

namespace JUI
{

	HorizontalLayout::HorizontalLayout( void )
	{
	}

	void HorizontalLayout::pack( unsigned int spacing, VerticalAlignType align_type )
	{
		// First get tallest element and clamp above minimum height.
		int max_height = 0;
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* component = components_.at( i );
			int height = component->get_height();
			if (height > max_height) {
				max_height = height;
			}
		}
		if (max_height < minimum_height_) {
			max_height = minimum_height_;
		}

		// Now pack all elements into position.
		int width = 0;
		for (i = 0; i < length; ++i) {
			Component* component = components_.at( i );

			// Push by spacing if not first.
			if (i != 0) {
				width += spacing;
			}

			// Set position aligned vertically.
			int y;
			switch (align_type) {
			case ALIGN_TOP:
				y = 0;
				break;
			case ALIGN_MIDDLE:
				y = (max_height - component->get_height()) / 2;
				break;
			case ALIGN_BOTTOM:
				y = max_height - component->get_height();
				break;
			}
			set_constraint( component, width, y );

			// Push width by component width.
			width += component->get_width();
		}

		// Update size.
		set_size( width, max_height );
	}

	void HorizontalLayout::set_minimum_height( int height )
	{
		minimum_height_ = height;
	}

}
