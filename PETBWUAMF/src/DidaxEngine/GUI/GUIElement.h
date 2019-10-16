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

	GUIElement();
	~GUIElement(); 

	const Canvas * getRoot()const;
	Canvas * getRoot();

	void open(GUIElementPrototype * prototype, AssetMeneger * assets, Engine * e);

	static sf::Vector2f UNITPOSITIONTAB[16];
	static sf::Vector2f ORDERPOSITIONTAB[10];
	static sf::Color INTERACTIONCOLORS[3];

	Engine * engine;

protected:

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _root{ nullptr };

	WidgetHolder_t _widgets;



protected:
	
	void createEmptyButton(Widget * w);
	void createButton(Widget * w, const  std::function<void()> & onHoverIn, const  std::function<void()> & onPress, const  std::function<void()> & onHoverOut);


	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;
	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

};

}