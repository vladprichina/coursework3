#pragma once

enum eTypeLink
{
	eNone = 0,
	eHard = 1,
	eSymbol = 2,
};

DECLARE_SMART(Link, spLink);
class Link : public BaseObject
{
public:
	Link(std::wstring srName, eTypeLink eType, spBaseObject pRef );
	virtual~Link();

	virtual float			GetSize() override;
	virtual spBaseObject	IsOpen()  override;
	virtual void			DeleteThis() override;
	virtual void			SetLink(spBaseObject pRef)			{ m_pRefObject = pRef; }

private:
	spBaseObject			m_pRefObject;		// объект, на который ссылаемся
	eTypeLink				m_eLinkType;
};

