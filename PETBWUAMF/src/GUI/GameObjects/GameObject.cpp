#include "GameObject.h"


namespace Didax
{

Didax::GameObject::GameObject()
	:_id{ getUniqueID<GameObject>() }
{
}

size_t GameObject::getID() const
{
	return _id;
}

void GameObject::openGUI(Canvas * parent, AssetMeneger * assets)
{
	_representation->open(parent, assets);
}

void GameObject::closeGUI(Canvas * parent)
{
	_representation->close(parent);
}

void GameObject::setFunctions(const std::map<std::string, std::function<void(Unit*u)>>& f)
{
}




}