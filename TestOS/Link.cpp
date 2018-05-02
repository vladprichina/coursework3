#include "Header.h"
#include "BaseObject.h"
#include "Link.h"

Link::Link()
{
	m_pRefObject = nullptr;
}

Link::~Link()
{
	m_pRefObject = nullptr;
}

float Link::GetSize()
{
	if (m_pRefObject)
		return m_pRefObject->GetSize();
	
	return 0.f;
}