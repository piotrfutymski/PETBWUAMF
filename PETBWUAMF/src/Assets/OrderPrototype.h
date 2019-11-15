#pragma once
#include <functional>
#include "Asset.h"

class Unit;
class Move;

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
	virtual void loadAsset(const nlohmann::json & assetFile) override;

	void set_canBeUsed(const std::function<bool(Unit*)> &);
	void set_getProperTargets(const std::function<std::vector<Target>(const Unit *, int, const Move & m)> &);
	void set_execute(const std::function<bool(Unit *, const Move &)> &);

public:

	std::function<bool(Unit * )> _canBeUsed;
	std::function<std::vector<Target>(const Unit *, int, const Move & m)> _getProperTargets;
	std::function<bool(Unit *, const Move &)> _execute;

	bool _canBeUsedOnAllUnit;
	std::vector <std::string> _allowedTypes;
	std::vector <std::string> _allowedUnits;

	std::vector<TargetType> _targets;
	std::string _description;

	std::string _texture;
	std::string _icon;

};
