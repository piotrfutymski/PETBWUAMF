#include "Engine.h"

namespace Didax
{

Engine::Engine()
{

}

Engine::~Engine()
{
}

bool Engine::init(const nlohmann::json & settings, Game * g)
{
	_window.init(Didax::WindowConfig{ settings });
	_clock.restart();
	Input::setWindow(&_window.getWindow());
	_window.getWindow().setActive(false);

	_elements.push_back(std::make_unique<BoardGUI>(AssetMeneger::getAsset<GUIElementPrototype>("BoardGUI")));
	_board = static_cast<BoardGUI *>(_elements.begin()->get());

	_board->open(&_updater);

	return true;
}

Move Engine::getMove()
{
	return Move();
}

void Engine::setMoveRes(const MoveRes & moveRes)
{
}

void Engine::run()
{
	_window.getWindow().setActive(true);
	while (_window.getWindow().isOpen())
	{
		update();
		render();
		input();
	}
}
	
void Engine::update()
{
	auto time = _clock.getElapsedTime();
	_clock.restart();
	float deltaT = time.asSeconds();

	// updating

	_updater.update(deltaT);
}
	
void Engine::render()
{
	_window.getWindow().clear(sf::Color{ 0,0,0,255 });

	//rendering

	_window.getWindow().draw(_updater);

	//

	_window.render();
}
	
void Engine::input()
{
	sf::Event event;

	while (_window.getWindow().pollEvent(event))
	{
		_window.processEvent(event);

		if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Escape)
			_window.getWindow().close();

		_updater.input(event);
	}
}



}