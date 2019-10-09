#include "Application.h"



Application::Application()
{
}

void Application::init(std::string settingFilePath)
{
	std::ifstream stream(settingFilePath);

	if(stream.is_open())
	{
		stream >> _settings;
		_logger.log("Setting loaded succesfully");
	}
	else
	{
		_logger.log("Unable to load settings");
		return;
	}

	stream.close();

	_window.init(Didax::WindowConfig{ _settings });

	_clock.restart();

	Didax::Input::setWindow(&_window.getWindow());

	_game.init(_settings);

}

int Application::run()
{
	try
	{
		while (_window.getWindow().isOpen())
		{
			update();
			render();
			input();
		}
	}
	catch (std::exception & e)
	{
	#ifdef DEBUG
		std::cout << e.what();
	#endif // DEBUG

		return 1;
	}

	return 0;
}

void Application::input()
{
	sf::Event event;

	while (_window.getWindow().pollEvent(event))
	{
		_window.processEvent(event);
		_game.input(event);
	}

}

void Application::update()
{
	auto time = _clock.getElapsedTime();
	_clock.restart();
	float deltaT = time.asSeconds();
	frames++;
	sec += deltaT;
	if (sec > 1)
	{
		sec = 0;
		std::cout << frames << std::endl;
		frames = 0;
	}

	_game.update(deltaT);
}

void Application::render()
{
	_window.getWindow().clear(sf::Color{ 0,0,0,255 });
	_game.render(_window.getWindow());
	_window.render();
}
