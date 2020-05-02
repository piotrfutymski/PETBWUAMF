#pragma once

#include "GUIElement.h"

namespace Didax
{

class Engine;
class InfoGUI : public GUIElement
{
public:

	InfoGUI(GUIElementPrototype * prototype, Game * game, Engine * e);
	~InfoGUI();

	void setUnitInfo(size_t u);
	void setOrderInfo(size_t o);
	void setChancesInfo(size_t u, const Move & m);

	void clearInfo();


private:

	TextArea * _info;

	std::string _name{"Name:\t"};
	std::string _description{};
	std::string _health{"Unit health:\t"};
	std::string _attack{"Unit attack:\t" };
	std::string _defence{ "Unit defence:\t" };
	std::string _armor { "Unit armor:\t" };


private:

	// Inherited via GUIElement
	virtual void _init() override;

};



}