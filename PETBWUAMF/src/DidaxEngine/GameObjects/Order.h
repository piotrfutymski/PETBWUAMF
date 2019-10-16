#pragma once
#include "GameObject.h"
#include "../GUI/OrderRepresentation.h"

namespace Didax
{


class Order : public GameObject
{
public:
	
	enum class Location
	{
		InDeck, InHand, Used
	};

	Order(Engine * eng, OrderPrototype * prototype);
	~Order();

	bool isInHand()const;

	Canvas * show(AssetMeneger * assets, int pos);
	
	void setAsChoosable();

private:
	OrderPrototype * _prototype;

	Location _location{ Location::InHand };

	int _owner{ 0 };
};

}