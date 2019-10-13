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

	void setOnChoosed(const std::function<void(int choosedPos)> & func);
	void resetOnChoosed();
	const bool * getChoosablePositions()const;
	bool getIfCanBeChoosen(int pos)const;

	void onChoose(int pos);

	sf::Color getColorFromSide(int p, YellowSide s)const;

private:
	std::function<void(int)> _onChoose{ nullptr };

	ImageWidget * _borders[16];

	bool _choosablePositions[16];

	YellowSide _side;


private:

	// Inherited via GUIElement
	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

};

}