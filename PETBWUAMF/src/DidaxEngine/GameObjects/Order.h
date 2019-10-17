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

	Order(OrderPrototype * prototype, AssetMeneger * assets);
	~Order();

	bool isInHand()const;

	void showInHand(AssetMeneger * assets, int pos, Canvas * parent, const std::function<void(Order *)> & hi, const std::function<void(Order *)> & ho);
	
	void setAsChoosable(const std::function<void(Order *)> & f);

	const OrderPrototype * getPrototype()const;

private:
	OrderPrototype * _prototype;

	Location _location{ Location::InHand };

	int _owner{ 0 };
};

}