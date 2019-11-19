#pragma once
#include <functional>
#include "Asset.h"

class Unit;
struct Move;
struct MoveRes;

class OrderPrototype :public Asset
{
public:

	enum TargetType
	{
		MoveT, AttackT, ChargeT, BuffT, BuffAllayT, BuffEnemyT, CreateT
	};


	OrderPrototype(const std::string & name) :Asset(name) {};
	~OrderPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

	void set_execute(const std::function<MoveRes(Unit *, const Move &)> &);

public:

	std::function<MoveRes(Unit *, const Move &)> _execute;

	bool _canBeUsedOnAllUnit;
	std::vector <std::string> _allowedTypes;
	std::vector <std::string> _allowedUnits;

	TargetType _target;
	int _targetCount;
	int _cost;
	int _useNum;

	std::string _description;
	std::string _texture;
	std::string _icon;

};
