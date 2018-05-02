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
	virtual bool IsOpen()								{ return true; }

	void AddChild(spBaseObject pChild);	
	void RemoveChild(spBaseObject pChild);		
	void RemoveChilds();						

	std::set < spBaseObject, sortObject> m_vChilds;
};