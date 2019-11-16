#pragma once
#include "../Game/Game.h"

class Reporter
{
public:
	Reporter();
	~Reporter() {};

	void SaveTurn(MoveRes data);
	MoveRes getLastTurn()const;
	MoveRes getTurn(int number)const;
	std::vector<MoveRes> getAllTurns()const;

private:
	std::vector<MoveRes> _turnReport;
};