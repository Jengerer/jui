#ifndef HORIZONTAL_LAYOUT_HPP
#define HORIZONTAL_LAYOUT_HPP

#include "jui/layout/layout.hpp"
#include "jui/layout/component.hpp"

namespace JUI
{

	enum EVerticalAlignType {
		ALIGN_TOP,
		ALIGN_MIDDLE,
		ALIGN_BOTTOM
	};

	class HorizontalLayout: public Layout
	{

	public:

		__declspec(dllexport) HorizontalLayout( unsigned int spacing = 0, EVerticalAlignType align_type = ALIGN_MIDDLE );

		// Packs elements into a horizontal layout.
		__declspec(dllexport) virtual void pack( void );
		__declspec(dllexport) void SetMinimumHeight( int minimumHeight );

		__declspec(dllexport) void set_align_type( EVerticalAlignType align_type );
		__declspec(dllexport) EVerticalAlignType get_align_type( void ) const;

	private:

		int minimum_height_;
		EVerticalAlignType align_type_;


	};

}

#endif // HORIZONTAL_LAYOUT_HPP
