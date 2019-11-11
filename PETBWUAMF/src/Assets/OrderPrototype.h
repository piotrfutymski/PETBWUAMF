#pragma once
#include <functional>
#include "Asset.h"

class Unit;
class Move;

class OrderPrototype :public Asset
{
public:

	enum Target
	{
		Position_target, Unit_target
	};

	OrderPrototype(const std::string & name) :Asset(name) {};
	~OrderPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

	void set_canBeUsed(const std::function<bool(Unit*)> &);
	void set_isProperAsTargetP(const std::function<bool(Unit *, int, const sf::Vector2i &)> &);
	void set_isProperAsTargetU(const std::function<bool(Unit *, int, size_t)> &);
	void set_execute(const std::function<bool(Unit *, const Move &)> &);

public:

	std::function<bool(Unit * )> _canBeUsed;
	std::function<bool(Unit * , int , const sf::Vector2i &)> _isProperAsTargetP;
	std::function<bool(Unit * , int , size_t)> _isProperAsTargetU;
	std::function<bool(Unit *, const Move &)> _execute;

	std::vector<Target> _targets;
	std::string _description;

	std::string _texture;
	std::string _icon;

};
