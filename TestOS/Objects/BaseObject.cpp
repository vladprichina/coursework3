#include "../Header.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	m_Parent = nullptr;
}

BaseObject::~BaseObject()
{
	m_Parent = nullptr;
}

void BaseObject::DeleteThis()
{
	if (m_Parent)
		m_Parent->RemoveChild(this);
	m_Parent = NULL;
}

std::string BaseObject::GetPath()
{
	std::string srPath;

	if (m_Parent)
	{
		srPath = m_Parent->GetPath();
		srPath += " / ";
	}
	srPath += m_srName;
	return srPath;
}

std::string BaseObject::GetExtName()
{
	std::string srFullName = GetName();
	if (!GetAddName().empty())
	{
		srFullName += GetAddName();
	}

	return srFullName;
}