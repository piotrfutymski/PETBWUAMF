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


}