#pragma once
#include "Game.h"

class PrototypeInitializer
{
public:

	static Game * game;

	static void initGame(Game * g);

	static void initPrototypes();

	static std::vector<OrderPrototype::Target> getPosibleMoves(const Unit * u);
	static std::vector<OrderPrototype::Target> getPossibleFightTargets(const Unit * u);
	static void move(Unit * u, const sf::Vector2i & pos);
	static void attack(Unit * u, size_t en);

	static bool canBeUsedOnUnit(const OrderPrototype* o, const Unit * u);

	static void initOrders();
	static void initBuffs();

};
