#include "GameObject.h"


namespace Didax
{

Didax::GameObject::GameObject(Engine * engine)
	:_id{ getUniqueID<GameObject>() }, _engine{ engine}
{
}

size_t GameObject::getID() const
{
	return _id;
}




}