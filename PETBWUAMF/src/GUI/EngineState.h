#pragma once

namespace Didax
{
	class Order;
	class Unit;

struct EngineState
{
public:

	enum class TurnPhase {
		BeforeStart = -1, FirstPlayerMove, PlayingFirstPlayerMoves, SecondPlayerMove, PlayingSecondPlayerMoves, End
	};

	TurnPhase _turnPhase{TurnPhase::BeforeStart};
	bool _endGame{ false };

	// setting order to unit

	Order *_choosedOrder{nullptr};
	Unit * _choosedOrderTarget{nullptr};
	std::vector<int> _choosedSpots;
	std::vector<Unit *> _choosedUnits;
};

}