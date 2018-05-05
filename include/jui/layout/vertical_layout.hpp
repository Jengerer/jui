#ifndef VERTICAL_LAYOUT_HPP
#define VERTICAL_LAYOUT_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/component.hpp"

namespace JUI
{

	// Enumerator for alignment along horizontal axis.
	enum HorizontalAlignType {
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};

	/*
	 * Vertical layout that distributes elements across a vertical span.
	 */
	class VerticalLayout : public Layout
	{

	public:

		JUI_API VerticalLayout( void );

		// Packs elements into a horizontal layout.
		JUI_API virtual void pack( unsigned int spacing, HorizontalAlignType align_type );
		JUI_API void set_minimum_width( int width );

	private:

		int minimum_width_;

	};

}

#endif // VERTICAL_LAYOUT_HPP
