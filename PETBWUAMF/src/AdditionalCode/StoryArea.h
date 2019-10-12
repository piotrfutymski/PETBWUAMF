#pragma once

namespace Didax
{


class StoryArea
{
public:
	StoryArea();
	~StoryArea();

	void init(Canvas * h, ImageWidget * b, ScrollArea * s, TextArea * t, ImageWidget * i);

	void setSize(const sf::Vector2f & s);
	sf::Vector2f getSize()const;

	void setPosition(const sf::Vector2f & p);
	sf::Vector2f getPosition()const;

	void setScrollMargin(const sf::Vector2f & m);
	sf::Vector2f getScrollMargin()const;

	void setScrollPadding(const sf::Vector2f & p);
	sf::Vector2f getScrollPadding()const;

private:
	Canvas * _holder;
	ImageWidget * _background;
	ScrollArea * _scrollArea;
	TextArea * _text;
	ImageWidget * _image;

	sf::Vector2f _size{ 1024,768 };
	sf::Vector2f _position{ 0,0 };
	sf::Vector2f _scrollMargin{64,64};
	sf::Vector2f _scrollPadding{ 32,32 };

	bool _imageFirst{ true };

private:

	void resetBackgrounds();
	void recalculatePositions();
	void recalculateSizes();
	void recalculateAll();
};

}