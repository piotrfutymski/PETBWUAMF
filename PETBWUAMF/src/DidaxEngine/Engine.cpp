#include "Engine.h"

namespace Didax
{

Engine::Engine()
{
	this->initEvents();
}

Engine::~Engine()
{
}

bool Engine::init(const std::function<bool(Engine*e)> _initLogicFunc, const nlohmann::json & settings)
{
	if (_initLogicFunc == nullptr)
		return false;
	if (!_initLogicFunc(this))
		return false;
	if (!_assetMeneger.loadAllAssets(settings))
		return false;


	this->openMainGUI();
	this->createBoard();
	_players[0].init(_bord, &_assetMeneger);
	_players[1].init(_bord, &_assetMeneger);
	return true;
}

void Engine::startGame()
{
	if (_events[EngineEvents::OnStart] != nullptr)
		_events[EngineEvents::OnStart](this, 0);

	//test only
	this->addUnit("testWarrior", 0, 3);
	this->addUnit("testWarrior", 1, 7);
	this->addUnit("testWarrior", 0, 1);

	this->addOrder("attack", 0);
	this->addOrder("move", 0);
	//

	this->startNextTurn();

}
	
void Engine::update(float deltaTime)
{
	_root.update(deltaTime);
}
	
void Engine::render(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(_root , states);
}
	
void Engine::input(const sf::Event & e)
{
	_root.input(e);
}

void Engine::setEvent(const EngineEvents & t, const std::function<void(Engine*, float)>& func)
{
	_events[t] = func;
}

bool Engine::end()
{
	return _state._endGame;
}


void Engine::addUnit(const std::string & name, int player, int pos)
{
	if ((player != 0 && player != 1)|| pos < 0 || pos > 7)
	{
		Logger::log("Can't add unit: " + name);
		return;
	}

	_gameObjects.push_back(std::make_unique<Unit>(this, _assetMeneger.getAsset<UnitPrototype>(name)));
	auto u = static_cast<Unit *>((_gameObjects.end() - 1)->get());
	u->setPosition(pos);
	u->setOwner(player);
	_players[player].addUnit(u);
}

void Engine::addOrder(const std::string & name, int player)
{
	if (player != 0 && player != 1)
	{
		Logger::log("Can't add order: " + name);
	}
	_gameObjects.push_back(std::make_unique<Order>(this, _assetMeneger.getAsset<OrderPrototype>(name)));
	auto o = static_cast<Order *>((_gameObjects.end() - 1)->get());
	_players[player].addOrder(o);

}

void Engine::startNextTurn()
{
	int playerNr = this->getPlayerOnTurnStart();
	this->setUnitsAndOrdersOnTurnStart(playerNr);
	this->waitForOrderChoose();
}

void Engine::waitForOrderChoose()
{
	if (_state._turnPhase == EngineState::TurnPhase::FirstPlayerMove)
		_players[0].setOrdersAsChoosable();
	else
		_players[1].setOrdersAsChoosable();
}

void Engine::endGame()
{
	_state._endGame = true;
}

void Engine::initEvents()
{
	_events[EngineEvents::OnStart] = nullptr;
}

void Engine::createBoard()
{
	_gameObjects.push_back(std::make_unique<Board>(this));
	_bord = static_cast<Board *>((_gameObjects.end() - 1)->get());
	_root.addChild(_bord->openBoardGUI(&_assetMeneger));
}

void Engine::openMainGUI()
{
	_mainGui.open(_assetMeneger.getAsset<GUIElementPrototype>("MainGUI"), &_assetMeneger, this);
	_root.addChild(_mainGui.getRoot());
}

int Engine::getPlayerOnTurnStart()
{
	auto res = 0;
	if (_state._turnPhase == EngineState::TurnPhase::BeforeStart || _state._turnPhase == EngineState::TurnPhase::PlayingSecondPlayerMoves)
		_state._turnPhase = EngineState::TurnPhase::FirstPlayerMove;
	else
	{
		_state._turnPhase = EngineState::TurnPhase::SecondPlayerMove;
		res = 1;
	}
	return res;
}

void Engine::setUnitsAndOrdersOnTurnStart(int p)
{
	int e = 0;
	if (p == 0)
		e = 1;
	_players[p].setUnitsAndOrdersAsAllay(&_root);
	_players[e].setUnitsAsEnemy(&_root);

}

}