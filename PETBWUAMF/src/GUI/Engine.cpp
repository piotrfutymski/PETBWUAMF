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

	this->initObjects();
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
	if (e.type == sf::Event::EventType::KeyPressed && _onEsc != nullptr)
	{
		if (e.KeyPressed == sf::Keyboard::Escape)
			this->_onEsc();
	}
	_root.input(e);
}

void Engine::setEvent(const EngineEvents & t, const std::function<void(Engine*, float)>& func)
{
	_events[t] = func;
}

bool Engine::isWaitingForEnd()
{
	return _state._endGame;
}


void Engine::addUnit(const std::string & name, int player, int pos)
{
	if ((player != 0 && player != 1)|| pos < 0 || pos > 7)
	{
		Logger::log("Can't add unit: " + name + " - Bad player nr or position nr");
		return;
	}
	auto prot = _assetMeneger.getAsset<UnitPrototype>(name);

	if (prot == nullptr)
	{
		Logger::log(name +" -This unit does not exist");
		return;
	}

	_gameObjects.push_back(std::make_unique<Unit>(prot, &_assetMeneger));
	auto u = static_cast<Unit *>((_gameObjects.end() - 1)->get());
	u->setPosition(pos);
	u->setOwner(player);
	_players[player].addUnit(u);
}

void Engine::addOrder(const std::string & name, int player)
{
	if (player != 0 && player != 1)
	{
		Logger::log("Can't add order: " + name + " - Bad player nr (can be 0 or 1)");
	}

	auto prot = _assetMeneger.getAsset<OrderPrototype>(name);
	if (prot == nullptr)
	{
		Logger::log(name + " -This order does not exist");
		return;
	}

	_gameObjects.push_back(std::make_unique<Order>(prot,& _assetMeneger));
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
		_players[0].setOrdersWaitingForChoose();
	else
		_players[1].setOrdersWaitingForChoose();
}

void Engine::orderChoosed()
{
	if (_state._turnPhase == EngineState::TurnPhase::FirstPlayerMove)
		_players[0].setForWaitingOnOrderTarget(_state._choosedOrder);
	else
		_players[1].setForWaitingOnOrderTarget(_state._choosedOrder);

	_onEsc = [this]() {this->resetOrderChoose(); };
}

void Engine::orderUnchoosed()
{
	this->waitForOrderChoose();
}

void Engine::unitChoosed()
{
	if (_state._turnPhase == EngineState::TurnPhase::FirstPlayerMove)
		_players[0].setForWaitingOnOrderTarget(_state._choosedOrder);
	else
		_players[1].setForWaitingOnOrderTarget(_state._choosedOrder);

	_onEsc = [this]() {this->resetUnitChoose(); };
}

void Engine::unitUnchoosed()
{
}

void Engine::nextSpotChoosed()
{
}

void Engine::endGame()
{
	_state._endGame = true;
}

void Engine::initObjects()
{
}

void Engine::initEvents()
{
	_events[EngineEvents::OnStart] = nullptr;
}

void Engine::createBoard()
{
	_gameObjects.push_back(std::make_unique<Board>(&_assetMeneger));
	_bord = static_cast<Board*>((_gameObjects.end() - 1)->get());
	_bord->openGUI(&_root, & _assetMeneger);
}

void Engine::openMainGUI()
{
	_mainGui = std::make_unique<MainGUI>(_assetMeneger.getAsset<GUIElementPrototype>("MainGUI"));
	_mainGui.get()->open(&_root, &_assetMeneger);
	static_cast<MainGUI *>(_mainGui.get())->setOnPressToButton("exit", [this]() {this->endGame(); });
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

void Engine::resetOrderChoose()
{
	_state._choosedOrder = nullptr;
}

void Engine::resetUnitChoose()
{
}

void Engine::showUnitDescription(Unit * u)
{
	auto s = u->getPrototype()->_description;
	_mainGui->setDescription(s);
}

void Engine::hideUnitDescription(Unit * u)
{
	_mainGui->setDescription("");
}

void Engine::showOrderDescription(Order * o)
{
	auto s = o->getPrototype()->_description;
	_mainGui->setDescription(s);
}

void Engine::hideOrderDescription(Order * o)
{
	_mainGui->setDescription("");
}

void Engine::orderChoosed(Order * o)
{
	_state._choosedOrder = o;
	this->orderChoosed();
}

}