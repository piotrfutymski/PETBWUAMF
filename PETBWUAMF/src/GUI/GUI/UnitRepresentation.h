#pragma once
#include "GUIElement.h"

namespace Didax
{

class UnitRepresentation:  public GUIElement
{
public:
	enum class ParameterColor {
		green, white, red
	};

	UnitRepresentation(GUIElementPrototype * prototype);
	~UnitRepresentation();

	void setUnit(const std::string & name, AssetMeneger * assets);
	void resetUnit();
	void setOrderToUnit(const std::string & name, AssetMeneger * assets, int nr);

	void setAttack(const ParameterColor & p, int v);
	void setDefence(const ParameterColor & p, int v);
	void setHealth(const ParameterColor & p, int v);

	void setPosition(int pos);


private:

	TextArea * _attack;
	TextArea * _health;
	TextArea * _defence;

	std::array<ImageWidget *, 4> _orderSpots;
	std::array<ImageWidget *, 4> _orders;



private:
	// Inherited via GUIElement
	virtual void _init(AssetMeneger * assets) override;

	// Inherited via GUIElement
	virtual void _initLogic( AssetMeneger * assets) override;

	sf::Color getColorFromPC(const ParameterColor & p);

};

}