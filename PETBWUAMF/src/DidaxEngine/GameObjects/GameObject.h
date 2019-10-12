#pragma once
#include "../GUI/GUIElement.h"
#include "../Utility/UniqueID.h"
#include "../Utility/Logger.h"

namespace Didax 
{
	class Engine;


class GameObject
{
public:

	GameObject(Engine * engine);

	void init();

	GameObject(GameObject&&) = delete;

	GameObject& operator = (GameObject&&) = delete;

	virtual ~GameObject() = default;

	size_t getID()const;

	Engine * getParent();


protected:

	std::map<std::string, std::unique_ptr<GUIElement>> _representation;

	size_t _id;

	Engine * _engine;


protected:

	template <typename T>
	Canvas * addGUI(const std::string & name, AssetMeneger * assets);
};

template <typename T>
Canvas * GameObject::addGUI(const std::string & name, AssetMeneger * assets)
{
	try
	{
		_representation[name] = std::make_unique<T>();
		_representation[name].get()->init(assets->getAsset<GUIElementPrototype>(name), assets);
		return _representation[name].get()->getRoot();
	}
	catch(std::exception & e)
	{
		Logger::log(e.what());
		return nullptr;
	}
}

}