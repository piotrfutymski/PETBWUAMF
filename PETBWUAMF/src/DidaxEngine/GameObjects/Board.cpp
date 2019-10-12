#include "Board.h"

namespace Didax
{

Board::Board(Engine * eng):GameObject(eng)
{
}

Board::~Board()
{
}

Canvas * Board::openHourglass(AssetMeneger * assets)
{
	auto res = this->addGUI<Hourglass>("Hourglass", assets);
	auto hgl = static_cast<Hourglass *>(_representation["Hourglass"].get());
	hgl->setOnStateChanged([this]() {
		auto e = this->getParent();
		e->changeState(Engine::EngineState::FirstPlayerMove);
	});
	return res;
}

}