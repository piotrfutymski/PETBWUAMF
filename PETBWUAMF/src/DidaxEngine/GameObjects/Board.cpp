#include "Board.h"

namespace Didax
{

Board::Board(Engine * eng):GameObject(eng)
{
}

Board::~Board()
{
}

Canvas * Board::openBoardGUI(AssetMeneger * assets)
{
	auto res = this->openGUI<BoardGUI>("BoardGUI", assets);
	bool tab[16] = { true,false,true,true,false,false,false,false,true,true,false,true,false,true,true,true };
	this->getGUI<BoardGUI>("BoardGUI")->setReadyToChoose(tab);
	return res;
}

void Board::addUnitOnPos(int p)
{
	if (_units[p] == nullptr)
		_units[p];
}


}