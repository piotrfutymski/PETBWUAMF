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
	if (!_assetMeneger.loadAssetsFromFile(settings["assetsFilename"]))
		return false;

	this->createBoard();
	return true;
}

void Engine::startGame()
{
	if (_events[EngineEvents::OnStart] != nullptr)
		_events[EngineEvents::OnStart](this, 0);

	_state._turnPhase = EngineState::TurnPhase::FirstPlayerMove;

	//test only
	this->addUnit("testWarrior", 3);
	this->addUnit("testWarrior", 8);
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

void Engine::nextPhase()
{
	if (_state._turnPhase == EngineState::TurnPhase::FirstPlayerMove)
		this->changePhase(EngineState::TurnPhase::SecondPlayerMove);
	else if (_state._turnPhase == EngineState::TurnPhase::SecondPlayerMove)
		this->changePhase(EngineState::TurnPhase::PlayingMoves);
	else if (_state._turnPhase == EngineState::TurnPhase::PlayingMoves)
		this->changePhase(EngineState::TurnPhase::FirstPlayerMove);
}

EngineState::TurnPhase Engine::getPhase() const
{
	return _state._turnPhase;
}

void Engine::addUnit(const std::string & name, int pos)
{
	_gameObjects.push_back(std::make_unique<Unit>(this, _assetMeneger.getAsset<UnitPrototype>(name)));
	int site = 0;
	if (pos >= 8)
		site = 1;
	_playerUnits[site].push_back(static_cast<Unit *>((_gameObjects.end() - 1)->get()));
	auto u = *(_playerUnits[site].end() - 1);
	_root.addChild(u->setOnTable(&_assetMeneger, pos));
}


void Engine::initEvents()
{
	_events[EngineEvents::OnStart] = nullptr;
}

void Engine::createBoard()
{
	_gameObjects.push_back(std::make_unique<Board>(this));
	_bord = static_cast<Board *>((_gameObjects.end() - 1)->get());
	_root.addChild(_bord->openSideGUI(&_assetMeneger));
	_root.addChild(_bord->openMainGUI(&_assetMeneger));
}

void Engine::changePhase(const EngineState::TurnPhase & p)
{
	Logger::log("State has been changed");
	_state._turnPhase = p;

}

}