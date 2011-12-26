#ifndef IRESOURCE_SOURCE_H
#define IRESOURCE_SOURCE_H

#include <string>

class IResourceSource
{

public:

	virtual void get_resource( const std::string& target, const std::string& destination ) = 0;

};

#endif // IRESOURCE_SOURCE_H