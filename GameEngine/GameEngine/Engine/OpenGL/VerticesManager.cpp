#include <OpenGL/VerticesManager.hh>
#include <OpenGL/Vertices.hh>
#include <OpenGL/VerticesPool.hh>

#define WARNING_NOT_FOUND(thing) \
	std::cerr << "Warning: cannot find " << thing << "." << std::endl; \

#define WARNING_KEY(in) \
	std::cerr << "Warning: the key send to " in << " is broken." << std::endl;

namespace gl
{
	VerticesManager::VerticesManager()
		: _indicesPool()
	{
		GLenum typeComponent = GL_UNSIGNED_INT;
		uint8_t sizeTypeComponent = sizeof(unsigned int);
		uint8_t nbrComponent = 1;
		_indicesPool.setData(1, &typeComponent, &sizeTypeComponent, &nbrComponent);
		_indicesPool.setIsIndicesPool(true);
	}

	VerticesManager::~VerticesManager()
	{

	}

	Key<VerticesPool> VerticesManager::addPool()
	{
		Key<VerticesPool> key;
		_pools[key] = VerticesPool();
		return (key);
	}

	Key<VerticesPool> VerticesManager::addPool(uint8_t nbrAttributes, GLenum *typeComponent, uint8_t *sizeTypeComponent, uint8_t *nbrComponent)
	{
		Key<VerticesPool> key;

		_pools[key] = VerticesPool(nbrAttributes, typeComponent, sizeTypeComponent, nbrComponent);
		return (key);
	}

	Key<VerticesPool> VerticesManager::getPool(size_t target) const
	{
		if (target >= _pools.size())
		{
			Key<VerticesPool> corruptKey;
			corruptKey.destroy();
			return (corruptKey);
		}
		auto &element = _pools.begin();
		for (size_t index = 0; index < target; ++index)
			++element;
		return (element->first);
	}

	size_t VerticesManager::nbrPool() const
	{
		return (_pools.size());
	}

	// the key will be set to empty
	VerticesManager &VerticesManager::rmPool(Key<VerticesPool> &key)
	{
		if (!key)
			return (*this);
		_pools.erase(key);
		key.destroy();
		return (*this);
	}

	Key<Vertices> VerticesManager::getVertices(size_t target) const
	{
		if (target >= _vertices.size())
		{
			Key<Vertices> corruptKey;
			corruptKey.destroy();
			return (corruptKey);
		}
		auto &element = _vertices.begin();
		for (size_t index = 0; index < target; ++index)
			++element;
		return (element->first);
	}

	size_t VerticesManager::getNbrVertices() const
	{
		return (_vertices.size());
	}

	Key<Vertices> VerticesManager::addVertices(size_t nbrVertices, uint8_t nbrBuffers, size_t *sizeBuffers, void **buffers)
	{
		Key<Vertices> key;

		_vertices[key] = Vertices(nbrVertices, nbrBuffers, sizeBuffers, buffers);
		return (key);
	}

	VerticesManager &VerticesManager::rmVertices(Key<Vertices> &key)
	{
		if (!key)
		{
			WARNING_KEY("rmVertices")
			return (*this);
		}
		_vertices.erase(key);
		key.destroy();
		return (*this);
	}

	VerticesManager &VerticesManager::attachVerticesToPool(Key<Vertices> const &keyvertices, Key<VerticesPool> const &keypool)
	{
		if (!keyvertices || !keypool)
		{
			WARNING_KEY("attachVerticesToPool")
			return (*this);
		}
		auto &vertices = _vertices.find(keyvertices);
		if (vertices == _vertices.end())
			return (*this);
		auto &pool = _pools.find(keypool);
		if (pool == _pools.end())
			return (*this);
		if (vertices->second._pool)
			vertices->second._pool->rmVertices(vertices->second);
		vertices->second._pool = &pool->second;
		pool->second.addVertices(vertices->second);
		return (*this);
	}

	VerticesManager &VerticesManager::dettachVerticesToPool(Key<Vertices> const &keyvertices)
	{
		if (!keyvertices)
		{
			WARNING_KEY("dettachVerticesToPool")
			return (*this);
		}
		auto &vertices = _vertices.find(keyvertices);
		if (vertices == _vertices.end())
			return (*this);
		if (vertices->second._pool)
		{
			vertices->second._pool->rmVertices(vertices->second);
			vertices->second._pool = NULL;
		}
		return (*this);
	}

	VerticesManager &VerticesManager::dettachVerticesToIndicesPool(Key<Vertices> const &keyvertices)
	{
		if (!keyvertices)
		{
			WARNING_KEY("dettachVerticesToPoolIndicesPool")
				return (*this);
		}
		auto &vertices = _vertices.find(keyvertices);
		if (vertices == _vertices.end())
			return (*this);
		if (vertices->second._pool)
		{
			vertices->second._pool->rmVertices(vertices->second);
			vertices->second._pool = NULL;
		}
		return (*this);
	}

	VerticesManager &VerticesManager::attachVerticesToIndicesPool(Key<Vertices> const &keyvertices)
	{
		if (!keyvertices)
		{
			WARNING_KEY("attachVerticesToIndicesPool")
			return (*this);
		}
		auto &vertices = _vertices.find(keyvertices);
		if (vertices == _vertices.end())
			return (*this);
		if (vertices->second._pool)
			vertices->second._pool->rmVertices(vertices->second);
		vertices->second._pool = &_indicesPool;
		_indicesPool.addVertices(vertices->second);
		return (*this);
	}

	VerticesManager &VerticesManager::drawByIndices(Key<Vertices> const &keyindices, Key<VerticesPool> const &keypool)
	{
		if (!keyindices || !keypool)
		{
			WARNING_KEY("drawByIndices")
			return (*this);
		}
		auto &vertices = _vertices.find(keyindices);
		if (vertices == _vertices.end())
			return (*this);
		auto &pool = _pools.find(keypool);
		if (pool == _pools.end())
			return (*this);
		_indicesPool.syncronisation();
		pool->second.syncronisation();
		pool->second.attributesSyncronisation(_indicesPool);
		
		//???
		return (*this);
	}

	VerticesManager &VerticesManager::draw(Key<Vertices> const &keyvertices)
	{
		if (!keyvertices)
		{
			WARNING_KEY("draw")
			return (*this);
		}
		return (*this);
	}

}