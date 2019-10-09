#include "SwitchableImage.h"

namespace Didax
{


SwitchableImage::SwitchableImage()
{
}


SwitchableImage::~SwitchableImage()
{
}

void SwitchableImage::init(const std::vector<sf::Texture*> & im)
{
	if (im.size() == 0)
		return;
	_textures = im;
	auto t = _textures[0]->getSize();
	this->setSize({ (float)t.x,(float)t.y });
	this->setOption(0);
}

void SwitchableImage::setOption(size_t id)
{
	if (id >= 0 && id < _textures.size())
	{
		_sprite.setTexture(*_textures[id]);
		_choosenOption = id;
		auto s = _textures[id]->getSize();
		_sprite.scale({ _size.x / s.x,  _size.y / s.y });
	}
		
}

size_t SwitchableImage::getOption() const
{
	return _choosenOption;
}

void SwitchableImage::nextOption()
{
	if (_choosenOption == _textures.size() - 1)
		this->setOption(0);
	else
		this->setOption(_choosenOption + 1);
}

void SwitchableImage::_update(float deltaT)
{
}

bool SwitchableImage::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void SwitchableImage::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void SwitchableImage::updatePosition()
{
	_sprite.setPosition(this->getAbsolutePosition());
}

void SwitchableImage::updateSize()
{
	auto s = _textures[_choosenOption]->getSize();
	_sprite.scale({ _size.x / s.x,  _size.y / s.y });
}

void SwitchableImage::updateColor()
{
	_sprite.setColor(_color);
}


}