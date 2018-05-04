#pragma once

enum eTypeLink
{
	eNone = 0,
	eHard = 1,
	eSymbol = 2,
};

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
	virtual std::wstring GetAddName()				{ return L""; }
	virtual float GetSize()							{ return 0.f; }
	virtual bool IsOpen()							{ return false; }

	//setters
	void SetName(std::wstring newName)				{ m_srName = newName; }
	void SetIconName(std::wstring newName)			{ m_srIconName = newName; }
	void SetParent(spBaseObject newParent)			{ m_Parent = newParent.get(); }

	//remove
	virtual void RemoveChild(spBaseObject pChild)   {};
	virtual void RemoveChilds()						{};
	virtual void DeleteThis();

protected:
	std::wstring			m_srName;
	std::wstring			m_srIconName;
	BaseObject *			m_Parent;
};
