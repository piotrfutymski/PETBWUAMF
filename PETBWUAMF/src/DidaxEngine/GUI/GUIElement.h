#pragma once
#include "../Widgets/Widgets.h"
#include "../Assets/GUIElementPrototype.h"
#include "../Assets/AssetMeneger.h"

#include <string>


namespace Didax
{

class GUIElement
{
public:

	using WidgetHolder_t = std::vector<std::unique_ptr<Widget>>;

	GUIElement();
	~GUIElement(); 

	const Canvas * getRoot()const;
	Canvas * getRoot();

	void open(GUIElementPrototype * prototype, AssetMeneger * assets);

	void unactiveButton(const std::string & name);
	void activeButton(const std::string & name);

	void onlyHoverButton(const std::string & name);

	void setOnHoverInToButton(const std::string & name, std::function<void()>);
	void setOnPressToButton(const std::string & name, std::function<void()>);
	void setOnHoverOutToButton(const std::string & name, std::function<void()>);
	void resetOnHoverInButton(const std::string & name);
	void resetOnPressButton(const std::string & name);
	void resetOnHoverOutButton(const std::string & name);

	static sf::Vector2f UNITPOSITIONTAB[16];
	static sf::Vector2f ORDERPOSITIONTAB[10];
	static sf::Color INTERACTIONCOLORS[3];

protected:

	GUIElementPrototype * _prototype;

	// widgets

	Canvas * _root{ nullptr };

	WidgetHolder_t _widgets;

	std::map<std::string, Widget *> _buttons;


protected:
	
	void createEmptyButton(const std::string & name, Widget * w);

	Widget * findButton(const std::string & name);

	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;
	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) = 0;

};

}