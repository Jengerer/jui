#ifndef LAYOUT_H
#define LAYOUT_H

#include "jui/component.h"
#include "jui/constrained_container.h"

// Abstract class to format elements within a container.
class Layout: public ConstrainedContainer
{

public:

	__declspec(dllexport) Layout( unsigned int spacing = 0 );
	__declspec(dllexport) virtual ~Layout( void );

	// Format the elements into the appropriate layout.
	__declspec(dllexport) virtual void		pack( void ) = 0;

	// Sets the spacing between elements.
	__declspec(dllexport) int	get_spacing( void ) const;
	__declspec(dllexport) void	set_spacing( int spacing );

	// Bound restriction based on parent.
	__declspec(dllexport) virtual bool is_visible( Component *component ) const;

	// Sets a parent to handle size constraints.
	__declspec(dllexport) void set_parent( Container *parent );
	__declspec(dllexport) const Container* get_parent( void ) const ;

private:

	Container		*parent_;
	int				spacing_;

};

#endif // LAYOUT_H