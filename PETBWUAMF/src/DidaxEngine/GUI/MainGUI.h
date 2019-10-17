#pragma once
#include "GUIElement.h"

namespace Didax
{


class MainGUI : public GUIElement
{
public:

	MainGUI(GUIElementPrototype * prototype);
	~MainGUI();

	void startHourglassOnState();

	void nextState();

	void addTime(float t);

	float getTime()const;

	Widget * getHourglass()const;

	void setDescription(const std::string & d);

private:

	float _dT{ 0 };

	int _state;

// widgets

	TextArea * _text;

	ImageWidget * _hourglass;

	ImageWidget * _exitButton;

	TextArea * _unOrDescritpion;

	std::string _displayedTexts[3];

private:

	virtual void _init(AssetMeneger * assets) override;

	virtual void _initLogic(AssetMeneger * assets, const std::vector<std::function<void()>> & func = {}) override;

};

}