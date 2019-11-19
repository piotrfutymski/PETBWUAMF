#include "BuffPrototype.h"

void BuffPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_forAlways = assetFile["always"];
	
	for (auto it = assetFile.begin(); it != assetFile.end(); ++it) 
	{
		if (it.key() == "attack")
			_attack = it.value();
		if (it.key() == "defence")
			_defence = it.value();
		if (it.key() == "armor")
			_armor = it.value();
		if (it.key() == "health")
			_health = it.value();
		if (it.key() == "rangedAttack")
			_rangedAttack = it.value();
		if (it.key() == "rangedRange")
			_range = it.value();
		if (it.key() == "chargeAttack")
			_chargeAttack = it.value();
		if (it.key() == "chargeDefence")
			_chargeDefence = it.value();
		if (it.key() == "move")
			_move = it.value();
		if (it.key() == "morale")
			_morale = it.value();
		if (it.key() == "formationSize")
			_formationSize = it.value();
	}

}
