#pragma once
#define GET_CLASS_SIZE(classname) \
	inline size_t GetClassSize() \
	{ \
	return sizeof(classname); \
	}
#define VIRTUAL_GET_CLASS_SIZE(classname) \
	virtual size_t GetClassSize() \
	{ \
		return sizeof(classname); \
	}