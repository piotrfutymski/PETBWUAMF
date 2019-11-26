#pragma once
#include "GUIElement.h"
#include <array>

namespace Didax
{
class Engine;
class BoardGUI : public GUIElement
{
public:
	enum class PositionState{
		Inactive, Movable, Enemy, Allay, ActiveUnit, ChoosableUnit, Choosed
	};

	struct PositionWidget
	{
		sf::Vector2i pos;
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



	void setTargets(const std::vector<Target> & targets, OrderPrototype::TargetType t);

	void reloadFromGame();

	sf::Vector2i getLastChoosed()const;

	PositionWidget getOnPos(const sf::Vector2i & p)const;

	void destroyOnPos(const sf::Vector2i & p);

	static std::function<void(PositionWidget *, Engine *)> onHoverIn;
	static std::function<void(PositionWidget *, Engine *)> onHoverOut;
	static std::function<void(PositionWidget *, Engine *)> onRelease;
		

private:

	Buttons_t _positions;

	sf::Vector2i _lastChoosed{ -1,-1 };


private:

	// Inherited via GUIElement
	virtual void _init() override;

	virtual void _initLogic(Engine * e) override;

	void setPositionInState(PositionState st, const sf::Vector2i & p, int uID = 0, int owner = 0);

	void setPosTargets(const std::vector<Target> & targets);
	void setAttackTargets(const std::vector<Target> & targets);
	void setChargeTargets(const std::vector<Target> & targets);
	void setBuffTargets(const std::vector<Target> & targets);



};

}