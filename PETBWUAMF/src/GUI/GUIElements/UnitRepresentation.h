#pragma once
#include "GUIElement.h"

namespace Didax
{

	class Engine;

class UnitRepresentation:  public GUIElement
{
public:

	UnitRepresentation(GUIElementPrototype * prototype, Game * game, Engine* e);
	~UnitRepresentation();

	void setUnit(size_t u);
	void resetUnit();

	size_t getUnitID();
	sf::Vector2i getPosition()const;

	void reloadHealth();
	void reloadPosition();

	bool isChoosable()const;
	void setChoosable(bool c);

	void recalculate();
	void hide();


private:

	Button * _unit;
	HPbar * _bar;

	int _unitSize;
	int _padding;

	size_t _unitID;
	sf::Vector2i _pos;

	bool _choosable{ false };


private:
	// Inherited via GUIElement
	virtual void _init() override;


};

}