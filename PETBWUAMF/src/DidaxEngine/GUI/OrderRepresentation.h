#pragma once
#include "GUIElement.h"


namespace Didax
{
class OrderRepresentation:public GUIElement
{
public:

	OrderRepresentation();
	~OrderRepresentation();

	void setChoosable();
	void setOrder(const std::string & name, AssetMeneger * assets);

	void setPosition(int pos);


	

private:

	bool _chosable{ false };

private:

	// Inherited via GUIElement
	virtual void _init(GUIElementPrototype * prototype, AssetMeneger * assets) override;
	virtual void _initLogic(GUIElementPrototype * prototype, AssetMeneger * assets) override;

};

}