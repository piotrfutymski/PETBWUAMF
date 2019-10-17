#pragma once
#include "GUIElement.h"

namespace Didax
{
class BoardGUI : public GUIElement
{
public:

	enum class YellowSide {
		left, right
	};

	BoardGUI(GUIElementPrototype * prototype);
	~BoardGUI();

	void setReadyToChoose(const bool posTab[16]);
	void unsetReadyToChoose();

	const bool * getChoosablePositions()const;
	bool getIfCanBeChoosen(int pos)const;

	int getLastChoosed()const;

private:

	SwitchableImage * _borders[16];

	bool _choosablePositions[16];

	YellowSide _side;

	int _lastChoosed{ -1 };


private:

	// Inherited via GUIElement
	virtual void _init(AssetMeneger * assets) override;

	virtual void _initLogic(AssetMeneger * assets, const std::vector<std::function<void()>>& func) override;

};

}