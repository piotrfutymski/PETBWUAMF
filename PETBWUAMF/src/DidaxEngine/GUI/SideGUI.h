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

	virtual void init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

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

	void initLogic();

	void hourglassClicked();

};

}