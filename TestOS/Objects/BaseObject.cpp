#include "../Header.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	time_t rawtime;
	time(&rawtime);                              
	gmtime_s(&m_pTimeCreate, &rawtime);
	gmtime_s(&m_pTimeModify, &rawtime);
}

BaseObject::~BaseObject()
{
	m_Parent = nullptr;
}

void BaseObject::SetModifyTime()
{
	time_t rawtime;
	time(&rawtime);
	gmtime_s(&m_pTimeModify, &rawtime);
}

std::wstring BaseObject::GetTimeCreate()
{
	std::wstring srReturn = to_wstring(m_pTimeCreate.tm_hour +VRN) + L":" + to_wstring(m_pTimeCreate.tm_min) + L"  ";
	srReturn += to_wstring(m_pTimeCreate.tm_mday) + L"." + to_wstring(m_pTimeCreate.tm_mon + 1) + L"." + to_wstring(m_pTimeCreate.tm_year + START_YEAR);
	
	return srReturn;
}
std::wstring BaseObject::GetTimeModify()
{
	std::wstring srReturn = to_wstring(m_pTimeModify.tm_hour + VRN) + L":" + to_wstring(m_pTimeModify.tm_min) + L"  ";
	srReturn += to_wstring(m_pTimeModify.tm_mday) + L"." + to_wstring(m_pTimeModify.tm_mon + 1) + L"." + to_wstring(m_pTimeModify.tm_year + START_YEAR);


	return srReturn;
}

void BaseObject::DeleteThis()
{
	if (m_Parent)
		m_Parent->RemoveChild(this);
	m_Parent = NULL;

	for (spBaseObject pRef : m_vLinks)
		pRef->SetLink(nullptr);
	

	m_vLinks.clear();
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

void BaseObject::DeleteLink(spBaseObject pLink)
{
	auto iterFind = find(m_vLinks.begin(), m_vLinks.end(), pLink);

	if (iterFind != m_vLinks.end())
	{
		m_vLinks.erase(iterFind);
	}
}
