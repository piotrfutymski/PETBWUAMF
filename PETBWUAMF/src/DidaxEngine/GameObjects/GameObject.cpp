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

void GameObject::openGUI(Canvas * parent, AssetMeneger * assets, const std::vector<std::function<void()>>& func)
{
	_representation->open(parent, assets, func);
}

void GameObject::closeGUI(Canvas * parent)
{
	_representation->close(parent);
}




}