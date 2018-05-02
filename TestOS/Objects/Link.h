#pragma once

DECLARE_SMART(Link, spLink);
class Link : public BaseObject
{
public:
	Link();
	virtual~Link();

	virtual float GetSize() override;

private:
	spBaseObject		m_pRefObject;		// объект, на который ссылаемся
};

