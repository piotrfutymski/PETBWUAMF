#include "Slider.h"

namespace Didax
{

void Slider::init(Canvas * holder, SwitchableImage * background, ImageWidget * filling, Axis ax)
{
	_holder = holder;
	_background = background;
	_filling = filling;
	_axis = ax;

	this->initWdgets();

}

const Canvas * Slider::getHolder() const
{
	return _holder;
}

Canvas * Slider::getHolder()
{
	return _holder;
}

void Slider::setFillingArea(const sf::Rect<float>& r)
{
	_fillingArea = r;
	this->calculateFillingPos();
	_holder->resizeToChildren();
}

void Slider::setHeightArrowArea(const sf::Rect<float>& r)
{
	_heightArrowArea = r;
}

void Slider::setLowArrowArrea(const sf::Rect<float>& r)
{
	_lowArrowArea = r;
}

void Slider::setVelocity(float V)
{
	_arrowV = V;
}

float Slider::getValue() const
{
	return _arrowV;
}

void Slider::setValue(float v)
{
	if (v < 0)
		_value = 0;
	else if (v > 1)
		_value = 1;
	else
		_value = v;
	this->recalculateFilling();
	if(_onValueChanged!=nullptr)
		_onValueChanged(v);
}

void Slider::setOnValueChanged(const std::function<void(float v)>& f)
{
	_onValueChanged = f;
}

void Slider::onHoverIn()
{
	_isHover = true;
	_background->setOption(1);
}

void Slider::onHoverOut()
{
	_isHover = false;
	_background->setOption(0);
}


void Slider::onHold(float dt)
{
	if (this->isInLow())
	{
		if (!_isHoldLow)
		{
			_isHoldLow = true;
			_background->setOption(2);
		}
		this->setValue(_value - dt * _arrowV);
	}
	if (this->isInHeight())
	{
		if (!_isHoldHeight)
		{
			_isHoldHeight = true;
			_background->setOption(2);
		}
		this->setValue(_value + dt * _arrowV);
	}
}

void Slider::onRealesed()
{
	if (_isHoldLow)
		_isHoldLow = false;
	if (_isHoldHeight)
		_isHoldHeight = false;

	if (_isHover)
		_background->setOption(1);
	else
		_background->setOption(0);
}

void Slider::recalculateFilling()
{
	if (_axis == Axis::Vertical)
		_filling->setSize({ _value*_fillingArea.width*_background->getSize().x, _fillingArea.height*_background->getSize().y});
	if (_axis == Axis::Horizontal)
		_filling->setSize({ _fillingArea.width*_background->getSize().x, _value*_fillingArea.height*_background->getSize().y });
}

void Slider::initWdgets()
{
	//_filling->setScalableTexture(true);
	_background->setWidgetEvent(Widget::CallbackType::onHoverIn, [this](Widget * w, float t){
		this->onHoverIn();
	});
	_background->setWidgetEvent(Widget::CallbackType::onHoverOut, [this](Widget * w, float t) {
		this->onHoverOut();
	});
	_background->setWidgetEvent(Widget::CallbackType::onHold, [this](Widget * w, float t) {
		this->onHold(t);
	});
	_background->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget * w, float t) {
		this->onRealesed();
	});
}

void Slider::calculateFillingPos()
{
	_background->setPosition(0, 0);
	_filling->setPosition(_fillingArea.left*_background->getSize().x, _fillingArea.top*_background->getSize().y);
}

bool Slider::isInLow()
{
	if (_lowArrowArea.contains(_background->mouseRelativePos()))
		return true;
	return false;
}

bool Slider::isInHeight()
{
	if (_heightArrowArea.contains(_background->mouseRelativePos()))
		return true;
	return false;
}


}