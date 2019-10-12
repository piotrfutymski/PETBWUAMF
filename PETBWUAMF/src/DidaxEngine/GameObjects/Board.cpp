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
	//auto res = this->addGUI<MainGUI>("MainGUI", assets);
	return nullptr;
}

Canvas * Board::openSideGUI(AssetMeneger * assets)
{
	auto res = this->addGUI<SideGUI>("SideGUI", assets);
	auto hgl = static_cast<SideGUI *>(_representation["SideGUI"].get());
	hgl->setOnHourglassClicked([this]()->int {
		auto e = this->getParent();
		e->nextPhase();
		return (int)e->getPhase();
	});
	return res;
}

}