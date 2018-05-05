#pragma once

DECLARE_SMART(BaseObject, spBaseObject);
class BaseObject : public ref_counter
{
public:
	BaseObject();
	virtual ~BaseObject();

	//getters
	const std::wstring & GetName()					{ return m_srName; }
	const std::wstring & GetIconName()				{ return m_srIconName; }
	std::wstring GetPath();
	std::wstring GetExtName();
	BaseObject * GetParent()						{ return m_Parent; }
	virtual float GetSize()							{ return 0.f; }
	virtual spBaseObject IsOpen()					{ return nullptr; }
	virtual std::wstring GetAddName()				{ return m_srAddName; }
	std::wstring GetTimeCreate();
	std::wstring GetTimeModify();

	//setters
	void SetName(std::wstring newName)				{ m_srName = newName; }
	void SetIconName(std::wstring newName)			{ m_srIconName = newName; }
	void SetParent(spBaseObject newParent)			{ m_Parent = newParent.get(); }
	void SetModifyTime();

	//remove
	virtual void RemoveChild(spBaseObject pChild)   {};
	virtual void RemoveChilds()						{};
	virtual void DeleteThis();
	
	//links
	void AddLink(spBaseObject newLink)				{ m_vLinks.push_back(newLink); }
	void DeleteLink(spBaseObject pLink);
	virtual void SetLink(spBaseObject pRef)			{};

protected:
	std::wstring				m_srName;
	std::wstring				m_srIconName;
	std::wstring				m_srAddName;
	BaseObject *				m_Parent;
	std::vector<spBaseObject>	m_vLinks;		 // все ссылки на данный объект
	struct tm					m_pTimeCreate;
	struct tm					m_pTimeModify;
};
