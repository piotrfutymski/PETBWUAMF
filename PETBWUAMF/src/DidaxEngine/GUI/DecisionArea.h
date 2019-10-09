#pragma once

#include "../Widgets/ImageWidget.h"
#include "../Widgets/Canvas.h"
#include "../Widgets/TextArea.h"
#include "../Widgets/ScrollArea.h"


namespace Didax
{

class DecisionArea
{
public:
	DecisionArea();
	~DecisionArea();

	void init(Canvas * holder, ImageWidget * background, ScrollArea * scrollArea, const std::vector<TextArea *> & options);

	void setSize(const sf::Vector2f & s);
	sf::Vector2f getSize()const;

	void setPosition(const sf::Vector2f & p);
	sf::Vector2f getPosition()const;

	void setScrollMargin(const sf::Vector2f & m);
	sf::Vector2f getScrollMargin()const;

	void setScrollPadding(const sf::Vector2f & p);
	sf::Vector2f getScrollPadding()const;

	size_t getHoveredOption()const;

	void setOnChoosenOption(const std::function<void(size_t opt)> & f);

private:

	std::vector<TextArea *> _options;
	Canvas * _holder;
	ImageWidget * _background;
	ScrollArea * _scrollArea;

	sf::Vector2f _size{ 1024,312 };
	sf::Vector2f _position{ 0,0 };
	sf::Vector2f _scrollMargin{ 64,32 };
	sf::Vector2f _scrollPadding{ 3,3 };

	size_t _hoveredOption{ (size_t)-1 };

	std::function<void(size_t opt)> _onOptionChoosed{ nullptr };

private:

	void initWidgetFunctions();
	void resetBackgrounds();
	void recalculatePositions();
	void recalculateSizes();
	void recalculateAll();

};

}