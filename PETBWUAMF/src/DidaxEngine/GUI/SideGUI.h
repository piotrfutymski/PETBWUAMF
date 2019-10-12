#pragma once
#include "GUIElement.h"

namespace Didax
{


class SideGUI : public GUIElement
{
public:

	SideGUI();
	~SideGUI();

	void setOnHourglassClicked(const std::function<int()> & func);
	int onHourglassClicked();



	void addTime(float t);

	float getTime()const;

private:

	std::function<int()> _onHourglassClicked;

	float _dT{ 0 };

// widgets

	TextArea * _text;

	ImageWidget * _hourglass;

	std::string _displayedTexts[3];

private:

	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

	void hourglassClicked();

};

}