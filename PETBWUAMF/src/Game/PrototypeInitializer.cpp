#include "Game.h"

void Game::initOrderFunctions()
{
	// ATTACK

	auto p = Didax::AssetMeneger::getAsset<OrderPrototype>("attack");

	p->_execute = [](Game * game, const Move & m) {
		return game->fight(game->getActiveUnitID(), m.units[0], Game::AttackType::Normal);
	};

	// MOVE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("move");
	p->_execute = [](Game * game, const Move & m) {
		return game->moveUnit(game->getActiveUnitID(), m.positions[0]);
	};

	// CHARGE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("charge");
	p->_execute = [](Game * game, const Move & m) {
		auto a = game->moveUnit(game->getActiveUnitID(), m.positions[0]);
		auto b = game->fight(game->getActiveUnitID(), m.units[0], Game::AttackType::Charge);
		return a + b;
	};

	// PREPARE

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("prepare");
	p->_execute = [](Game * game, const Move & m) {
		return game->buff("prepare", game->getActiveUnitID());
	};

	// BLEEDING ATTACK

	p = Didax::AssetMeneger::getAsset<OrderPrototype>("bleedingAttack");
	p->_execute = [](Game * game, const Move & m) {
		auto a = game->fight(game->getActiveUnitID(), m.units[0], Game::AttackType::Normal);
		auto b = game->buff("bleeding", m.units[0], a.getEventOfType(MoveRes::EventType::DMGTaken).dmg);
		return a + b;
	};

}
