#include "../Header.h"
#include "BaseObject.h"
#include "Link.h"

Link::Link()
{
	m_pRefObject = nullptr;
	m_eLinkType = eNone;
}

Link::~Link()
{
	m_pRefObject = nullptr;
}

Link::Link(std::wstring srName, eTypeLink eType, spBaseObject pRef)
{
	m_srName = srName;
	m_srAddName = m_eLinkType == eSymbol ? L"link" : L"hlink";
	m_eLinkType = eType;
	m_pRefObject = pRef;
}

float Link::GetSize()
{
	if (m_pRefObject)
		return m_pRefObject->GetSize();
	
	return 0.f;
}