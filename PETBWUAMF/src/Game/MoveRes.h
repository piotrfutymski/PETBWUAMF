#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Unit.h"

struct MoveRes
{
	std::vector<std::pair<size_t, sf::Vector2i>> _unitsMoved;
	std::vector < std::pair<size_t, int>> _demageDealt;
	std::vector < std::tuple<size_t, Unit::UParameter, int>> _buffs;
	std::vector < std::tuple<size_t, Unit::UParameter, int>> _deBuffs;


	MoveRes operator+ (const MoveRes & r)
	{
		MoveRes res;

		res._unitsMoved = this->_unitsMoved;
		res._demageDealt = this->_demageDealt;
		res._buffs = this->_buffs;
		res._deBuffs = this->_deBuffs;

		res._unitsMoved.insert(res._unitsMoved.end(), r._unitsMoved.begin(), r._unitsMoved.end());
		res._demageDealt.insert(res._demageDealt.end(), r._demageDealt.begin(), r._demageDealt.end());
		res._buffs.insert(res._buffs.end(), r._buffs.begin(), r._buffs.end());
		res._deBuffs.insert(res._deBuffs.end(), r._deBuffs.begin(), r._deBuffs.end());

		return res;
	}
};

