#ifndef IRESOURCE_SOURCE_HPP
#define IRESOURCE_SOURCE_HPP

#include <string>

namespace JUI
{

    class ResourceSourceInterface
    {

    public:

        virtual void get_resource( const std::string& target, const std::string& destination ) = 0;

    };

}

#endif // IRESOURCE_SOURCE_HPP
