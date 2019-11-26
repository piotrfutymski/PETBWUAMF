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
	_board->open(&_updater, this);

	_elements.push_back(std::make_unique<InfoGUI>(AssetMeneger::getAsset<GUIElementPrototype>("InfoGUI"), g));
	_info = static_cast<InfoGUI *>((_elements.begin()+1)->get());
	_info->open(&_updater, this);

	this->initGame();
	this->startTurn();

	return true;
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
			this->escEvent();
		if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Return)
			_window.getWindow().close();

		_updater.input(event);
	}
}

void Engine::startTurn()
{
	_board->reloadFromGame();
	this->reloadOrders();
	this->reloadUnits();

	_choosedOrder = (size_t)(-1);
	_state = EngineState::ChoosingOrder;
}

void Engine::reloadOrders()
{
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
		if (std::find(choosable.begin(), choosable.end(), ord->getOrderID()) != choosable.end())
		{
			ord->resetPosition();
			ord->show();
			ord->setChoosable(true);
		}
		else if (std::find(showable.begin(), showable.end(), ord->getOrderID()) != showable.end())
		{
			ord->resetPosition();
			ord->show();
			ord->setChoosable(false);
		}
		else
		{
			ord->hide();
		}
	}
}

void Engine::reloadUnits()
{
	auto it = _units.begin();
	while (it != _units.end())
	{
		if (_game->getObject<Unit>((*it)->getUnitID()) == nullptr)
		{
			_board->destroyOnPos((*it)->getPosition());
			it->get()->hide();
		}
		else
			(*it)->recalculate();
		++it;
	}
}

void Engine::orderChoosed(size_t orderID)
{
	_choosedOrder = orderID;
	_state = EngineState::ChoosingTarget;
	this->prepareBoardOnChoosed();
	this->prepareOrdersOnChoosed();

	auto choosed = _game->getObject<Order>(_choosedOrder);
	if (choosed->getPrototype()->_target == OrderPrototype::TargetType::BuffT)
		this->playMove({ _choosedOrder, {},{} });
}

void Engine::prepareOrdersOnChoosed()
{
	for (auto x : _orders)
	{
		x->setChoosable(false);
	}
	auto choosed = this->findRepresentationWithOrder(_choosedOrder);
	choosed->setChoosen();
}

void Engine::prepareBoardOnChoosed()
{
	auto choosed = _game->getObject<Order>(_choosedOrder);
	auto targets = _game->getPossibleTargets(_choosedOrder);
	auto orderT = choosed->getPrototype()->_target;
	_board->setTargets(targets, orderT);

	for (auto t : targets)
		if (orderT == OrderPrototype::TargetType::AttackT) //TODO
			findRepresentationWithUnit(t.unit)->setChoosable(true);

}

void Engine::targetChoosed(const sf::Vector2i & pos)
{
	auto choosed = _game->getObject<Order>(_choosedOrder);
	auto orderT = choosed->getPrototype()->_target;

	if (orderT == OrderPrototype::TargetType::MoveT)
		this->playMove({ _choosedOrder,{},{pos} });
	else if (orderT == OrderPrototype::TargetType::AttackT)
		this->playMove({ _choosedOrder,{(size_t)(_board->getOnPos(pos).unitID)}, {} });

	for (auto & x : _units)
	{
		x->setChoosable(false);
	}

}

void Engine::playMove(const Move & m)
{
	_game->playTurn(m);
	this->startTurn();
}

void Engine::escEvent()
{
	if (_state == EngineState::ChoosingTarget)
		this->startTurn();
}

OrderRepresentation * Engine::findRepresentationWithOrder(size_t o)
{
	return *(std::find_if(_orders.begin(), _orders.end(), [o](OrderRepresentation* arg) {
		return (arg->getOrderID() == o);
	}));
}

UnitRepresentation * Engine::findRepresentationWithUnit(size_t u)
{
	return (*(std::find_if(_units.begin(), _units.end(), [u](std::unique_ptr<UnitRepresentation> & arg) {
		return (arg->getUnitID() == u);
	}))).get();
}

void Engine::initGame()
{
	OrderRepresentation::onHoverIn = orderOnHoverIn;
	OrderRepresentation::onHoverOut = orderOnHoverOut;
	OrderRepresentation::onRelease = orderOnRelease;

	UnitRepresentation::onHoverIn = unitOnHoverIn;
	UnitRepresentation::onHoverOut = unitOnHoverOut;
	UnitRepresentation::onRelease = unitOnRelease;

	BoardGUI::onHoverIn = positionOnHoverIn;
	BoardGUI::onHoverOut = positionOnHoverOut;
	BoardGUI::onRelease = positionOnRelease;

	for (auto & x : _game->getHolder<Unit>())
	{
		_units.push_back(std::make_unique<UnitRepresentation>(AssetMeneger::getAsset<GUIElementPrototype>("UnitRepresentation"), _game));
		auto ptr = (_units.end() - 1)->get();
		ptr->open(_board->getRoot(), this);
		ptr->setUnit(x->getID());
	}

	int i = 0;
	int j = 0;
	for (auto & x : _game->getHolder<Order>())
	{
		_elements.push_back(std::make_unique<OrderRepresentation>(AssetMeneger::getAsset<GUIElementPrototype>("OrderRepresentation"), _game));
		auto ptr = static_cast<OrderRepresentation *>((_elements.end() - 1)->get());
		_orders.push_back(ptr);
		ptr->open(&_updater, this);
		ptr->setOrder(x->getID());
		if(x->getOwner() == 0)
			ptr->setPosition(i++);
		else
			ptr->setPosition(j++);
	}
}

void Engine::orderOnHoverIn(OrderRepresentation * o, Engine * e)
{
	e->_info->setOrderInfo(o->getOrderID());
	if (e->_state == EngineState::ChoosingOrder&& o->isChoosable())
		o->setHoverInTime();
}

void Engine::orderOnHoverOut(OrderRepresentation * o, Engine * e)
{
	e->_info->clearInfo();
	if (e->_state == EngineState::ChoosingOrder && o->isChoosable())
		o->resetPosition();
}

void Engine::orderOnRelease(OrderRepresentation * o, Engine * e)
{
	if (e->_state == EngineState::ChoosingOrder&& o->isChoosable())
		e->orderChoosed(o->getOrderID());
}

void Engine::unitOnHoverIn(UnitRepresentation * o, Engine * e)
{
	e->_info->setUnitInfo(o->getUnitID());
}

void Engine::unitOnHoverOut(UnitRepresentation * o, Engine * e)
{
	e->_info->clearInfo();
}

void Engine::unitOnRelease(UnitRepresentation * o, Engine * e)
{
	if (e->_state == EngineState::ChoosingTarget&& o->isChoosable())
		e->targetChoosed(o->getPosition());
}

void Engine::positionOnHoverIn(BoardGUI::PositionWidget * o, Engine * e)
{
}

void Engine::positionOnHoverOut(BoardGUI::PositionWidget * o, Engine * e)
{
}

void Engine::positionOnRelease(BoardGUI::PositionWidget * o, Engine * e)
{
	if (e->_state == EngineState::ChoosingTarget&& o->s == BoardGUI::PositionState::Movable)
		e->targetChoosed(o->pos);
}




}