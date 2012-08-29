#pragma once

#include "jui/layout.h"
#include "jui/component.h"

enum EVerticalAlignType {
	ALIGN_TOP,
	ALIGN_MIDDLE,
	ALIGN_BOTTOM
};

class HorizontalLayout: public Layout
{

public:

	__declspec(dllexport) HorizontalLayout( unsigned int spacing = 0, EVerticalAlignType alignType = ALIGN_MIDDLE );

	// Packs elements into a horizontal layout.
	__declspec(dllexport) virtual void pack( void );
	__declspec(dllexport) void SetMinimumHeight( int minimumHeight );

	__declspec(dllexport) void set_align_type( EVerticalAlignType alignType );
	__declspec(dllexport) EVerticalAlignType get_align_type( void ) const;

private:

	int minimumHeight_;
	EVerticalAlignType alignType_;


};
