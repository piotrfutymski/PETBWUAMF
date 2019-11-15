#include "PrototypeInitializer.h"

Game * PrototypeInitializer::game = nullptr;

void PrototypeInitializer::initGame(Game * g)
{
	game = g;
}

void PrototypeInitializer::initPrototypes()
{
	auto p = Didax::AssetMeneger::getAsset<OrderPrototype>("attack");
	auto g = game;

	p->set_canBeUsed([](Unit * u)
	{
		if (PrototypeInitializer::getPossibleFightTargets(u).size() != 0)
			return true;
		return false;
	});

	p->set_getProperTargets([](const Unit * u, int n) {
		if (n != 0)
			return std::vector<OrderPrototype::Target>();
		return std::move(PrototypeInitializer::getPossibleFightTargets(u));
	});

	p->set_execute([](Unit * u, const Move & m) {
		PrototypeInitializer::attack(u, m);
		return true;
	});

	//MOVE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("move");

	p->set_canBeUsed([](Unit * u)
	{
		return true;
	});

	p->set_getProperTargets([](const Unit * u, int n) {
		if (n != 0)
			return std::vector<OrderPrototype::Target>();
		return std::move(PrototypeInitializer::getPosibleMoves(u));
	});

	p->set_execute([](Unit * u, const Move & m) {
		PrototypeInitializer::move(u, m);
		return true;
	});


	//CHARGE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("charge");

	p->set_canBeUsed([](Unit * u)
	{
		return false;
	});

	//PREPARE
	p = Didax::AssetMeneger::getAsset<OrderPrototype>("prepare");

	p->set_canBeUsed([](Unit * u)
	{
		return false;
	});

	//HELP

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("help");

	p->set_canBeUsed([](Unit * u)
	{
		return false;
	});
}

std::vector<OrderPrototype::Target> PrototypeInitializer::getPosibleMoves(const Unit * u)
{
	auto res = std::vector<OrderPrototype::Target>();
	auto paths = game->getMap().getPaths(u->getID(), u->getMove());

	for (auto & el : paths)
	{
		res.push_back({ OrderPrototype::TargetType::Position_target, el, 0 });
	}
	return std::move(res);
}

std::vector<OrderPrototype::Target> PrototypeInitializer::getPossibleFightTargets(const Unit * u)
{
	auto res = std::vector<OrderPrototype::Target>();
	auto& units = game->getHolder<Unit>();
	if (u->hasFlag(Unit::UFlag::Ranged))
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
			res.push_back({ OrderPrototype::TargetType::Unit_target, game->getObject<Unit>(x)->getPosition(), x });
		}
	}
	return res;
}

void PrototypeInitializer::move(Unit * u, const Move & m)
{
	for (auto neight : game->getNeightbours(u))
	{
		if (neight->getOwner() != u->getOwner())
			neight->removeInFightWith(u->getID());
	}
	game->getMap().moveUnitFromPosition(u->getPosition(), m.positions[0]);
	u->setPosition(m.positions[0]);
	auto neights = std::vector<size_t>();
	for (auto neight : game->getNeightbours(u))
	{
		if (neight->getOwner() != u->getOwner())
		{
			neight->addInFightWith(u->getID());
			neights.push_back(neight->getID());
		}
	}
	u->setInFightWith(neights);
}

void PrototypeInitializer::attack(Unit * u, const Move & m)
{
	if (u->hasFlag(Unit::UFlag::Ranged))
		u->rangedAttack(game->getObject<Unit>(m.units[0]));
	else
		u->normalAttack(game->getObject<Unit>(m.units[0]));
}
