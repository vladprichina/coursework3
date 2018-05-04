#pragma once

DECLARE_SMART(File, spFile);
class File : public BaseObject
{
public:
	File() {}
	File(const std::wstring & srName, const std::wstring & srIconName, const std::wstring & srAddName, float fSize);
	virtual ~File();

	//getters
	virtual float GetSize() override							{ return m_fSize; }

	//setters
	void SetAddName( std::wstring newName )						{ m_srAddName = newName;}

	

private:
	float				m_fSize;
};