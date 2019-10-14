#pragma once
#include "../Widgets/Widgets.h"
#include "../Assets/GUIElementPrototype.h"
#include "../Assets/AssetMeneger.h"

#include <string>


namespace Didax
{
class Engine;

class GUIElement
{
public:

	using WidgetHolder_t = std::vector<std::unique_ptr<Widget>>;
	using EventsHolder_t = std::map < Widget *, std::function<void()>>;

	GUIElement();
	~GUIElement(); 

	bool setParent(Canvas * parent);
	Canvas * getParent();

	const Canvas * getRoot()const;
	Canvas * getRoot();

	void init(GUIElementPrototype * prototype, AssetMeneger * assets);

	void onHoverInElement(Widget * w);
	void onHoverOutElement(Widget * w);
	void onPressElement(Widget * w);


	static sf::Vector2f POSITIONTAB[16];
	static sf::Color BORDERCOLORS[3];
	static sf::Color INTERACTIONCOLORS[3];

protected:

	EventsHolder_t _onPress;
	EventsHolder_t _onHoverIn;
	EventsHolder_t _onHoverOut;

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _parent{ nullptr };

	Canvas * _root{ nullptr };

	WidgetHolder_t _widgets;



protected:

	void _initElement(Widget * w);
	void _setOnHoverIn(Widget * w, const std::function<void()> & f);
	void _setOnHoverOut(Widget * w, const std::function<void()> & f);
	void _setPress(Widget * w, const std::function<void()> & f);

	void _resetOnHoverIn(Widget * w);
	void _resetOnHoverOut(Widget * w);
	void _resetPress(Widget * w);

	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

};

}