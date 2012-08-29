#ifndef HORIZONTAL_SPLIT_CONTAINER_H
#define HORIZONTAL_SPLIT_CONTAINER_H

#include "jui/layout.h"
#include "jui/horizontal_layout.h"

class HorizontalSplitLayout: public Layout
{

public:

	__declspec(dllexport) HorizontalSplitLayout( int width, unsigned int spacing = 0 );

	__declspec(dllexport) virtual void pack();
	__declspec(dllexport) void add_left( Component* component );
	__declspec(dllexport) void add_right( Component* component );

private:

	HorizontalLayout* left_;
	HorizontalLayout* right_;

};

#endif // HORIZONTAL_SPLIT_CONTAINER_H