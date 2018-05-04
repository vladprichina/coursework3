#pragma once

// set нуждается в переопределении оператора < или предикате для сортировки
struct sortObject
{
	bool operator() (spBaseObject obj1, spBaseObject obj2)const
	{
		return obj1->GetName() < obj2->GetName();
	}
};

DECLARE_SMART(Folder, spFolder);
class Folder : public BaseObject
{
public:
	Folder();
	Folder(const std::wstring & srName, const std::wstring & srIconName);
	virtual ~Folder();

	virtual float			GetSize() override;
	virtual void			DeleteThis() override;
	virtual void			RemoveChilds() override;
	virtual spBaseObject	IsOpen() override								{ return this; }
	virtual std::wstring	GetAddName()	override						{ return L""; }
	virtual void			RemoveChild(spBaseObject pChild) override;
	void					AddChild(spBaseObject pChild);	
	spBaseObject			GetChild(const std::wstring & srName, const std::wstring & srAddName);
	
	std::set < spBaseObject, sortObject> m_vChilds;
};