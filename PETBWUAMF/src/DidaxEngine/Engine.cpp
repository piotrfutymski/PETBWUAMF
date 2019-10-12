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

	_state = EngineState::FirstPlayerMove;
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

void Engine::changeState(const EngineState & state)
{
	_state = state;
	Logger::log("State has been changed");
}

Engine::EngineState Engine::getState() const
{
	return _state;
}

void Engine::initEvents()
{
	_events[EngineEvents::OnStart] = nullptr;
}

void Engine::createBoard()
{
	_gameObjects.push_back(std::make_unique<Board>(this));
	_bord = static_cast<Board *>((_gameObjects.end() - 1)->get());
	_root.addChild(_bord->openHourglass(&_assetMeneger));
}

}