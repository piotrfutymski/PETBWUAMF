#pragma once
#include "GUIElement.h"

namespace Didax
{


class MainGUI : public GUIElement
{
public:

	MainGUI();
	~MainGUI();

	void startHourglassOnState();

	void nextState();

	void addTime(float t);

	float getTime()const;

	Widget * getHourglass()const;

private:

	float _dT{ 0 };

	int _state;

// widgets

	TextArea * _text;

	ImageWidget * _hourglass;

	ImageWidget * _exitButton;

	std::string _displayedTexts[3];

private:

	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

};

}