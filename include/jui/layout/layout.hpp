#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "jui/layout/component.hpp"
#include "jui/layout/constrained_container.hpp"

namespace JUI
{

	/*
	 * Generic layout class that formats inner components.
	 */
	class Layout: public ConstrainedContainer
	{

	public:

		JUI_API Layout( void );
		JUI_API virtual ~Layout( void );

		// Bound restriction based on parent.
		// TODO: Is parent needed?
		JUI_API virtual bool is_visible( Component *component ) const;

		// Sets a parent to handle size constraints.
		JUI_API void set_parent( Container *parent );
		JUI_API const Container* get_parent( void ) const ;

	private:

		Container* parent_;

	};

}

#endif // LAYOUT_HPP
