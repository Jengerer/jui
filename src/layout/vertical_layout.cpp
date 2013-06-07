#include "jui/layout/vertical_layout.hpp"

namespace JUI
{

	/*
	 * Vertical layout constructor.
	 */
	VerticalLayout::VerticalLayout( void )
	{
		set_minimum_width( 0 );
	}

	/*
	 * Align all elements into vertical layout.
	 */
	void VerticalLayout::pack( unsigned int spacing, HorizontalAlignType align_type )
	{
		// First get maximum width and clamp above minimum width.
		int max_width = 0;
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* component = components_.at( i );
			int width = component->get_width();
			if (width > max_width) {
				max_width = width;
			}
		}

		// Enforce minimal width.
		if (max_width < minimum_width_) {
			max_width = minimum_width_;
		}

		// Now pack.
		int height = 0;
		for (i = 0; i < length; ++i) {
			Component *component = components_.at( i );

			// Push by spacing if not first.
			if (i != 0) {
				height += spacing;
			}

			// Set position aligned horizontally.
			int x;
			switch (align_type) {
			case ALIGN_LEFT:
				x = 0;
				break;
			case ALIGN_CENTER:
				x = (max_width - component->get_width()) / 2;
				break;
			case ALIGN_RIGHT:
				x = max_width - component->get_width();
				break;
			}
			set_constraint( component, x, height );

			// Push height by component height.
			height += component->get_height();
		}

		// Update size.
		set_size( max_width, height );
	}

	/*
	 * Set minimum width for layout.
	 */
	void VerticalLayout::set_minimum_width( int width )
	{
		minimum_width_ = width;
	}

}
