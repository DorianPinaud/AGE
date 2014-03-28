
#include "EntityData.hh"
#include "Core/Engine.hh"
#include "Components/Component.hh"
#include "Entity.hh"
#include <limits>
#include <Core/AScene.hh>

EntityData::EntityData(std::weak_ptr<AScene> scene) :
    _scene(scene),
	_flags(0),
	_localTranslation(0),
	_localRotation(0),
	_localScale(0),
	_globalTranslation(0),
	_globalRotation(0),
	_globalScale(0),
	_parent(Entity(std::numeric_limits<unsigned int>::max(), nullptr))
{
	removeFlags(ACTIVE);
}

EntityData::~EntityData()
{
	_components.clear();
}

EntityData::EntityData(EntityData &&o)
{
	_handle = std::move(o._handle);
	_scene = std::move(o._scene);
	_flags = std::move(o._flags);
	_localTransform = std::move(o._localTransform);
	_globalTransform = std::move(o._globalTransform);
	_localRotation = std::move(o._localRotation);
	_localScale = std::move(o._localScale);
	_localTranslation = std::move(o._localTranslation);
	_globalRotation = std::move(o._globalRotation);
	_globalScale = std::move(o._globalScale);
	_globalTranslation = std::move(o._globalTranslation);
	_components = std::move(o._components);
	_code = std::move(o._code);
	_childs = std::move(o._childs);
	_parent = std::move(o._parent);
}

Entity &EntityData::getHandle()
{
	return _handle;
}

std::shared_ptr<AScene> EntityData::getScene() const
{
	return _scene.lock();
}

void EntityData::setHandle(Entity &handle)
{
	_handle = handle;
}

glm::mat4 const  		&EntityData::getLocalTransform()
{
	return (_localTransform);
}

void   			        EntityData::setLocalTransform(const glm::mat4 &t, bool forceMovedFlag)
{
	_flags |= HAS_MOVED;
	_localTransform = t;
	computeTransformAndUpdateGraphnode();
	if (forceMovedFlag)
		_flags |= HAS_MOVED;
}

glm::mat4 const			&EntityData::getGlobalTransform() const
{
	return (_globalTransform);
}

void 					EntityData::computeGlobalTransform(glm::mat4 const &fatherTransform)
{
	_globalTransform = fatherTransform * _localTransform;
	_flags ^= HAS_MOVED;
}

void 					EntityData::computeGlobalTransform(const Entity &parent)
{
	if (!parent.get())
		return;
	_globalTransform = parent.get()->getGlobalTransform() * _localTransform;
	_flags ^= HAS_MOVED;
}

void                    EntityData::translate(const glm::vec3 &v)
{
	_localTranslation += v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

void                    EntityData::setTranslation(const glm::vec3 &v)
{
	_localTranslation = v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

glm::vec3 const         &EntityData::getTranslation() const
{
	return _localTranslation;
}

void                    EntityData::rotate(const glm::vec3 &v)
{
	_localRotation += v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

void                    EntityData::setRotation(const glm::vec3 &v)
{
	_localRotation = v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

glm::vec3 const         &EntityData::getRotation() const
{
	return _localRotation;
}

void                    EntityData::scale(const glm::vec3 &v)
{
	_localScale += v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

void                    EntityData::setScale(const glm::vec3 &v)
{
	_localScale = v;
	_flags |= HAS_MOVED;
	computeTransformAndUpdateGraphnode();
}

glm::vec3 const         &EntityData::getScale() const
{
	return _localScale;
}

void                    EntityData::computeTransformAndUpdateGraphnode()
{
	if (!_parent.get())
	{
		computeGlobalTransform(glm::mat4(1));
	}
	else
	{
		computeGlobalTransform(_parent);
	}
	for (auto e : _childs)
	{
		e->computeTransformAndUpdateGraphnode();
	}
}

size_t 					EntityData::getFlags() const
{
	return (_flags);
}

void 					EntityData::setFlags(size_t flags)
{
	_flags = flags;
}

void 					EntityData::addFlags(size_t flags)
{
	_flags |= flags;
}

void 					EntityData::removeFlags(size_t flags)
{
	flags &= _flags;
	_flags ^= flags;
}

Barcode                 &EntityData::getCode()
{
	return _code;
}

void                    EntityData::addTag(unsigned short tag)
{
	assert(tag < MAX_TAG_NUMBER && "Tags limit is 31");
	_code.add(tag);
	_scene.lock()->informFilters(true, tag, std::move(_handle));
}

void                    EntityData::removeTag(unsigned short tag)
{
	assert(tag < MAX_TAG_NUMBER && "Tags limit is 31");
	_code.remove(tag);
	_scene.lock()->informFilters(false, tag, std::move(_handle));
}
bool                    EntityData::isTagged(unsigned short tag) const
{
	assert(tag < MAX_TAG_NUMBER && "Tags limit is 31");
	return _code.isSet(tag);
}

bool                    EntityData::isTagged(Barcode &code)
{
	// TODO get the size of the code and assert if > 31
	return _code.match(code);
}

void EntityData::reset()
{
	_flags = 0;
	_localTranslation = glm::vec3(0);
	_localRotation = glm::vec3(0);
	_localScale = glm::vec3(0);
	_globalTranslation = glm::vec3(0);
	_globalRotation = glm::vec3(0);
	_globalScale = glm::vec3(0);
	_globalTransform = glm::mat4(1);
	_localTransform = glm::mat4(1);
	_code.reset();
	auto scene = _scene.lock();
	for (std::size_t i = 0; i < MAX_TAG_NUMBER; ++i)
	{
		if (scene)
			scene->informFilters(false, static_cast<unsigned short>(i), std::move(_handle));
	}
	for (std::size_t i = 0; i < _components.size(); ++i)
	{
		std::size_t id = i + MAX_TAG_NUMBER;
		if (_components[i].get())
		{
			if (scene)
				scene->informFilters(false, static_cast<unsigned short>(id), std::move(_handle));
			_components[i]->reset();
		}
		_components[i].reset();
	}
	removeParent();
	for (auto e : _childs)
		e->removeParent(false);
	_childs.clear();
}

////////////////
//
// Graphnode

const Entity	    	&EntityData::getParent() const
{
	return _parent;
}

void 					EntityData::removeChild(Entity &child, bool notify)
{
	_childs.erase(child);
	if (notify)
	{
		child->removeParent(false);
	}
}

void 					EntityData::setParent(Entity &parent, bool notify)
{
	if (_parent.get())
	{
		_parent->removeChild(_handle, false);
	}
	if (notify)
		parent->addChild(_handle, false);
	computeTransformAndUpdateGraphnode();
	_parent = parent;
}

void 					EntityData::addChild(Entity &child, bool notify)
{
	_childs.insert(child);
	if (notify)
	{
		child->setParent(_handle, false);
	}
}

void                    EntityData::removeParent(bool notify)
{
	if (notify && _parent.get())
	{
		_parent->removeChild(_handle);
	}
	_parent = Entity(std::numeric_limits<unsigned int>::max(), nullptr);
	computeTransformAndUpdateGraphnode();
}

std::set<Entity>::iterator EntityData::getChildsBegin()
{
	return std::begin(_childs);
}
		
std::set<Entity>::iterator EntityData::getChildsEnd()
{
	return std::end(_childs);
}

