#pragma once
#include "GameObject.h"
#include "../GUI/Hourglass.h"
#include "../Engine.h"

namespace Didax
{

class Board :
	public GameObject
{
public:
	Board(Engine * eng);
	~Board();

	Canvas * openHourglass(AssetMeneger * assets);

};

}