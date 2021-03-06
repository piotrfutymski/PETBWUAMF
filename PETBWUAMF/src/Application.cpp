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

	Didax::AssetMeneger::loadAllAssets(_settings);
	_game.init({});
	_game.initOrderFunctions();
	_engine.init(_settings, &_game);

}

int Application::run()
{
	_engine.run();

	while (!_game.isGameEnded())
	{
		auto gamedata = _game.playTurn(this->getMoveFromConsole());
		_reporter.SaveTurn(gamedata);
	}

	return 0;
}


Move Application::getMoveFromConsole()
{


	bool reset = true;

	//petla cala
	while (reset)
	{
		Move res;
		_consoleUI.clear();
		_consoleUI.logState(_game, _reporter);
		_consoleUI.makeMove(_game);
		Order * order = nullptr;
		int oID, x, y, id, rest=0;
		//petla wyboru rozkazu 
		while (1)
		{
			Logger::log("----------------------Pick order id----------------------");
			std::cin >> oID;
			if (oID == -1)
			{
				rest = 1;
				break;
			}
			order = _game.getObject<Order>(oID);
			if (order == nullptr)
			{
				Logger::log("-------------------Order doesn't exist-------------------");
			}
			else
			{
				auto poss = _game.getPossibleOrders(_game.getActivePlayer());
				if (std::find(poss.begin(), poss.end(), order->getID()) != poss.end())
					break;
			}
		}
		if (rest)
			continue;
		//do tad bylo fajnie, ale chce dac  mozliwosc wycofania sie z rozkazu
		res.orderID = oID;
		Logger::log("---------------------------------------------------------");
		for (size_t i = 0; i < order->getTargetsCount(); i++)
		{
			if (order->getPrototype()->_target == OrderPrototype::TargetType::MoveT)
			{
				_consoleUI.MoveMap(_game, order);
				Logger::log("----------------------Choose Position (int) (int)--------");
				std::cin >> x;
				if (x == -1)
				{
					rest = 1;
					break;
				}
				std::cin >> y;
				if (y == -1)
				{
					rest = 1;
					break;
				}

				res.positions.push_back({ x,y });
				Logger::log("---------------------------------------------------------");
			}
			else if(order->getPrototype()->_target == OrderPrototype::TargetType::AttackT)
			{
				Logger::log("------------------Choose Target ID (int)-----------------");
				_consoleUI.AttackMap(_game, order);
				std::cin >> id;
				if (id == -1)
				{
					rest = 1;
					break;
				}

				res.units.push_back(id);
				Logger::log("---------------------------------------------------------");
			}
			else if (order->getPrototype()->_target == OrderPrototype::TargetType::ChargeT)
			{
				_consoleUI.MoveMap(_game, order);
				Logger::log("----------------------Choose Position (int) (int)--------");
				std::cin >> x;
				if (x == -1)
				{
					rest = 1;
					break;
				}
				std::cin >> y;
				if (y == -1)
				{
					rest = 1;
					break;
				}

				res.positions.push_back({ x,y });
				Logger::log("---------------------------------------------------------");
				Logger::log("------------------Choose Target ID (int)-----------------");
				_consoleUI.ChargeMap(_game, order, res);
				std::cin >> id;
				if (id == -1)
				{
					rest = 1;
					break;
				}

				res.units.push_back(id);
				Logger::log("---------------------------------------------------------");
			}


		}
		if (rest)
			continue;
		return res;
	}
	
}

