#pragma once
#include "../Widgets/SwitchableImage.h"
#include "../Widgets/ImageWidget.h"
#include "../Widgets/Canvas.h"


namespace Didax
{

class Slider
{
public:

	enum class Axis
	{
		Horizontal, Vertical
	};

	Slider() {};

	void init(Canvas * holder, SwitchableImage * background, ImageWidget * filling, Axis ax);

	const Canvas * getHolder()const;
	Canvas * getHolder();

	void setFillingArea(const sf::Rect<float> & r);
	void setHeightArrowArea(const sf::Rect<float> & r);
	void setLowArrowArrea(const sf::Rect<float> & r);

	void setVelocity(float V);

	float getValue()const;
	void setValue(float v);

	void setOnValueChanged(const std::function<void(float v)> & f);

private:
	Canvas * _holder;
	SwitchableImage * _background;
	ImageWidget * _filling;

	sf::Rect<float> _fillingArea{0,0,0,0};
	sf::Rect<float> _heightArrowArea{ 0,0,0,0 };
	sf::Rect<float> _lowArrowArea{ 0,0,0,0 };
	Axis _axis;
	float _arrowV{ 0.5f };

	float _value{ 0 };

	std::function<void(float v)> _onValueChanged{ nullptr };

	bool _isHoldLow{ false };
	bool _isHoldHeight{ false };
	bool _isHover{ false };

private:

	void onHoverIn();
	void onHoverOut();
	void onHold(float dt);
	void onRealesed();

	void recalculateFilling();
	void initWdgets();
	void calculateFillingPos();

	bool isInLow();
	bool isInHeight();

};

}