#pragma once
#include "GUIElement.h"

namespace Didax
{
class Engine;

class Hourglass :public GUIElement
{
public:

	Hourglass();
	~Hourglass();

	void setOnStateChanged(const std::function<void()> & func);

	void onStateChanged();

	virtual void init(GUIElementPrototype * prototype, AssetMeneger * assets) override;

private:

	std::function<void()> _onStateChanged;


private:

	// Inherited via GUIElement


	void initLogic();

};

}

