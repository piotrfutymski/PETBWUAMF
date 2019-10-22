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
	void addToHand(AssetMeneger * assets, int pos, Canvas * parent);

	const OrderPrototype * getPrototype()const;
	

	//Gui

	void setDescriptable();
	void setUnClicable();
	void setCHoosable();


	static void setFunctions(const std::map<std::string, std::function<void(Order * u)>> & f);

private:

	static std::map<std::string, std::function<void(Order * u)>> _functions;

	OrderPrototype * _prototype;

	Location _location{ Location::InHand };

	int _owner{ 0 };
};

}