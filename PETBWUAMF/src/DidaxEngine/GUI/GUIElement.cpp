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

void Didax::GUIElement::open(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_prototype = prototype;
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets[0].get());
	this->_init(prototype, assets);
	this->_initLogic(prototype, assets);

}

void Didax::GUIElement::unactiveButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;
	w->setActive(false);
}

void Didax::GUIElement::activeButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;

	w->setActive(true);
}

void Didax::GUIElemnt::onlyHoverButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;

	w->resetWidgetEvent(Widget::CallbackType::onPress);
}

void Didax::GUIElement::setOnHoverInToButton(const std::string & name, const std::function<void() &> f)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;
	w->setWidgetEvent(Widget::CallbackType::onHoverIn, [this, f](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[1]);
		f();
	});	
}

void Didax::GUIElement::setOnHoverOutToButton(const std::string & name, const std::function<void()> & f)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;
	w->setWidgetEvent(Widget::CallbackType::onHoverOut, [this, f](Widget * w, float dt) {
		if(!w->isPressed())
			w->setColor(INTERACTIONCOLORS[0]);
		f();
	});	
}

void Didax::GUIElement::setOnPressToButton(const std::string & name, const std::function<void()> & f)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;

	w->setWidgetEvent(Widget::CallbackType::onPress, [this, f](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[2]);
		f();
	});	
}

void Didax::GUIElement::resetOnHoverInButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;
	w->setWidgetEvent(Widget::CallbackType::onHoverIn, [this, f](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[1]);
	});	
}

void Didax::GUIElement::resetOnHoverOutButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;
	w->setWidgetEvent(Widget::CallbackType::onHoverOut, [this, f](Widget * w, float dt) {
		if(!w->isPressed())
			w->setColor(INTERACTIONCOLORS[0]);
	});	
}

void Didax::GUIElement::resetOnPressButton(const std::string & name)
{
	auto w = this->findButton(name);
	if(w == nullptr)
		return;

	w->setWidgetEvent(Widget::CallbackType::onPress, [this, f](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[2]);
	});	
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

/*
template<typename ...Args>
auto doNothing(Args&&... args)
{
	return [](std::forward<Args>... args){};
}*/

Didax::Widget * Didax::GUIElement::findButton(const std::string & name)
{
	auto r = _buttons.find(name);
	if(r == _buttons.end())
		return nullptr;
	return r->second;
}

void Didax::GUIElement::createEmptyButton(const std::string & name, Widget * w)
{
	w->setWidgetEvent(Widget::CallbackType::onHoverIn, [this](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[1]);
	});
	w->setWidgetEvent(Widget::CallbackType::onHoverOut, [this](Widget * w, float dt) {
		if(!w->isPressed())
			w->setColor(INTERACTIONCOLORS[0]);
	});
	w->setWidgetEvent(Widget::CallbackType::onPress, [this](Widget * w, float dt) {
		w->setColor(INTERACTIONCOLORS[2]);
	});
	w->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget * w, float dt) {
		if (w->isHovered())
			w->setColor(INTERACTIONCOLORS[1]);
		else
			w->setColor(INTERACTIONCOLORS[0]);

	});
	_buttons.insert(std::make_pair(name, w));
}


