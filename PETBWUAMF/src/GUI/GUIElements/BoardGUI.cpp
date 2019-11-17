#include "BoardGUI.h"

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
			_positions[i][j].button->setPosition(i*(padd + p_size), j*(padd + p_size));
			_positions[i][j].button->setSize({ p_size, p_size });
			_positions[i][j].button->setTexture(&text->_texture);
			this->setPositionInState(PositionState::Movable, { (int)i,(int)j });
		}
	}

}

void Didax::BoardGUI::_initLogic()
{

}

void Didax::BoardGUI::setPositionInState(PositionState st, const sf::Vector2i & p, int uID, int owner)
{
	if (st == PositionState::Movable|| st == PositionState::ChoosableUnit)
		_positions[p.x][p.y].button->setActive(true);
	else
		_positions[p.x][p.y].button->setActive(false);

	_positions[p.x][p.y].s = st;
	_positions[p.x][p.y].button->setColor(this->colorFromState(st));

	if (st == PositionState::Enemy || st == PositionState::Allay || st == PositionState::ActiveUnit || st == PositionState::Choosed)
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

sf::Color Didax::BoardGUI::colorFromState(PositionState s)
{
	if (s == PositionState::Inactive)
		return sf::Color::White;
	if (s == PositionState::Movable)
		return sf::Color{ 239,228,176 };
	if (s == PositionState::ActiveUnit)
		return sf::Color{ 200,172,40 };
	if (s == PositionState::Allay)
		return sf::Color{ 60,170,13 };
	if (s == PositionState::ChoosableUnit)
		return sf::Color{ 78,223,239 };
	if (s == PositionState::Choosed)
		return sf::Color{ 180,155,129 };
	else
		return sf::Color{ 255,102,102 };
}

Didax::BoardGUI::BoardGUI(GUIElementPrototype * prototype):GUIElement(prototype)
{
}

Didax::BoardGUI::~BoardGUI()
{
}

void Didax::BoardGUI::setTargets(const std::vector<OrderPrototype::Target>& targets)
{
}

sf::Vector2i Didax::BoardGUI::getLastChoosed() const
{
	return _lastChoosed;
}
