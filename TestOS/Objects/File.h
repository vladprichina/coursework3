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
	
private:
	float				m_fSize;
};