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
	while (!_game.isEnded())
	{
		while (!_game.playMove(this->getMoveFromConsole()))
			;
	}

	return 0;
}


Move Application::getMoveFromConsole()
{
	Move res;
	res.unitID = _game.getActiveUnit()->getID();
	
	_consoleUI.logState(_game);
	_consoleUI.makeMove(_game);

	Order * order = nullptr;
	int oID;
	while (1)
	{
		Logger::log("----------------------Pick order id----------------------");
		std::cin >> oID;
		order = _game.getObject<Order>(oID);
		if (order == nullptr)
		{
			Logger::log("-------------------Order doesn't exist-------------------");
			continue;
		}
		if (order->canBeUsed(_game.getActiveUnit()))
		{
			Logger::log("----------------------Choosed order: " + std::to_string(oID) + "-------------------");
			break;
		}
		Logger::log("-------------------Order can't be used-------------------");
	}
	res.orderID = oID;
	Logger::log("---------------------------------------------------------");
	for (size_t i = 0; i < order->getTargetsCount(); i++)
	{
		if (order->getTargetType(i) == OrderPrototype::TargetType::Position_target)
		{
			_consoleUI.MoveMap(_game, order, i);

			Logger::log("----------------------Choose Position (int) (int)--------");
			int x, y;
			std::cin >> x;
			std::cin >> y;
			res.positions.push_back({ x,y });
			Logger::log("---------------------------------------------------------");
		}
		else
		{
			_consoleUI.AttackMap(_game);
			Logger::log("------------------Choose Target ID (int)-----------------");
			if (_game.getActivePlayer() == 1)
				_consoleUI.logStateUnits(_game, 0);
			else
				_consoleUI.logStateUnits(_game, 1);
			int id;
			std::cin >> id;
			res.units.push_back(id);
			Logger::log("---------------------------------------------------------");
		}
	}
	return res;

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