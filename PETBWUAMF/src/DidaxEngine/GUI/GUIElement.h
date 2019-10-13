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

	bool setParent(Canvas * parent);
	Canvas * getParent();

	const Canvas * getRoot()const;
	Canvas * getRoot();

	void init(GUIElementPrototype * prototype, AssetMeneger * assets);

	static sf::Vector2f POSITIONTAB[16];
	static sf::Color BORDERCOLORS[3];
	static sf::Color INTERACTIONCOLORS[3];

protected:

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _parent{ nullptr };

	Canvas * _root{ nullptr };

	WidgetHolder_t _widgets;



protected:

	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

};

}