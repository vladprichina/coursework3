#include "../stdafx.h"
#include "../Header.h"
#include "BaseObject.h"
#include "Folder.h"


Folder::Folder(const std::wstring & srName, const std::wstring & srIconName)
{
	m_srName = srName;
	m_srIconName = srIconName;

	BaseObject::BaseObject();
}

Folder::~Folder()
{
	m_vChilds.clear();
}

float Folder::GetSize()
{
	float fSize = 0.f;

	for (spBaseObject spSmart: m_vChilds)
	{
		BaseObject * pObj = spSmart.get();
		fSize += pObj->GetSize();
	}

	return fSize;
}

void Folder::DeleteThis()
{
	RemoveChilds();

	BaseObject::DeleteThis();
}

void Folder::AddChild(spBaseObject pChild)
{
	m_vChilds.insert(pChild);
	pChild->SetParent(this);
}

void Folder::RemoveChild(spBaseObject pChild)
{
	pChild->SetParent(nullptr);
	m_vChilds.erase(pChild);
}

void Folder::RemoveChilds()
{
	for (spBaseObject spSmart : m_vChilds)
	{
		BaseObject * pObj = spSmart.get();
		pObj->RemoveChilds();
	}

	m_vChilds.clear();
}

spBaseObject Folder::GetChild(const std::wstring & srName, const std::wstring & srAddName)
{
	auto iterFind = find_if(m_vChilds.begin(), m_vChilds.end(), [&](spBaseObject  pBase)
	{
		return pBase->GetName() == srName && pBase->GetAddName() == srAddName;
	});

	if (iterFind!= m_vChilds.end())
		return *iterFind;

	return nullptr;
}