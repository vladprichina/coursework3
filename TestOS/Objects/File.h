#pragma once

DECLARE_SMART(File, spFile);
class File : public BaseObject
{
public:
	File() {}
	File(const std::wstring & srName, const std::wstring & srIconName, const std::wstring & srAddName, float fSize);
	virtual ~File();

	//getters
	virtual std::wstring GetAddName()							{ return m_srAddName; }

	//setters
	void SetAddName( std::wstring newName )						{ m_srAddName = newName;}

	virtual float GetSize() override							{ return m_fSize; }

private:
	std::wstring		m_srAddName;
	float				m_fSize;
};