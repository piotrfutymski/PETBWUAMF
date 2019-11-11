#include "Game.h"


void Game::initPrototypes()
{

	//ATTACK

	auto p = Didax::AssetMeneger::getAsset<OrderPrototype>("attack");

	p->set_canBeUsed([this](Unit * u)
	{
		if (u->isRanged())
			return true;
		else
		{
			if (u->isInFight())
				return true;
		}
		return false;
	});

	p->set_isProperAsTargetP([](Unit * u,int n, const sf::Vector2i & pos) {
		return false;
	});

	p->set_isProperAsTargetU([](Unit * u, int n, size_t tar) {
		if (n != 0)
			return false;
		if (u->isInFightWith(tar))
			return true;
		return false;
	});

	p->set_execute([this](Unit * u, const Move & m) {
		if (u->isRanged())
			u->rangedAttack(this->getObject<Unit>(m.units[0]));
		else
			u->normalAttack(this->getObject<Unit>(m.units[0]));
		return true;
	});

	//MOVE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("move");

	p->set_canBeUsed([this](Unit * u)
	{
		return true;
	});

	p->set_isProperAsTargetP([this](Unit * u, int n, const sf::Vector2i & pos) {
		if (n != 0)
			return false;
		PathFinder pathFinder(Unit::MAXPOS.x+1, Unit::MAXPOS.y+1);
		int ow = u->getOwner();
		for (auto & x: _units)
		{
			if (x->getOwner() == ow)
				pathFinder.addAllay(x->getPosition());
			else
				pathFinder.addEnemy(x->getPosition());
		}

		return pathFinder.pathExist(u->getPosition(), pos, u->getMove());
	});

	p->set_isProperAsTargetU([](Unit * u, int n, size_t tar) {
		return false;
	});

	p->set_execute([this, p](Unit * u, const Move & m) {
		if (p->_isProperAsTargetP(u, 0, m.positions[0]))
		{
			u->setPosition(m.positions[0]);
			return true;
		}
		return false;
	});

}