#ifndef   __COLLISION_HPP__
# define  __COLLISION_HPP__

#include <Components/Component.hh>

namespace Component
{
	struct Collision : public ComponentBase<Collision>
	{
		Collision()
			: ComponentBase<Collision>()
			, force(0)
		{
				
		}

		virtual ~Collision()
		{
		}

		void init()
		{
			force = 0;
		}

		virtual void reset()
		{
			collisions.clear();
		}

		void addCollision(const Entity &entity)
		{
			collisions.insert(entity);
		}

		std::set<Entity> &getCollisions()
		{
			return collisions;
		}

		void clear()
		{
			collisions.clear();
		}

		//////
		////
		// Serialization

		template <typename Archive>
		Base *unserialize(Archive &ar, Entity e)
		{
			auto res = new Collision();
			res->setEntity(e);
			ar(*res);
			return res;
		}

		template <typename Archive>
		void save(Archive &ar) const
		{
			std::set<std::size_t> entityIds;
			for (auto e : collisions)
			{
				entityIds.insert(_entity.get()->getScene()->registrarSerializedEntity(e.getId()));
			}
			ar(cereal::make_nvp("Collisions", entityIds));
		}

		template <typename Archive>
		void load(Archive &ar)
		{
			std::set<std::size_t> entityIds;
			ar(entityIds);
			for (auto e : entityIds)
				collisions.insert(Entity(e));
			for (auto it = std::begin(collisions); it != std::end(collisions); ++it)
			{ 
				Entity *e = const_cast<Entity *>(&(*it));
				_entity->getScene()->entityHandle(it->getId(), e);
			}
		}

		// !Serialization
		////
		//////
		float force;
		std::set<Entity> collisions;
	};
}

#endif    //__COLLISION_HPP__