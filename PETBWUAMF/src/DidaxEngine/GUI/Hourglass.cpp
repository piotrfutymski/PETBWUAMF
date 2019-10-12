#include "Hourglass.h"


Didax::Hourglass::Hourglass()
{
}

Didax::Hourglass::~Hourglass()
{
}

void Didax::Hourglass::setOnStateChanged(const std::function<void()>& func)
{
	_onStateChanged = func;

}

void Didax::Hourglass::onStateChanged()
{
	if(_onStateChanged != nullptr)
		this->_onStateChanged();
}


void Didax::Hourglass::init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets[0].get());

	_root->setSize({ prototype->_values["width"], (prototype->_values["height"]) });
	_root->setPosition({ prototype->_values["xPos"], (prototype->_values["yPos"]) });

	auto text = assets->getAsset<TextureAsset>(prototype->_fileNames["texture"]);
	_root->setTexture(&(text->_texture));
	this->initLogic();

}

void Didax::Hourglass::initLogic()
{
	_root->setWidgetEvent(Widget::CallbackType::onHoverIn, [](Widget * w, float dt) {
		static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,50 }); });
	_root->setWidgetEvent(Widget::CallbackType::onHoverOut, [](Widget * w, float dt) {
		static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,0 }); });
	_root->setWidgetEvent(Widget::CallbackType::onPress, [this](Widget * w, float dt) {
		static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,100 });
		this->onStateChanged();
	});

}
