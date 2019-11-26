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
	_game = g;

	_elements.push_back(std::make_unique<BoardGUI>(AssetMeneger::getAsset<GUIElementPrototype>("BoardGUI"), g));
	_board = static_cast<BoardGUI *>(_elements.begin()->get());
	_board->open(&_updater);

	_elements.push_back(std::make_unique<InfoGUI>(AssetMeneger::getAsset<GUIElementPrototype>("InfoGUI"), g));
	_info = static_cast<InfoGUI *>((_elements.begin()+1)->get());
	_info->open(&_updater);

	this->initGame();
	this->startTurn();

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

void Engine::startTurn()
{
	_board->reloadFromGame();
	auto orCH = _game->getPossibleOrders(_game->getActivePlayer());

	std::vector<size_t> choosable;
	std::vector<size_t> showable;

	for (auto & ord : orCH)
	{
		choosable.push_back(ord);
	}

	for (auto & ord : _game->getHolder<Order>())
	{
		if (ord->getOwner() == _game->getActivePlayer())
			showable.push_back(ord->getID());
	}

	for (auto & ord : _orders)
	{
		if (std::find(choosable.begin(), choosable.end(), ord->getOrderId()) != choosable.end())
		{
			ord->show();
			ord->setChoosable(true);
		}
		else if (std::find(showable.begin(), showable.end(), ord->getOrderId()) != showable.end())
		{
			ord->show();
			ord->setChoosable(false);
		}
		else
		{
			ord->hide();
		}
	}
}

void Engine::orderChoosed(size_t orderID)
{
	_choosedOrder = orderID;
}

void Engine::initGame()
{
	for (auto & x : _game->getHolder<Unit>())
	{
		_elements.push_back(std::make_unique<UnitRepresentation>(AssetMeneger::getAsset<GUIElementPrototype>("UnitRepresentation"), _game));
		auto ptr = static_cast<UnitRepresentation *>((_elements.end() - 1)->get());
		_units.push_back(ptr);
		ptr->open(_board->getRoot());
		ptr->setUnit(x->getID());
		ptr->set_onHoverIn([=, &x] {
			_info->setUnitInfo(x->getID());
		});

		ptr->set_onHoverOut([=] {
			_info->clearInfo();
		});
	}

	int i = 0;
	int j = 0;
	for (auto & x : _game->getHolder<Order>())
	{
		_elements.push_back(std::make_unique<OrderRepresentation>(AssetMeneger::getAsset<GUIElementPrototype>("OrderRepresentation"), _game));
		auto ptr = static_cast<OrderRepresentation *>((_elements.end() - 1)->get());
		_orders.push_back(ptr);
		ptr->open(&_updater);
		ptr->setOrder(x->getID());
		if(x->getOwner() == 0)
			ptr->setPosition(i++);
		else
			ptr->setPosition(j++);
	}

	OrderRepresentation::onHoverIn = ([=](OrderRepresentation * o) {
		_info->setOrderInfo(o->getOrderId());
	});

	OrderRepresentation::onHoverOut = ([=](OrderRepresentation * o) {
		_info->clearInfo();
	});

	OrderRepresentation::onReleaseIfChoosabe = ([=](OrderRepresentation * o) {
		this->orderChoosed(o->getOrderId());
	});
}



}