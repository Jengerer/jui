#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "jui/layout/component.hpp"
#include "jui/layout/constrained_container.hpp"

namespace JUI
{

	/*
	 * Generic layout class that formats inner components.
	 */
	class __declspec(dllexport) Layout: public ConstrainedContainer
	{

	public:

		Layout( void );
		virtual ~Layout( void );

		// Bound restriction based on parent.
		// TODO: Is parent needed?
		virtual bool is_visible( Component *component ) const;

		// Sets a parent to handle size constraints.
		void set_parent( Container *parent );
		const Container* get_parent( void ) const ;

	private:

		Container* parent_;

	};

}

#endif // LAYOUT_HPP
