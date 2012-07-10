#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define SHARE_PTR(x) \
	typedef boost::shared_ptr<x>	x##_Sptr; \
	typedef boost::ptr_vector<x>	x##_Sptrs; \
	typedef std::vector<x>		x##_Vector; \
	typedef x*			x##_RawPtr; \
	typedef std::vector<x*>		x##_RawPtrs;

#define INTRUSIVE_PTR(x) \
	typedef boost::shared_ptr<x>	   x##_Iptr; \
	void intrusive_ptr_add_ref(x *p)   \
	{   \
		p->AddRef();   \
	}   \
	void intrusive_ptr_release(x *p)   \
	{   \
		p->Release();   \
	}

static struct
{
	template<class T> operator boost::shared_ptr<T> ()
	{
		return boost::shared_ptr<T> (new T);
	}
}
SharePtrNew;



