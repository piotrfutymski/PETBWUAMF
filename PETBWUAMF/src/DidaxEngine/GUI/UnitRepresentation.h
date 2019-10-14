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

	UnitRepresentation();
	~UnitRepresentation();

	void setUnit(const std::string & name, AssetMeneger * assets);

	void setAttack(const ParameterColor & p, int v);
	void setDefence(const ParameterColor & p, int v);
	void setHealth(const ParameterColor & p, int v);

	void setPosition(int pos);

	void setActive(bool a);


private:

	TextArea * _attack;
	TextArea * _health;
	TextArea * _defence;

	bool _active;

private:
	// Inherited via GUIElement
	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	// Inherited via GUIElement
	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	sf::Color getColorFromPC(const ParameterColor & p);

};

}