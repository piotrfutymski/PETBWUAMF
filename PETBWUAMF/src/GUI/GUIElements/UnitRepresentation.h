#pragma once
#include "GUIElement.h"

namespace Didax
{

class UnitRepresentation:  public GUIElement
{
public:

	UnitRepresentation(GUIElementPrototype * prototype, Game * game);
	~UnitRepresentation();

	void setUnit(size_t u);
	void resetUnit();

	void reloadHealth();
	void reloadPosition();


private:

	Button * _unit;
	HPbar * _bar;

	int _unitSize;
	int _padding;

	size_t _unitID;


private:
	// Inherited via GUIElement
	virtual void _init() override;

	// Inherited via GUIElement
	virtual void _initLogic( ) override;


};

}