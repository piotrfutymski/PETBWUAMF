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

	GameObject(GameObject&&) = delete;

	GameObject& operator = (GameObject&&) = delete;

	virtual ~GameObject() = default;

	size_t getID()const;


protected:

	std::map<std::string, std::unique_ptr<GUIElement>> _representations;

	size_t _id;

	Engine * _engine;


protected:

	template <typename T>
	Canvas * openGUI(const std::string & name, AssetMeneger * assets);

	template <typename T>
	T* getGUI(const std::string & name);
};

template <typename T>
Canvas * GameObject::openGUI(const std::string & name, AssetMeneger * assets)
{
	try
	{
		_representations.insert(std::pair(name, std::make_unique<T>()));
		_representations[name].get()->open(assets->getAsset<GUIElementPrototype>(name), assets, _engine);
		return _representations[name].get()->getRoot();
	}
	catch(std::exception & e)
	{
		Logger::log(e.what());
		return nullptr;
	}
}

template<typename T>
inline T * GameObject::getGUI(const std::string & name)
{
	T* res = nullptr;
	try
	{
		res = static_cast<T*>(_representations[name].get());
	}
	catch (std::exception & e)
	{
		Logger::log(e.what());
	}
	return res;
}

}