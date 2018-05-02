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
	const std::string & GetName()					{ return m_srName; }
	const std::string & GetIconName()				{ return m_srIconName; }
	std::string GetPath();
	std::string GetExtName();
	BaseObject * GetParent()						{ return m_Parent; }
	virtual std::string GetAddName()				{ return ""; }
	virtual float GetSize()							{ return 0; }
	virtual bool IsOpen()							{ return false; }

	//setters
	void SetName(std::string newName)				{ m_srName = newName; }
	void SetIconName(std::string newName)			{ m_srIconName = newName; }
	void SetParent(spBaseObject newParent)			{ m_Parent = newParent.get(); }

	//remove
	virtual void RemoveChild(spBaseObject pChild)   {};
	virtual void RemoveChilds()						{};
	virtual void DeleteThis();

protected:
	std::string			m_srName;
	std::string			m_srIconName;
	BaseObject *		m_Parent;
};
