#pragma once
#include "../Assets/AssetMeneger.h"
#include "../Utility/UniqueID.h"

class Game;


template <typename Prototype>
class GameObject
{
public:

	GameObject(const std::string & name) :_id{ getUniqueID<Prototype>() }
	{
		_prototype = Didax::AssetMeneger::getAsset<Prototype>(name);
	};

	size_t getID()const
	{
		return _id;
	};

	const Prototype * getPrototype()const
	{
		return _prototype;
	};

	Game * getGame()
	{
		return _game;
	}

	//

	static void setParent(Game * g)
	{
		_game = g;
	};

private:

static Game * _game;
const Prototype * _prototype;

size_t _id;

};

template <typename T>
Game* GameObject<T>::_game = nullptr;