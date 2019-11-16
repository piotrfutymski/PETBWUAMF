#include "PrototypeInitializer.h"

Game * PrototypeInitializer::game = nullptr;

void PrototypeInitializer::initGame(Game * g)
{
	game = g;
}

void PrototypeInitializer::initPrototypes()
{
	initOrders();
	initBuffs();
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

MoveRes PrototypeInitializer::move(Unit * u, const sf::Vector2i & pos)
{
	for (auto neight : game->getNeightbours(u))
	{
		if (neight->getOwner() != u->getOwner())
			neight->removeInFightWith(u->getID());
	}
	game->getMap().moveUnitFromPosition(u->getPosition(), pos);
	u->setPosition(pos);
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

	return { {{u->getID(), pos}},{},{},{} };
}

MoveRes PrototypeInitializer::attack(Unit * u, size_t en)
{
	auto enemy = game->getObject<Unit>(en);
	auto startH = enemy->getHealth();
	if (u->hasFlag(Unit::UFlag::Ranged))
		u->rangedAttack(enemy);
	else
		u->normalAttack(enemy);

	auto endH = enemy->getHealth();

	return{ {},{{en, endH - startH}},{},{} };
}

bool PrototypeInitializer::canBeUsedOnUnit(const OrderPrototype * o, const Unit * u)
{
	auto uprot = u->getPrototype();
	if (o->_canBeUsedOnAllUnit)
		return true;
	if (std::find(o->_allowedTypes.begin(), o->_allowedTypes.end(), uprot->_unitType) != o->_allowedTypes.end())
		return true;
	if (std::find(o->_allowedUnits.begin(), o->_allowedUnits.end(), uprot->getName()) != o->_allowedUnits.end())
		return true;
	return false;
}

void PrototypeInitializer::initOrders()
{
	auto p = Didax::AssetMeneger::getAsset<OrderPrototype>("attack");
	auto g = game;

	p->set_canBeUsed([p](Unit * u)
	{
		if (PrototypeInitializer::getPossibleFightTargets(u).size() != 0 && PrototypeInitializer::canBeUsedOnUnit(p, u))
			return true;
		return false;
	});

	p->set_getProperTargets([](const Unit * u, int n, const Move & m) {
		if (n != 0)
			return std::vector<OrderPrototype::Target>();
		return std::move(PrototypeInitializer::getPossibleFightTargets(u));
	});

	p->set_execute([](Unit * u, const Move & m) {
		return PrototypeInitializer::attack(u, m.units[0]);
	});

	//MOVE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("move");

	p->set_canBeUsed([p](Unit * u)
	{
		if (PrototypeInitializer::canBeUsedOnUnit(p, u))
			return true;
		return false;
	});

	p->set_getProperTargets([](const Unit * u, int n, const Move & m) {
		if (n != 0)
			return std::vector<OrderPrototype::Target>();
		return std::move(PrototypeInitializer::getPosibleMoves(u));
	});

	p->set_execute([](Unit * u, const Move & m) {
		return PrototypeInitializer::move(u, m.positions[0]);
	});


	//CHARGE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("charge");

	p->set_canBeUsed([=](Unit * u)
	{
		if (u->hasFlag(Unit::UFlag::Ranged))
			return false;
		if (g->getMap().posInFightAfterMove(u->getID(), u->getMove()).size() != 0)
			return true;
		return false;
	});
	p->set_getProperTargets([=](const Unit * u, int n, const Move & m) {
		auto res = std::vector<OrderPrototype::Target>();
		if (n == 0)
		{
			auto pos = g->getMap().posInFightAfterMove(u->getID(), u->getMove());
			for (auto & x: pos)
			{
				res.push_back({ OrderPrototype::TargetType::Position_target,x, 0 });
			}
			return res;
		}
		else if (n == 1)
		{
			auto nei = g->getMap().getNeightboursOfPos(m.positions[0]);
			for (auto & x : nei)
			{
				if (x.second != u->getOwner())
				{
					auto unit = g->getObject<Unit>(x.first);
					res.push_back({ OrderPrototype::TargetType::Unit_target,unit->getPosition(), unit->getID() });
				}				
			}
			return res;
		}
		return std::vector<OrderPrototype::Target>();
	});

	p->set_execute([=](Unit * u, const Move & m) {
		g->addBuff("chargeBoost", u->getID());
		auto a = PrototypeInitializer::move(u, m.positions[0]);
		auto b = PrototypeInitializer::attack(u, m.units[0]);
		return a+b;
	});


	//PREPARE
	p = Didax::AssetMeneger::getAsset<OrderPrototype>("prepare");

	p->set_canBeUsed([p](Unit * u)
	{
		if (PrototypeInitializer::canBeUsedOnUnit(p, u))
			return true;
		return false;
	});
	p->set_getProperTargets([=](const Unit * u, int n, const Move & m)
	{
		return std::vector<OrderPrototype::Target>();
	});
	p->set_execute([=](Unit * u, const Move & m) {
		g->addBuff("prepareBoost", u->getID());
		return (MoveRes{ {},{},{{u->getID(),Unit::UParameter::Armor, u->getChargeDefence() }},{} });
	});

	//HELP

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("help");

	p->set_canBeUsed([p](Unit * u)
	{
		if (PrototypeInitializer::canBeUsedOnUnit(p, u))
			return true;
		return false;
	});
	p->set_getProperTargets([=](const Unit * u, int n, const Move & m)
	{
		auto res = std::vector<OrderPrototype::Target>();
		if (n != 0)
			return res;
		for (auto & x : g->getHolder<Unit>())
		{
			if (x->getOwner() == u->getOwner() && x.get()!=u)
				res.push_back({ OrderPrototype::TargetType::Unit_target,u->getPosition(), u->getID() });

		}
		return res;
	});
	p->set_execute([=](Unit * u, const Move & m) {
		g->getObject<Unit>(m.units[0])->upgradeParameter(Unit::UParameter::Health, 5);
		return (MoveRes{ {},{},{{u->getID(), Unit::UParameter::Health, 5 }},{} });
	});
}

void PrototypeInitializer::initBuffs()
{
	auto p = Didax::AssetMeneger::getAsset<BuffPrototype>("prepareBoost");
	auto g = game;

	//Prepare

	p->_onBegin = [=](size_t u, Buff * buff)
	{
		auto unit = g->getObject<Unit>(u);
		buff->setBoostValue(unit->getChargeDefence());
		unit->upgradeParameter(Unit::UParameter::Armor, unit->getChargeDefence());
	};

	p->_onTurnEnd = [=](size_t u, Buff * buff) {};
	p->_onEnd = [=](size_t u, Buff * buff)
	{
		auto unit = g->getObject<Unit>(u);
		unit->upgradeParameter(Unit::UParameter::Armor, -buff->getBoostValue());
	};

	//Charge

	p = Didax::AssetMeneger::getAsset<BuffPrototype>("chargeBoost");
	p->_onBegin = [=](size_t u, Buff * buff)
	{
		auto unit = g->getObject<Unit>(u);
		buff->setBoostValue(unit->getChargeAttack());
		unit->upgradeParameter(Unit::UParameter::Attack, unit->getChargeAttack());
	};
	p->_onTurnEnd = [=](size_t u, Buff * buff) {};
	p->_onEnd = [=](size_t u, Buff * buff)
	{
		auto unit = g->getObject<Unit>(u);
		unit->upgradeParameter(Unit::UParameter::Attack, -buff->getBoostValue());
	};
	
}
