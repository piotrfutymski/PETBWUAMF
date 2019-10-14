#include "GUIElement.h"

Didax::GUIElement::GUIElement()
{

}

Didax::GUIElement::~GUIElement()
{
}

bool Didax::GUIElement::setParent(Canvas * parent)
{
	if (!parent->addChild(_root))
		return false;
	_parent = parent;
	return true;
}

Didax::Canvas * Didax::GUIElement::getParent()
{
	return _parent;
}

const Didax::Canvas * Didax::GUIElement::getRoot() const
{
	return _root;
}

Didax::Canvas * Didax::GUIElement::getRoot()
{
	return _root;
}

void Didax::GUIElement::init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_prototype = prototype;
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets[0].get());
	this->_init(prototype, assets);
	this->_initLogic(prototype, assets);

}

void Didax::GUIElement::onHoverInElement(Widget * w)
{
	if (_onHoverIn[w] != nullptr)
		_onHoverIn[w]();
}

void Didax::GUIElement::onHoverOutElement(Widget * w)
{
	if (_onHoverOut[w] != nullptr)
		_onHoverOut[w]();
}

void Didax::GUIElement::onPressElement(Widget * w)
{
	if (_onPress[w] != nullptr)
		_onPress[w]();
}

sf::Vector2f Didax::GUIElement::POSITIONTAB[] = {
	{200,40},{200,220},{200,400},{200,580},
	{350,40},{350,220},{350,400},{350,580},
	{600,40},{600,220},{600,400},{600,580},
	{750,40},{750,220},{750,400},{750,580}
};

sf::Color Didax::GUIElement::INTERACTIONCOLORS[] = {
	{255, 255, 255, 255},
	{200, 200, 200, 255},
	{150, 150, 150, 255},
};

sf::Color Didax::GUIElement::BORDERCOLORS[] = {
	{255, 255, 255, 255},
	{255, 255, 0, 255},
	{255, 0, 0, 255},
};

void Didax::GUIElement::_initElement(Widget * w)
{
	w->setWidgetEvent(Widget::CallbackType::onHoverIn, [this](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[1]);
		this->onHoverInElement(w);
	});
	w->setWidgetEvent(Widget::CallbackType::onHoverOut, [this](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[0]);
		this->onHoverOutElement(w);
	});
	w->setWidgetEvent(Widget::CallbackType::onPress, [this](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[2]);
		this->onPressElement(w);
	});
	w->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget * w, float dt) {
		if (w->isHovered())
			w->setColor(INTERACTIONCOLORS[1]);
		else
			w->setColor(INTERACTIONCOLORS[0]);

	});
}

void Didax::GUIElement::_setOnHoverIn(Widget * w, const std::function<void()>& f)
{
	_onHoverIn[w] = f;
}

void Didax::GUIElement::_setOnHoverOut(Widget * w, const std::function<void()>& f)
{
	_onHoverOut[w] = f;
}

void Didax::GUIElement::_setPress(Widget * w, const std::function<void()>& f)
{
	_onPress[w] = f;
}

void Didax::GUIElement::_resetOnHoverIn(Widget * w)
{
	_onHoverIn[w] = nullptr;
}

void Didax::GUIElement::_resetOnHoverOut(Widget * w)
{
	_onHoverOut[w] = nullptr;
}

void Didax::GUIElement::_resetPress(Widget * w)
{
	_onPress[w] = nullptr;
}
