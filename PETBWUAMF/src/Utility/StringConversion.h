#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class StringConversion
{
public:
	static std::string keyToString(const sf::Keyboard::Key & k);
};

