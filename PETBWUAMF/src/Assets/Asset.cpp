#include "Asset.h"



Asset::Asset(const std::string & name)
{
	_name = name;
}

Asset::~Asset()
{
}

const std::string & Asset::getName()
{
	return _name;
}

