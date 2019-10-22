#include "ImageWidget.h"


namespace Didax
{

ImageWidget::ImageWidget():Widget()
{
}

void ImageWidget::setTexture(const sf::Texture * t)
{
	_isTextureLoaded = true;
	_textureSize.x = (float)t->getSize().x;
	_textureSize.y = (float)t->getSize().y;
	_sprite.setTexture(*t);
	this->setSize({_textureSize.x, _textureSize.y});
}

void ImageWidget::setScalableTexture(bool flag)
{
	_noScalable = flag;
	this->updateSize();
}

bool ImageWidget::getScalable() const
{
	return _noScalable;
}

void ImageWidget::_update(float deltaT)
{
}

bool ImageWidget::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void ImageWidget::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void ImageWidget::updatePosition()
{
	_sprite.setPosition(this->getAbsolutePosition());
}

void ImageWidget::updateSize()
{
	if (_noScalable)
		_sprite.setTextureRect(sf::IntRect{ 0,0,(int)_size.x,(int)_size.y });
	else
		_sprite.setScale({ _size.x / _textureSize.x, _size.y / _textureSize.y });
}

void ImageWidget::updateColor()
{
	_sprite.setColor(_color);
}



}

