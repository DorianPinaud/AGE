#pragma once

#include <Physics/BulletCollisionManager.hpp>
#include <Utils/MultiTypeObjectPool.hpp>

namespace AGE
{
	class BulletDynamicManager : public BulletCollisionManager
	{
	private:
		btSequentialImpulseConstraintSolver *_constraintSolver;
	public:
		BulletDynamicManager()
			: BulletCollisionManager()
			, _constraintSolver(nullptr)
		{}

		virtual ~BulletDynamicManager()
		{
			uninit();
		}

		bool init()
		{
			if (!BulletCollisionManager::init(false))
				return false;

			_constraintSolver = new btSequentialImpulseConstraintSolver();
			_world = std::make_shared<btDiscreteDynamicsWorld>(_dispatcher, _broadphase, _constraintSolver, _collisionConfiguration);
			std::dynamic_pointer_cast<btDiscreteDynamicsWorld>(_world)->setGravity(btVector3(0, -10, 0));
			_world->getDispatchInfo().m_allowedCcdPenetration = 0.05f;
			return true;
		}

		virtual void uninit()
		{
			if (_world.get())
			{
				_world.reset();
			}
			if (_constraintSolver)
			{
				delete _constraintSolver;
				_constraintSolver = nullptr;
			}
		}
		inline btDynamicsWorld * getWorld() const { return std::dynamic_pointer_cast<btDynamicsWorld>(_world).get(); }

		inline AGE::MultiTypeObjectPool<16, 124> &getObjectPool() { return _objectPool; }
	private:
		AGE::MultiTypeObjectPool<16, 124> _objectPool;
	};
}