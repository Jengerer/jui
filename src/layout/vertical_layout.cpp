#include "jui/layout/vertical_layout.hpp"

namespace JUI
{

	/*
	 * Vertical layout constructor.
	 */
	VerticalLayout::VerticalLayout( unsigned int spacing, EHorizontalAlignType align_type ) : Layout( spacing )
	{
		set_align_type( align_type );
		set_minimum_width( 0 );
	}

	/*
	 * Align all elements into vertical layout.
	 */
	void VerticalLayout::pack( void )
	{
		// First get maximum width.
		int max_width = 0;
		size_t i;
		size_t length = components_.get_length();
		for (i = 0; i < length; ++i) {
			Component* component = components_.get( i );
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
			Component *component = components_.get( i );

			// Push by spacing if not first.
			if (i != 0) {
				height += get_spacing();
			}

			// Set position aligned horizontally.
			int x;
			switch (get_align_type()) {
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
	 * Set horizontal element alignment type.
	 */
	void VerticalLayout::set_align_type( EHorizontalAlignType align_type )
	{
		align_type_ = align_type;
	}

	/*
	 * Get current setting for alignment type.
	 */
	EHorizontalAlignType VerticalLayout::get_align_type( void ) const
	{
		return align_type_;
	}

	/*
	 * Set minimum width for layout.
	 */
	void VerticalLayout::set_minimum_width( int minimumWidth )
	{
		minimum_width_ = minimumWidth;
	}

}
