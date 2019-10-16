#pragma once
#include "GameObject.h"
#include "../Engine.h"
#include "../GUI/BoardGUI.h"

namespace Didax
{
class Unit;

class Board :
	public GameObject
{
public:
	Board(Engine * eng);
	~Board();

	Canvas * openBoardGUI(AssetMeneger * assets);

	void addUnitOnPos(int p);

private:

	Unit * _units[16];

};

}