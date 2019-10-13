#pragma once
#include "GameObject.h"
#include "../Engine.h"
#include "../GUI/SideGUI.h"
#include "../GUI/MainGUI.h"

namespace Didax
{

class Board :
	public GameObject
{
public:
	Board(Engine * eng);
	~Board();

	Canvas * openMainGUI(AssetMeneger * assets);
	Canvas * openSideGUI(AssetMeneger * assets);

};

}