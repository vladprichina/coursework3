#pragma once
#include "intrusive_ptr.h"

class ref_counter
{
public:
	int _ref_counter;

	bool m_SkipSP;

	ref_counter() : _ref_counter(0), m_SkipSP() {}
	virtual ~ref_counter() {}

	void addRef()
	{
		++_ref_counter;
	}

	void releaseRef()
	{
		if (m_SkipSP)
			return;

		if (0 == --_ref_counter)
			delete this;
	}

	void setRef(int ref)
	{
		_ref_counter = ref;
	}

	void OffSmartPointerProp()
	{
		// небезопасно 
		m_SkipSP = true;
	}

private:
	ref_counter(const ref_counter&);
};


inline void intrusive_ptr_add_ref(ref_counter* p)
{
	p->addRef();
}

inline void intrusive_ptr_release(ref_counter* p)
{
	p->releaseRef();
}

#define DECLARE_SMART(class_name, spname) class class_name;\
	typedef intrusive_ptr<class_name> spname;
