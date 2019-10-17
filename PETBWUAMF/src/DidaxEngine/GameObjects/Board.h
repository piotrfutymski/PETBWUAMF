#pragma once
#include "GameObject.h"
#include "../GUI/BoardGUI.h"
#include <array>

namespace Didax
{
class Unit;

class Board :
	public GameObject
{
public:
	Board(AssetMeneger * assets);
	~Board();

	void addUnitOnPos(Unit * u, int pos);
	void moveUnit(Unit *u, int targetPos);
	void removeUnits(Unit * u);


private:

	std::array<Unit *, 16> _units;

};

}