#pragma once
#include "GUIElement.h"


namespace Didax
{
class OrderRepresentation:public GUIElement
{
public:

	OrderRepresentation(GUIElementPrototype * prototype);
	~OrderRepresentation();

	void setChoosable(const std::function<void()> & f);
	void setOrder(const std::string & name, AssetMeneger * assets);

	void setPosition(int pos);

private:

	bool _chosable{ false };

private:

	// Inherited via GUIElement
	virtual void _init(AssetMeneger * assets) override;

	virtual void _initLogic(AssetMeneger * assets, const std::vector<std::function<void()>>& func) override;

};

}