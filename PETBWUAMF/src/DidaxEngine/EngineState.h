#pragma once

namespace Didax
{

struct EngineState
{
public:

	enum class TurnPhase {
		BeforeStart = -1, FirstPlayerMove, SecondPlayerMove, PlayingMoves, End
	};

	TurnPhase _turnPhase{TurnPhase::BeforeStart};
	bool _endGame{ false };
};

}