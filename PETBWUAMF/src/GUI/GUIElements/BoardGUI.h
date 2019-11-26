#pragma once
#include "GUIElement.h"
#include <array>

namespace Didax
{

class BoardGUI : public GUIElement
{
public:
	enum class PositionState{
		Inactive, Movable, Enemy, Allay, ActiveUnit, ChoosableUnit, Choosed
	};

	struct PositionWidget
	{
		PositionState s;
		Button * button;
		int unitID{ -1 };
		int unitOwner{ -1 };

	};

	sf::Color colorFromState(PositionState s);

	constexpr static int MAP_WIDTH = 16;
	constexpr static int MAP_HEIGHT = 10;

	using Buttons_t = std::array<std::array<PositionWidget, MAP_HEIGHT>, MAP_WIDTH>;

	BoardGUI(GUIElementPrototype * prototype, Game * game);
	~BoardGUI();



	void setTargets(const std::vector<Target> & targets);

	void reloadFromGame();

	sf::Vector2i getLastChoosed()const;

private:

	Buttons_t _positions;

	sf::Vector2i _lastChoosed{ -1,-1 };


private:

	// Inherited via GUIElement
	virtual void _init() override;

	virtual void _initLogic() override;

	void setPositionInState(PositionState st, const sf::Vector2i & p, int uID = 0, int owner = 0);
};

}