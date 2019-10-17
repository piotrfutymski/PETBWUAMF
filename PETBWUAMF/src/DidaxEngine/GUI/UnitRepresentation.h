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

	void setAttack(const ParameterColor & p, int v);
	void setDefence(const ParameterColor & p, int v);
	void setHealth(const ParameterColor & p, int v);

	void setPosition(int pos);


private:

	TextArea * _attack;
	TextArea * _health;
	TextArea * _defence;

private:
	// Inherited via GUIElement
	virtual void _init(AssetMeneger * assets) override;

	// Inherited via GUIElement
	virtual void _initLogic( AssetMeneger * assets, const std::vector<std::function<void()>> & func) override;

	sf::Color getColorFromPC(const ParameterColor & p);

};

}