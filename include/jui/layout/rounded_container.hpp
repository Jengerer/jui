#ifndef ROUNDED_RECTANGLE_CONTAINER_HPP
#define ROUNDED_RECTANGLE_CONTAINER_HPP

#include "jui/layout/constrained_container.hpp"
#include "jui/layout/horizontal_layout.hpp"
#include "jui/gfx/rounded_rectangle.hpp"

namespace JUI
{

	// A new record! Longest class name in the project!
	class RoundedRectangleContainer : public ConstrainedContainer
	{

	public:

		RoundedRectangleContainer( unsigned int radius, unsigned int padding, float localX = 0.0f, float localY = 0.0f );

		// Container functions.
		virtual void        pack();

		// Content and rectangle.
		void                SetContent( Component* content );
		RoundedRectangle*   GetRoundedRectangle() const;

		// Attribute function settings.
		void                SetPadding( unsigned int padding );

	private:

		RoundedRectangle*   roundedRect_;
		Component*          content_;
		unsigned int        padding_;

	};

}

#endif // ROUNDED_RECTANGLE_CONTAINER_HPP
