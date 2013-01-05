#ifndef BOX_HPP
#define BOX_HPP

#include "jui/layout/component.hpp"

namespace JUI
{

	class Box : public Component
	{

	public:
		
		// Constructor.
		Box();

		// IDrawable over-ride.
		virtual void draw( Graphics2D* graphics );

	private:

		Colour colour_;

	};

}

#endif // BOX_HPP
