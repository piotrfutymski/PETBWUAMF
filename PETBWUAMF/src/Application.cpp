#include "Application.h"



Application::Application()
{
}

void Application::init(std::string settingFilePath)
{
	srand(time(NULL));

	std::ifstream stream(settingFilePath);

	if(stream.is_open())
	{
		stream >> _settings;
		Logger::log("Setting loaded succesfully");
	}
	else
	{
		Logger::log("Unable to load settings");
		return;
	}

	stream.close();

	//_window.init(Didax::WindowConfig{ _settings });
	//_clock.restart();
	//Didax::Input::setWindow(&_window.getWindow());
	//_engine.init([](Engine * e) {return true; }, _settings);
	//_engine.startGame();

	Didax::AssetMeneger::loadAllAssets(_settings);

	_game.init({});

}

int Application::run()
{
	/*try
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

	return 0;*/

	return 0;
}



/*
void Application::input()
{
	sf::Event event;

	while (_window.getWindow().pollEvent(event))
	{
		_window.processEvent(event);
		_engine.input(event);
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

	_engine.update(deltaT);
	if (_engine.isWaitingForEnd())
		_window.getWindow().close();
}

void Application::render()
{
	_window.getWindow().clear(sf::Color{ 0,0,0,255 });
	_engine.render(_window.getWindow());
	_window.render();
}


*/