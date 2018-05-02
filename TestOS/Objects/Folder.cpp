#include "../stdafx.h"
#include "../Header.h"
#include "BaseObject.h"
#include "Folder.h"

Folder::Folder()
{
	m_srName = "default_name";
}

Folder::Folder(const std::string & srName, const std::string & srIconName)
{
	m_srName = srName;
	m_srIconName = srIconName;
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
	BaseObject::DeleteThis();

	for (spBaseObject spSmart : m_vChilds)
	{
		BaseObject * pObj = spSmart.get();
		pObj->DeleteThis();
	}

	m_vChilds.clear();
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
		pObj->DeleteThis();
	}

	m_vChilds.clear();
}