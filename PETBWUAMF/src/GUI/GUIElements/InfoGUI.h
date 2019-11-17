#pragma once

#include "GUIElement.h"

namespace Didax
{

class InfoGUI : public GUIElement
{
public:

	InfoGUI(GUIElementPrototype * prototype, Game * game);
	~InfoGUI();

	void setUnitInfo(size_t u);
	void setOrderInfo(size_t o);

	void clearInfo();


private:

	TextArea * _info;

	std::string _name{"Name:\t"};
	std::string _description{};
	std::string _health{"Unit health:\t"};
	std::string _attack{"Unit attack:\t" };
	std::string _defence{ "Unit attack:\t" };
	std::string _armor { "Unit armor:\t" };


private:

	// Inherited via GUIElement
	virtual void _init() override;

	virtual void _initLogic() override;

};



}