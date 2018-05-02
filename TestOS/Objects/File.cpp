#include "../Header.h"
#include "BaseObject.h"
#include "File.h"

File::File(const std::string & srName, const std::string & srIconName, const std::string & srAddName, float fSize)
{
	m_srName = srName;
	m_srIconName = srIconName;
	m_srAddName = srAddName;
	m_fSize = fSize;
}

File::~File()
{

}