#pragma once
#include "GameObject.h"

namespace Didax
{

class Unit :
	public GameObject
{
public:
	Unit(Engine * eng);
	~Unit();
};

}