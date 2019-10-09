#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <exception>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "../Inupt/Input.h"

namespace Didax
{

class Widget :public sf::Drawable
{
public:

	enum class CallbackType {
		onHover, onHoverIn, onHoverOut, onPress, onHold, onRelease, onPressRight
	};

	using WidgetFunctionHolder_t = std::map<CallbackType, std::function<void(Widget*, float)>>;
	using CallbackHolder_t = std::vector<CallbackType>;

public:						
	//constructors

	Widget();

	// public functions

	void update(float deltaT);
	bool input(const sf::Event & event, bool inArea = true);

	bool isInGivenArea(sf::Vector2f a, sf::Vector2f b);

	// properties

	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	void move(sf::Vector2f deltaS);
	sf::Vector2f getPosition()const;

	void setPositionInTime(sf::Vector2f, float T);
	void setPositionInTime(float x, float y, float T);

	void setColor(const sf::Color & c);
	void setColorInTime(const sf::Color & c, float T);
	sf::Color getColor()const;

	void setSize(const sf::Vector2f & s);
	void resizeToChildren();
	sf::Vector2f getSizeWithChildren()const;
	sf::Vector2f getSize()const;

	Widget * getParent();
	const Widget * getParent()const;

	void setPadding(const sf::Vector2f & pad);
	sf::Vector2f getPadding()const;

	bool isHovered()const;
	bool isPressed()const;

	bool isVisible()const;
	void setVisible(bool v);

	bool isActive()const;
	void setActive(bool a);

	int getPriority()const;
	void setPrority(int p);

	const std::vector <Widget *> & getChildren()const;
	std::vector <Widget *> & getChildren();

	void setLimitArea(const sf::Vector2f & A, const sf::Vector2f & B);
	void setLimitArea(const sf::Rect<float> & f);
	void limitSize();
	void resetLimitArea();

	void setWidgetEvent(CallbackType t, const std::function<void(Widget*, float)> & func);
	void onUpdate(const std::function<void(Widget*, float)> & func);

	sf::Vector2f getAbsolutePosition()const;
	
	bool isMoseIn()const;

	sf::Vector2f mouseRelativePos()const;

protected:

	// pure virtual

	virtual void _update(float deltaT)=0;
	virtual bool _input(const sf::Event & event, bool inArea = true) = 0;
	virtual bool _inputBeforeAll(const sf::Event & event, bool inArea = true) { return false; };
	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states)const = 0;
	virtual void _drawAfterAll(sf::RenderTarget & target, sf::RenderStates states)const {};
	virtual void updatePosition() = 0;
	virtual void updateSize() = 0;
	virtual void updateColor() = 0;

	// help functions 

	

	void _addChild(Widget * child);
	void _removeChild(Widget * child);
	void setParent(Widget * parent);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;

protected:

	WidgetFunctionHolder_t _widgetEvent;
	CallbackHolder_t _callbacks;

	std::function<void(Widget*, float)> _onUpdate{nullptr};

	sf::Vector2f _relativePos{ 0,0 };
	sf::Vector2f _size{ 0,0 };
	sf::Color _color{ sf::Color::White };
	sf::Vector2f _padding{ 0,0 };

	bool _isHovered{ false };
	bool _isPressed{ false };

	bool _isVisible{ true };
	bool _isActive{ true };

	int _priority{ 0 };

	std::vector<Widget *> _children;
	Widget * _parent{ nullptr };

	sf::Vector2f _nextPos{ 0,0 };
	sf::Vector2f _velocity{ 0,0 };
	float _timeToMove{ 0 };
	bool _movingInTime{ false };

	sf::Color _nextColor{ sf::Color::White };
	sf::Color _lastColor{ sf::Color::White };
	float _timefromBeg{ 0 };
	float _timeToChangeColor{ 0 };
	bool _changingColor{false};


	sf::Vector2f _borderArea[2]{ {0,0},{0,0} };
	bool _isSetArea{ false };


private:
	//private functions
	
	bool isPointInArea(const sf::Vector2f & point, const sf::Vector2f A, const sf::Vector2f B);
	void actualizeInTime(float deltaT);
	void updateCallbacks(float deltaT);
	bool poolEvents(const sf::Event & e);
	void updateEvents();	
	void recalculatePriority();

	void drawOnly(sf::RenderTarget & target, sf::RenderStates states) const;
};

}
