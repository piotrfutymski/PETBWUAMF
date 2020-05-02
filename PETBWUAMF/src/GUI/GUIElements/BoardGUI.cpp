#include "BoardGUI.h"
#include "../Engine.h"

void Didax::BoardGUI::_init()
{
	for (size_t i = 0; i < MAP_WIDTH; i++)
	{
		for (size_t j = 0; j < MAP_HEIGHT; j++)
		{
			_widgets.push_back(std::make_unique<Button>());
			_positions[i][j].button = static_cast<Button *>((_widgets.end() - 1)->get());
			_root->addChild(_positions[i][j].button);
		}
	}


	//root

	_root->setSize({ _prototype->_values["widthR"], (_prototype->_values["heightR"]) });
	_root->setPosition({ _prototype->_values["xPos"], (_prototype->_values["yPos"]) });
	auto text = AssetMeneger::getAsset<TextureAsset>(_prototype->_strings["background"]);
	_root->setTexture(&text->_texture);

	//buttons

	text = AssetMeneger::getAsset<TextureAsset>(_prototype->_strings["border"]);
	auto padd = _prototype->_values["Padd"];
	auto p_size = _prototype->_values["PosSize"];

	for (size_t i = 0; i < MAP_WIDTH; i++)
	{
		for (size_t j = 0; j < MAP_HEIGHT; j++)
		{
			_positions[i][j].pos = { (int)i,(int)j };
			_positions[i][j].button->setPosition(i*(padd + p_size), j*(padd + p_size));
			_positions[i][j].button->setSize({ p_size, p_size });
			_positions[i][j].button->setTexture(&text->_texture);
			this->setPositionInState(PositionState::Inactive, { (int)i,(int)j });
		}
	}

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			_positions[i][j].button->setWidgetEvent(Widget::CallbackType::onRelease, [this, i, j](Widget*, float) {
				_engine->positionOnRelease(this->getOnPos({ i,j }));
			});
		}
	}

}

void Didax::BoardGUI::setPositionInState(PositionState st, const sf::Vector2i & p, int uID, int owner)
{
	if (st == PositionState::Movable|| st == PositionState::ChoosableUnit)
		_positions[p.x][p.y].button->setActive(true);
	else
		_positions[p.x][p.y].button->setActive(false);

	_positions[p.x][p.y].s = st;
	_positions[p.x][p.y].button->setColor(this->colorFromState(st));

	if (st == PositionState::Enemy || st == PositionState::Allay || st == PositionState::ActiveUnit || st == PositionState::Choosed || st == PositionState::ChoosableUnit)
	{
		if (_positions[p.x][p.y].unitID == -1)
			_positions[p.x][p.y].unitID = uID;
		if (_positions[p.x][p.y].unitOwner == -1)
			_positions[p.x][p.y].unitOwner = owner;
	}
	else
	{
		_positions[p.x][p.y].unitID = -1;
		_positions[p.x][p.y].unitOwner = -1;
	}

}

void Didax::BoardGUI::setPosTargets(const std::vector<Target>& targets)
{
	for (auto &t: targets)
		this->setPositionInState(PositionState::Movable, { t.position });

}

void Didax::BoardGUI::setAttackTargets(const std::vector<Target>& targets)
{
	for (auto &t : targets)
		this->setPositionInState(PositionState::ChoosableUnit, { _game->getObject<Unit>(t.unit)->getPosition() });
}

void Didax::BoardGUI::setChargeTargets(const std::vector<Target>& targets)
{
}

void Didax::BoardGUI::setBuffTargets(const std::vector<Target>& targets)
{
}



sf::Color Didax::BoardGUI::colorFromState(PositionState s)
{
	if (s == PositionState::Inactive)
		return sf::Color::White;
	if (s == PositionState::Movable)
		return sf::Color{ 239,228,176 };
	if (s == PositionState::ActiveUnit)
		return sf::Color{ 200,172,40 ,120};
	if (s == PositionState::Allay)
		return sf::Color{ 60,170,13 ,120};
	if (s == PositionState::ChoosableUnit)
		return sf::Color{ 78,223,239 ,120};
	if (s == PositionState::Choosed)
		return sf::Color{ 180,155,129 };
	else
		return sf::Color{ 255,102,102 ,120};
}

Didax::BoardGUI::BoardGUI(GUIElementPrototype * prototype, Game * game, Engine * e):GUIElement(prototype, game, e)
{
}

Didax::BoardGUI::~BoardGUI()
{
}

void Didax::BoardGUI::setTargets(const std::vector<Target>& targets, OrderPrototype::TargetType t)
{
	if (t == OrderPrototype::TargetType::AttackT)
		this->setAttackTargets(targets);
	else if (t == OrderPrototype::TargetType::MoveT || t== OrderPrototype::TargetType::CreateT)
		this->setPosTargets(targets);
	else if (t == OrderPrototype::TargetType::ChargeT)
		this->setChargeTargets(targets);
	else if (t == OrderPrototype::TargetType::BuffAllayT || t == OrderPrototype::TargetType::BuffEnemyT)
		this->setBuffTargets(targets);

}

void Didax::BoardGUI::reloadFromGame()
{
	for (size_t i = 0; i < MAP_WIDTH; i++)
	{
		for (size_t j = 0; j < MAP_HEIGHT; j++)
		{
			auto mapspot = _game->getMap()[{ (int)i, (int)j}];
			if(! (mapspot.content == Map::SpotContent::Unit))
				this->setPositionInState(PositionState::Inactive, { (int)i,(int)j });
			else if(mapspot.content == Map::SpotContent::Unit)
			{
				auto u = mapspot.unit;
				auto owner = u->getOwner();
				if(owner != _game->getActivePlayer())
					this->setPositionInState(PositionState::Enemy, { (int)i,(int)j },u->getID(),owner);
				else
				{
					if(u->getID() != _game->getActiveUnitID())
						this->setPositionInState(PositionState::Allay, { (int)i,(int)j }, u->getID(), owner);
					else
						this->setPositionInState(PositionState::ActiveUnit, { (int)i,(int)j }, u->getID(), owner);
				}
			}
		}
	}
}

sf::Vector2i Didax::BoardGUI::getLastChoosed() const
{
	return _lastChoosed;
}

Didax::BoardGUI::PositionWidget Didax::BoardGUI::getOnPos(const sf::Vector2i & p) const
{
	return _positions[p.x][p.y];
}

void Didax::BoardGUI::destroyOnPos(const sf::Vector2i & p)
{
	_positions[p.x][p.y].unitID = (size_t)-1;
}
