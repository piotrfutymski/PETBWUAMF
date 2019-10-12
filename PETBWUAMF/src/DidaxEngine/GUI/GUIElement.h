#pragma once
#include "../Widgets/Widgets.h"
#include "../Assets/GUIElementPrototype.h"
#include "../Assets/AssetMeneger.h"


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

	virtual void init(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

protected:

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _parent{ nullptr };

	Canvas * _root{ nullptr };

	WidgetHolder_t _widgets;

protected:



};

}