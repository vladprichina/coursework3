#include "../Header.h"
#include "BaseObject.h"
#include "Link.h"

Link::~Link()
{
	m_pRefObject = nullptr;
}

Link::Link(std::wstring srName, eTypeLink eType, spBaseObject pRef)
{
	m_eLinkType = eType;
	m_pRefObject = pRef;
	m_srName = srName;
	m_srAddName = m_pRefObject->GetAddName();
	m_srAddName += m_eLinkType == eSymbol ? typeSLink : typeHLink;
	m_pRefObject->AddLink(this);

	BaseObject::BaseObject();
}

void Link::DeleteThis()
{
	BaseObject::DeleteThis();

	if (m_pRefObject)
	{
		m_pRefObject->DeleteLink(this);
		
		if (m_eLinkType == eSymbol)
		{
			m_pRefObject = nullptr;
		}
		else if (m_eLinkType == eHard)
		{
			m_pRefObject->DeleteThis();
		}
	}
}

float Link::GetSize()
{
	if (m_pRefObject)
		return m_pRefObject->GetSize();
	
	return 0.f;
}

spBaseObject Link::IsOpen()
{
	if (m_pRefObject)
		return m_pRefObject->IsOpen();

	return nullptr;
}