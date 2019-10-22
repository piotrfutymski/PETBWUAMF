#pragma once
#include "GUIElement.h"


namespace Didax
{
class OrderRepresentation:public GUIElement
{
public:

	OrderRepresentation(GUIElementPrototype * prototype);
	~OrderRepresentation();

	void setOrder(const std::string & name, AssetMeneger * assets);

	void setPosition(int pos);

	void setChoosed(bool c);

private:

	ImageWidget * _choosed;

private:

	// Inherited via GUIElement
	virtual void _init(AssetMeneger * assets) override;

	virtual void _initLogic(AssetMeneger * assets) override;

};

}