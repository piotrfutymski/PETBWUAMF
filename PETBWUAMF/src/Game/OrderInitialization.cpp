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

	p->set_getProperTargets([this](Unit * u,int n) {
		auto res = std::vector<OrderPrototype::Target>();
		if (n != 0)
			return res;
		auto& units = this->getHolder<Unit>();
		if (u->isRanged())
		{
			for (size_t i = 0; i < units.size(); i++)
			{
				res.push_back({ OrderPrototype::TargetType::Unit_target, {0,0}, units[i]->getID() });
			}
		}
		else
		{
			for (auto & x : u->getEnemyInFightWhith())
			{
				res.push_back({ OrderPrototype::TargetType::Unit_target, {0,0}, x });
			}
		}
		return std::move(res);
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

	p->set_getProperTargets([this](Unit * u, int n) {
		auto res = std::vector<OrderPrototype::Target>();
		if (n != 0)
			return res;
		PathFinder pathFinder(Unit::MAXPOS.x+1, Unit::MAXPOS.y+1);
		int ow = u->getOwner();
		for (auto & x: _units)
		{
			if (x->getOwner() == ow)
				pathFinder.addAllay(x->getPosition());
			else
				pathFinder.addEnemy(x->getPosition());
		}

		for (auto el: pathFinder.getGoodPositions(u->getPosition(), u->getMove()) )
		{
			if (el.second == true)
				res.push_back({ OrderPrototype::TargetType::Position_target, {el.first / 1000, el.first % 1000 }, 0});
		}

		return std::move(res);
	});


	p->set_execute([this](Unit * u, const Move & m) {
		
		for (auto neight : this->getNeightbours(u))
		{
			if(neight->getOwner() != u->getOwner())
				neight->removeInFightWith(u->getID());
		}
		u->setPosition(m.positions[0]);
		auto neights = std::vector<size_t>();
		for (auto neight : this->getNeightbours(u))
		{
			if (neight->getOwner() != u->getOwner())
			{
				neight->addInFightWith(u->getID());
				neights.push_back(neight->getID());
			}		
		}
		u->setInFightWith(neights);
		return true;
	});


	//CHARGE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("charge");

	p->set_canBeUsed([this](Unit * u)
	{
		return false;
	});

	//PREPARE
	p = Didax::AssetMeneger::getAsset<OrderPrototype>("prepare");

	p->set_canBeUsed([this](Unit * u)
	{
		return false;
	});

	//HELP

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("help");

	p->set_canBeUsed([this](Unit * u)
	{
		return false;
	});


}