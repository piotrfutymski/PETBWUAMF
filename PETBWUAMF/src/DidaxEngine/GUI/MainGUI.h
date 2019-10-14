#pragma once
#include "GUIElement.h"

namespace Didax
{
class MainGUI : public GUIElement
{
public:

	enum class YellowSide {
		left, right
	};

	MainGUI();
	~MainGUI();

	void setReadyToChoose(const bool posTab[16], YellowSide side);
	void unsetReadyToChoose();

	void setOnChoosed(const std::function<void()> & func);
	void resetOnChoosed();

	const bool * getChoosablePositions()const;
	bool getIfCanBeChoosen(int pos)const;

	int getLastChoosed()const;

	sf::Color getColorFromSide(int p, YellowSide s)const;

private:

	ImageWidget * _borders[16];

	bool _choosablePositions[16];

	YellowSide _side;

	int _lastChoosed{ -1 };


private:

	// Inherited via GUIElement
	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

};

}