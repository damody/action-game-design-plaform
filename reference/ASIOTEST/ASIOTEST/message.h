#pragma once

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class message
{
public:
	char sender[64];
	char text[256];
	char time[32];

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & sender;
		ar & text;
		ar & time;
	}
};