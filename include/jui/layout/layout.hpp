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

        Layout( unsigned int spacing = 0 );
        virtual ~Layout( void );

        // Format the elements into the appropriate layout.
        virtual void pack( void ) = 0;

        // Sets the spacing between elements.
        int get_spacing( void ) const;
        void set_spacing( int spacing );

        // Bound restriction based on parent.
        virtual bool is_visible( Component *component ) const;

        // Sets a parent to handle size constraints.
        void set_parent( Container *parent );
        const Container* get_parent( void ) const ;

    private:

        Container* parent_;
        int spacing_;

    };

}

#endif // LAYOUT_HPP
