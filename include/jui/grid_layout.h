#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include "jui/layout.h"

class GridLayout : public Layout
{

public:

	__declspec(dllexport) GridLayout( int gridWidth, unsigned int spacing );
	__declspec(dllexport) virtual ~GridLayout( void );

	__declspec(dllexport) virtual void pack( void );

private:

	int gridWidth_;

};

#endif // GRID_LAYOUT_H