#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Didax
{
class StringConversion
{
public:
	static std::string keyToString(const sf::Keyboard::Key & k);
};
}
