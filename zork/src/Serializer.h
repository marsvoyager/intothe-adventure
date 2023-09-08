#pragma once

namespace MRK_UTIL
{
class Serializer{
public:
	virtual ~Serializer(){}
	virtual void serialize(std::ostream &){}
	virtual void serialize_cin(){}
	virtual void deserialize(std::fstream &){}
	virtual void deserialize_cin(std::istream &){}
};
}