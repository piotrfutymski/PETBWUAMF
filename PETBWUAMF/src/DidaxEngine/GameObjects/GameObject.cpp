#include "GameObject.h"


namespace Didax
{

Didax::GameObject::GameObject(Engine * engine)
	:_id{ getUniqueID<GameObject>() }, _engine{ engine}
{
}

void GameObject::init()
{

}


size_t GameObject::getID() const
{
	return _id;
}

Engine * GameObject::getParent()
{
	return _engine;
}



}