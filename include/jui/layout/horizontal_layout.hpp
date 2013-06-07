#ifndef HORIZONTAL_LAYOUT_HPP
#define HORIZONTAL_LAYOUT_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/component.hpp"

namespace JUI
{

	// Enum for alignment along vertical axis.
	enum VerticalAlignType {
		ALIGN_TOP,
		ALIGN_MIDDLE,
		ALIGN_BOTTOM
	};

	class HorizontalLayout: public Layout
	{

	public:

		__declspec(dllexport) HorizontalLayout( void );

		// Packs elements into a horizontal layout.
		__declspec(dllexport) void pack( unsigned int spacing, VerticalAlignType align_type );
		__declspec(dllexport) void set_minimum_height( int height );

	private:

		int minimum_height_;

	};

}

#endif // HORIZONTAL_LAYOUT_HPP
