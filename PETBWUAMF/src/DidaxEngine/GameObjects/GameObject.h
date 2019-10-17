#pragma once
#include "../GUI/GUIElement.h"
#include "../Utility/UniqueID.h"
#include "../Utility/Logger.h"

namespace Didax 
{
class GameObject
{
public:

	GameObject();

	GameObject(GameObject&&) = delete;

	GameObject& operator = (GameObject&&) = delete;

	virtual ~GameObject() = default;

	size_t getID()const;

	template <typename T>
	void createGUI(const std::string & name, AssetMeneger * assets);

	template <typename T>
	T* getGUI();

	void openGUI(Canvas * parent, AssetMeneger * assets, const std::vector<std::function<void()>> & func);
	void closeGUI(Canvas * parent);


protected:

	std::unique_ptr<GUIElement> _representation;

	size_t _id;


protected:

};

template <typename T>
void GameObject::createGUI(const std::string & name, AssetMeneger * assets)
{
	try
	{
		auto a = std::make_unique<T>(assets->getAsset<GUIElementPrototype>(name));
		_representation = std::move(a);
	}
	catch(std::exception & e)
	{
		Logger::log(e.what());
	}
}

template<typename T>
inline T * GameObject::getGUI()
{
	T* res = nullptr;
	try
	{
		res = static_cast<T*>(_representation.get());
	}
	catch (std::exception & e)
	{
		Logger::log(e.what());
	}
	return res;
}

}