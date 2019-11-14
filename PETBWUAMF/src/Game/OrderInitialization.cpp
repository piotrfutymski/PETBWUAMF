#include "Game.h"


void Game::initPrototypes()
{

	//ATTACK

	auto p = Didax::AssetMeneger::getAsset<OrderPrototype>("attack");

	p->set_canBeUsed([this](Unit * u)
	{
		auto & units = this->getHolder<Unit>();
		if (u->isRanged())
		{
			for (size_t i = 0; i < units.size(); i++)
			{
				if (u->getOwner() != units[i]->getOwner() && u->getDistanceTo(units[i].get()) <= u->getRangedRange())
					return true;
			}
		}
		else
		{
			if (u->isInFight())
				return true;
		}
		return false;
	});

	p->set_getProperTargets([this](const Unit * u,int n) {
		auto res = std::vector<OrderPrototype::Target>();
		if (n != 0)
			return res;
		auto& units = this->getHolder<Unit>();
		if (u->isRanged())
		{
			for (size_t i = 0; i < units.size(); i++)
			{
				if (u->getOwner() != units[i]->getOwner() && u->getDistanceTo(units[i].get()) <= u->getRangedRange())
					res.push_back({ OrderPrototype::TargetType::Unit_target, units[i]->getPosition(), units[i]->getID() });
			}
		}
		else
		{
			for (auto & x : u->getEnemyInFightWhith())
			{
				res.push_back({ OrderPrototype::TargetType::Unit_target, this->getObject<Unit>(x)->getPosition(), x });
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

	p->set_getProperTargets([this](const Unit * u, int n) {
		auto res = std::vector<OrderPrototype::Target>();
		if (n != 0)
			return res;

		auto paths = this->getMap().getPaths(u->getID(), u->getMove());

		for (auto & el: paths )
		{
				res.push_back({ OrderPrototype::TargetType::Position_target, el, 0});
		}
		return std::move(res);
	});


	p->set_execute([this](Unit * u, const Move & m) {
		
		for (auto neight : this->getNeightbours(u))
		{
			if(neight->getOwner() != u->getOwner())
				neight->removeInFightWith(u->getID());
		}
		this->getMap().moveUnitFromPosition(u->getPosition(), m.positions[0]);
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