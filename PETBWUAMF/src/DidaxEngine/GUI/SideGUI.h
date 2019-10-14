#pragma once
#include "GUIElement.h"

namespace Didax
{


class SideGUI : public GUIElement
{
public:

	SideGUI();
	~SideGUI();

	void setOnHourglassClicked(const std::function<void()> & func);
	void setOnExitButtonClicked(const std::function<void()> & func);

	void startHourglassOnState(int state);

	void addTime(float t);

	float getTime()const;

	Widget * getHourglass()const;

private:

	float _dT{ 0 };

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