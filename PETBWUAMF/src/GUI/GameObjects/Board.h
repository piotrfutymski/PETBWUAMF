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

	//GUI

	void unsetChoosable();
	void setCHoosable(const bool posTab[16]);

	static void setFunctions(const std::map<std::string, std::function<void(int)>> & f);

private:

	static std::map<std::string, std::function<void(int)>> _functions;

	std::array<Unit *, 16> _units;

};

}