#pragma once
#include <fstream>
#include <SFML/Window.hpp>
#include <exception>
#include <nlohmann/json.hpp>

namespace Didax
{

class WindowConfig
{
public:
	WindowConfig();

	WindowConfig(const nlohmann::json & j);

	void loadFromJson(const nlohmann::json & j);

	sf::VideoMode _mode;
	sf::Uint32 _windowStyle;
	int _framerateLimit;

};

}