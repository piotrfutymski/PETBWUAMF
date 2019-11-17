#pragma once
#include "../Widgets/Widgets.h"
#include "../../Game/Game.h"
#include "../../Assets/GUIElementPrototype.h"
#include "../../Assets/AssetMeneger.h"

#include <string>


// DO Zaimplementowania - System Akcji!!!

namespace Didax
{

class GUIElement
{
public:

	using WidgetHolder_t = std::vector<std::unique_ptr<Widget>>;

	GUIElement(GUIElementPrototype * prototype);
	~GUIElement(); 

	const Canvas * getRoot()const;
	Canvas * getRoot();

	void open(Canvas * parent);
	void close();

	void setPriority(int p);
	int getPriority()const;


	static sf::Vector2f UNITPOSITIONTAB[16];
	static sf::Vector2f ORDERPOSITIONTAB[10];

protected:

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _root{ nullptr };

	Canvas * _parent{ nullptr };

	WidgetHolder_t _widgets;

	//

	int _priority{ 0 };


protected:

	virtual void _init() = 0;
	virtual void _initLogic() = 0;

};

}