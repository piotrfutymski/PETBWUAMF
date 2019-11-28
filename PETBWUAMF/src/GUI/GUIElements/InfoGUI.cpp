#include "InfoGUI.h"

Didax::InfoGUI::InfoGUI(GUIElementPrototype * prototype, Game * game)
	:GUIElement(prototype ,game)
{
}

Didax::InfoGUI::~InfoGUI()
{
}

void Didax::InfoGUI::setUnitInfo(size_t u)
{
	auto unit = _game->getObject<Unit>(u);
	std::string n = _name + unit->getPrototype()->getName() +"\n";
	std::string d = unit->getPrototype()->_description + "\n";
	std::string h = _health + std::to_string(unit->getHealth()) + "/" +std::to_string(unit->getPrototype()->_health) + "\n";
	std::string a = _attack + std::to_string(unit->getAttack()) + "\n";
	std::string df = _defence + std::to_string(unit->getDefence()) + "\n";
	std::string ar = _armor + std::to_string(unit->getArmor()) + "\n";

	_info->setText(n + d + h + a + df + ar);
	_info->resizeToText();

}

void Didax::InfoGUI::setOrderInfo(size_t o)
{
	auto order = _game->getObject<Order>(o);
	std::string n = _name + order->getPrototype()->getName() + "\n";
	std::string d = order->getPrototype()->_description + "\n";

	_info->setText(n + d);
	_info->resizeToText();

}

void Didax::InfoGUI::setChancesInfo(size_t u, const Move & m)
{
	auto unit = _game->getObject<Unit>(u);
	auto order = _game->getObject<Order>(m.orderID);

	auto v = order->getChances(_game, m);
	if (v > 0)
	{
		auto s = std::to_string(v);
		s.resize(2);
		_info->setText("Average damage:	" + s+"\n");
		_info->resizeToText();
	}

}

void Didax::InfoGUI::clearInfo()
{
	_info->setText("");
	_info->resizeToText();
}

void Didax::InfoGUI::_init()
{
	_widgets.push_back(std::make_unique<TextArea>());
	_info = static_cast<TextArea *>(_widgets[1].get());

	//root

	auto text = AssetMeneger::getAsset<TextureAsset>(_prototype->_strings["background"]);
	_root->setPosition(1420, 400);
	_root->setSize({ 400, 300 });
	_root->setTexture(&text->_texture);
	_root->addChild(_info);

	//info

	_info->setPosition({ 20,20 });
	_info->setFont(&AssetMeneger::getAsset<FontAsset>("data/fonts/DKNorthumbria.otf")->_font);
	_info->setCharacterSize(15);

}

void Didax::InfoGUI::_initLogic(Engine * e)
{
}
