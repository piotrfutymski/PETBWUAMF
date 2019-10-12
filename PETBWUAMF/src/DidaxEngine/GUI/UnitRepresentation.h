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

	enum class BorderColor {
		yellow, red
	};

	UnitRepresentation();
	~UnitRepresentation();

	void setUnit(const std::string & name, AssetMeneger * assets);

	void setAttack(const ParameterColor & p, int v);
	void setDefence(const ParameterColor & p, int v);
	void setHealth(const ParameterColor & p, int v);

	void setReadyToChoose(const BorderColor & c);
	void unsetReadyToChoose();

	void setPosition(int pos);

	void setOnChoosed(const std::function<void()> & func);
	void resetOnChoosed();
	bool getIfCanBeChoosed()const;

	void onChoosed();


private:

	std::function<void()> _onChoosed;

	TextArea * _attack;
	TextArea * _health;
	TextArea * _defence;
	ImageWidget * _border;

	bool _canBeChoosen{ false };

	static sf::Vector2f POSITIONTAB[16];

private:
	// Inherited via GUIElement
	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	// Inherited via GUIElement
	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	sf::Color getColorFromPC(const ParameterColor & p);
	sf::Color getColorFromBC(const BorderColor & c);

};

}