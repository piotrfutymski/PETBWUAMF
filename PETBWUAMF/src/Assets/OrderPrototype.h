#pragma once
#include <functional>
#include "Asset.h"

class Unit;
class Move;
class MoveRes;

class OrderPrototype :public Asset
{
public:

	enum TargetType
	{
		Position_target, Unit_target
	};

	struct Target
	{
		TargetType type;
		sf::Vector2i pos;
		size_t targetID;
	};

	OrderPrototype(const std::string & name) :Asset(name) {};
	~OrderPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override; /* Loads data from asset file*/

	void set_canBeUsed(const std::function<bool(Unit*)> &); /* Sets flag, by using lambda, if order can be used now*/
	void set_getProperTargets(const std::function<std::vector<Target>(const Unit *, int, const Move & m)> &); /* Gets all possible targets, using lambda */
	void set_execute(const std::function<MoveRes(Unit *, const Move &)> &);/* Executes order, using lambda*/

public:

	std::function<bool(Unit * )> _canBeUsed;
	std::function<std::vector<Target>(const Unit *, int, const Move & m)> _getProperTargets;
	std::function<MoveRes(Unit *, const Move &)> _execute;

	bool _canBeUsedOnAllUnit;
	std::vector <std::string> _allowedTypes;
	std::vector <std::string> _allowedUnits;
	std::vector <std::string> _allowedFactions;

	std::vector<TargetType> _targets;
	std::string _description;
	std::string _orderType;
	std::vector<std::string> _buffs;

	std::string _texture;
	std::string _icon;

};
