#pragma once

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
	Folder(const std::string & srName, const std::string & srIconName);
	virtual ~Folder();

	virtual float GetSize() override;
	virtual void  DeleteThis() override;
	virtual void  RemoveChilds() override;
	virtual bool  IsOpen()								{ return true; }
	virtual void  RemoveChild(spBaseObject pChild) override;

	void AddChild(spBaseObject pChild);	
	

	std::set < spBaseObject, sortObject> m_vChilds;
};