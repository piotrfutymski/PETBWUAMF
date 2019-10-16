#include "GUIElement.h"

Didax::GUIElement::GUIElement()
{

}

Didax::GUIElement::~GUIElement()
{
}

const Didax::Canvas * Didax::GUIElement::getRoot() const
{
	return _root;
}

Didax::Canvas * Didax::GUIElement::getRoot()
{
	return _root;
}

void Didax::GUIElement::open(GUIElementPrototype * prototype, AssetMeneger * assets, Engine * e)
{
	engine = e;
	_prototype = prototype;
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets[0].get());
	this->_init(prototype, assets);
	this->_initLogic(prototype, assets);

}

sf::Vector2f Didax::GUIElement::UNITPOSITIONTAB[] = {
	{200,40},{200,220},{200,400},{200,580},
	{350,40},{350,220},{350,400},{350,580},
	{600,40},{600,220},{600,400},{600,580},
	{750,40},{750,220},{750,400},{750,580}
};

sf::Vector2f Didax::GUIElement::ORDERPOSITIONTAB[] = {
	{0,840},{140,840},{280,840},{420,840},
	{560,840},{700,840},{940,840},{1080,840},
	{1220,840},{1360,840},
};

sf::Color Didax::GUIElement::INTERACTIONCOLORS[] = {
	{255, 255, 255, 255},
	{200, 200, 200, 255},
	{150, 150, 150, 255},
};


void Didax::GUIElement::createEmptyButton(Widget * w)
{
	this->createButton(w, []() {}, []() {}, []() {});
}

void Didax::GUIElement::createButton(Widget * w, const  std::function<void()> & onHoverIn, const  std::function<void()> & onPress, const  std::function<void()> & onHoverOut)
{
	w->setWidgetEvent(Widget::CallbackType::onHoverIn, [this, onHoverIn](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[1]);
		onHoverIn();
	});
	w->setWidgetEvent(Widget::CallbackType::onHoverOut, [this, onHoverOut](Widget * w, float dt) {
		if(!w->isPressed())
			w->setColor(INTERACTIONCOLORS[0]);
		onHoverOut();
	});
	w->setWidgetEvent(Widget::CallbackType::onPress, [this,onPress](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[2]);
		onPress();
	});
	w->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget * w, float dt) {
		if (w->isHovered())
			w->setColor(INTERACTIONCOLORS[1]);
		else
			w->setColor(INTERACTIONCOLORS[0]);

	});
}

