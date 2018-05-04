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

std::wstring BaseObject::GetPath()
{
	std::wstring srPath;

	if (m_Parent)
	{
		srPath = m_Parent->GetPath();
		srPath += L" / ";
	}
	srPath += m_srName;
	return srPath;
}

std::wstring BaseObject::GetExtName()
{
	std::wstring srFullName = GetName();
	if (!GetAddName().empty())
	{
		srFullName += GetAddName();
	}

	return srFullName;
}