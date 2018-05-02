#pragma once

DECLARE_SMART(File, spFile);
class File : public BaseObject
{
public:
	File() {}
	File(const std::string & srName, const std::string & srIconName, const std::string & srAddName, float fSize);
	virtual ~File();

	//getters
	virtual std::string GetAddName()							{ return m_srAddName; }

	//setters
	void SetAddName( std::string newName )				{ m_srAddName = newName;}

	virtual float GetSize() override					{ return m_fSize; }

private:
	std::string		m_srAddName;
	float			m_fSize;
};