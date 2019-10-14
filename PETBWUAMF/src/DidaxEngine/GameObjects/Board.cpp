#include "Board.h"

namespace Didax
{

Board::Board(Engine * eng):GameObject(eng)
{
}

Board::~Board()
{
}

Canvas * Board::openMainGUI(AssetMeneger * assets)
{
	auto res = this->addGUI<MainGUI>("MainGUI", assets);
	bool tab[16] = { true,false,true,true,false,false,false,false,true,true,false,true,false,true,true,true };
	this->getGUI<MainGUI>("MainGUI")->setReadyToChoose(tab, MainGUI::YellowSide::left);
	return res;
}

Canvas * Board::openSideGUI(AssetMeneger * assets)
{
	auto res = this->addGUI<SideGUI>("SideGUI", assets);
	auto hgl = this->getGUI<SideGUI>("SideGUI");
	hgl->setOnHourglassClicked([this, hgl]() {
		auto e = this->getParent();
		e->nextPhase();
		hgl->startHourglassOnState((int)e->getPhase());
	});
	hgl->setOnExitButtonClicked([this, hgl]() {
		this->getParent()->endGame();
	});
	return res;
}

}