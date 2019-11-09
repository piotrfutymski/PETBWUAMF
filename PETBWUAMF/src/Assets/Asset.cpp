#include "Asset.h"



Asset::Asset(const std::string & name)
{
	_name = name;
}

Asset::~Asset()
{
}

const std::string & Asset::getName()const
{
	return _name;
}

