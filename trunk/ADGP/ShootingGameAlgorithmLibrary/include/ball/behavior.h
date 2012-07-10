#pragma once
#include "common/shared_ptr.h"
#include <boost/functional/hash.hpp>

static boost::hash<std::string> strhasher;

class Ball;
class Behavior
{
public:
	size_t	m_typehash;
	virtual ~Behavior(){}
	virtual int UpdateBall(Ball* b, float elapsedtime) = 0;
};
SHARE_PTR(Behavior)

