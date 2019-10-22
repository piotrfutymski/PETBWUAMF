#pragma once
#include"../Widget.h"
#include <functional>

namespace Didax
{

class Scroller : public sf::Drawable
{
public:
	Scroller();

	Scroller(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Vector2f & size, const sf::Texture * back);

	//public functions

	void init(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Vector2f & size, const sf::Texture * back);

	bool input(const sf::Event & e);

	void update(float deltaT);


	//properties

	void setTextures(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Texture * back);

	void setHoverColor(const sf::Color & c);

	void setClickedColor(const sf::Color & c);

	void setNormalColor(const sf::Color & c);

	sf::Vector2f getSize()const;
	void setSize(const sf::Vector2f & s);

	float getArrowHeight()const;
	void setArrowHeight(float h);

	float getButtonHeight()const;
	void setButtonHeight(float b);

	float getButtonPosition()const;

	void moveButton(float delta);

	bool isActive()const;
	void setActive(bool a);

	void setArrowVelocity(float v);

	void setPosition(const sf::Vector2f & pos);
	sf::Vector2f getPosition();

	void setOnButtonPosChanged(const std::function<void()> & f);

	void setColor(const sf::Color &c);
	sf::Color getColor()const;

private:

	struct Element {
		sf::Sprite _sprite;
		bool _isHovered;
		bool _isPressed;

	};

	sf::Sprite _background;
	Element _topArrow;
	Element _bottomArrow;
	Element _button;

	sf::Color _globalColor{ sf::Color::White };

	sf::Color _hoveredColor{255,255,255,255};
	sf::Color _clickedColor{ 255,255,255,255 };
	sf::Color _inActiveColor{ 255,255,255,255 };
	sf::Color _normalColor{ 255,255,255,255 };
	
	sf::Vector2f _size{ 0.0f,0.0f };
	sf::Vector2f _position{ 0,0 };
	bool _isActive{ true };

	float _arrowHeight{ 0 };
	float _buttonHeight{ 0};
	int _buttonClickPos{ 0 };
	float _buttonClockPosprc{ 0 };
	int _freeSpaceheight;


	float _buttonPosition{ 0.0f };
	float _arrowVelocity{ 1.0f };


	std::function<void()> _onButtonPosChanged{ nullptr };


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void elemInput(Element * el, const sf::Event & e);
	void onHoverIn(Element * el);
	void onPress(Element * el);
	void onHold(Element * el, float deltaT);
	void onRealesed(Element * el);
	void onHoverOut(Element * el);

	void recalculateColor(Element * el);

	void recalculateAll();
	void recalculateButton();


	void calculateButtonPos();
	void setButtonPos(float pos);

};

}