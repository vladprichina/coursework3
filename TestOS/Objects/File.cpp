#include "../Header.h"
#include "BaseObject.h"
#include "File.h"

File::File(const std::wstring & srName, const std::wstring & srIconName, const std::wstring & srAddName, float fSize)
{
	m_srName = srName;
	m_srIconName = srIconName;
	m_srAddName = srAddName;
	m_fSize = fSize;
}

File::~File()
{

}