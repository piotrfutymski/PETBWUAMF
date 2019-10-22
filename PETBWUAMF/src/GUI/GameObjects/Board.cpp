#include "Board.h"

namespace Didax
{

Board::Board(AssetMeneger *assets)
{
	this->createGUI<BoardGUI>("BoardGUI", assets);
}

Board::~Board()
{
}

void Board::addUnitOnPos(Unit * u, int p)
{
	if (_units[p] == nullptr)
		_units[p] = u;
}

void Board::moveUnit(Unit * u, int targetPos)
{

}

void Board::removeUnits(Unit * u)
{
}

void Board::unsetChoosable()
{
	for (size_t i = 0; i < 16; i++)
	{
		_representation->unactiveButton("Pos" + std::to_string(i));
		static_cast<BoardGUI *>(_representation.get())->unsetReadyToChoose();
	}
}

void Board::setCHoosable(const bool posTab[16])
{
	for (size_t i = 0; i < 16; i++)
	{
		if (!posTab[i])
			continue;
		_representation->backToEmptyButton("Pos" +std::to_string(i));
		_representation->setOnPressToButton("Pos" + std::to_string(i), [i] {_functions["chooseSpot"](i); });
		static_cast<BoardGUI *>(_representation.get())->setReadyToChoose(posTab);
	}
}

void Board::setFunctions(const std::map<std::string, std::function<void(int)>>& f)
{
	_functions = f;
}


}