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
	_engine.init(_settings, &_game);
	PrototypeInitializer::initGame(&_game);
	PrototypeInitializer::initPrototypes();

}

int Application::run()
{

	while (!_game.isEnded())
	{
		auto gamedata = _game.playMove(this->getMoveFromConsole());
	}

	return 0;
}


Move Application::getMoveFromConsole()
{
	Move res;
	res.unitID = _game.getActiveUnit()->getID();
	_consoleUI.clear();
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
			_consoleUI.MoveMap(_game, order);
			Logger::log("----------------------Choose Position (int) (int)--------");
			int x, y;
			std::cin >> x;
			std::cin >> y;
			res.positions.push_back({ x,y });
			Logger::log("---------------------------------------------------------");
		}
		else
		{
			Logger::log("------------------Choose Target ID (int)-----------------");
			if (i == 0)
				_consoleUI.AttackMap(_game, order);
			else
				_consoleUI.ChargeMap(_game, order, res);
			int id;
			std::cin >> id;
			res.units.push_back(id);
			Logger::log("---------------------------------------------------------");
		}
	}
	return res;

}

