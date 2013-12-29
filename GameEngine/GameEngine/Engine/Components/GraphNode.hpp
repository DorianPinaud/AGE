#ifndef    __GRAPH_NODE_HPP__
# define   __GRAPH_NODE_HPP__

#include "Component.hh"
#include <Core/Engine.hh>
#include <Entities/Entity.hh>

namespace Component
{
	class GraphNode : public ComponentBase<GraphNode>
	{
	public:
		typedef std::list<Handle> t_EntityList;

		GraphNode(Engine &engine, Handle &entity)
			: ComponentBase<GraphNode>(engine, entity, "GraphNodeComponent")
		{
			}

		virtual ~GraphNode()
		{
		}

		void init()
		{
			_parent = Handle(std::numeric_limits<unsigned int>::max(), nullptr);

			// signal it's a root node
			auto key = PubSubKey("graphNodeSetAsRoot");
			_entity->broadCast(key, _entity);
		}

		virtual void reset()
		{
			_childs.clear();
			auto key = PubSubKey("graphNodeNotARoot");
			broadCast(key, _entity);
		}

		const Handle	    	&getParent() const
		{
			return _parent;
		}

		void 					removeSon(Handle &son, bool notify = true)
		{
			_childs.erase(son);
			if (notify && son->hasComponent<Component::GraphNode>())
			{
				son->getComponent<Component::GraphNode>()->removeParent(false);
			}
		}

		void 					setParent(Handle &father, bool notify = true)
		{
			if (_parent.get() && _parent->hasComponent<Component::GraphNode>())
			{
				_parent->getComponent<Component::GraphNode>()->removeSon(_entity, false);
			}

			if (notify && father->hasComponent<Component::GraphNode>())
				father->getComponent<Component::GraphNode>()->addSon(_entity, false);
			if (!father.get()) // if parent is null -> it's a root node
			{
				auto key = PubSubKey("graphNodeSetAsRoot");
				_entity->broadCast(key, _entity);
			}
			else if (!_parent.get()) // if it was a root node
			{
				auto key = PubSubKey("graphNodeNotARoot");
				_entity->broadCast(key, _entity);
			}
			_parent = father;
		}

		void 					addSon(Handle &son, bool notify = true)
		{
			_childs.insert(son);
			if (notify && son->hasComponent<Component::GraphNode>())
			{
				son->getComponent<Component::GraphNode>()->setParent(_entity, false);
			}
		}

		void                    removeParent(bool notify = true)
		{
			if (notify && _parent.get() && _parent->hasComponent<Component::GraphNode>())
			{
				_parent->getComponent<Component::GraphNode>()->removeSon(_entity);
			}
			auto key = PubSubKey("graphNodeSetAsRoot");
			_entity->broadCast(key, _entity);
			_parent = Handle(std::numeric_limits<unsigned int>::max(), nullptr);
		}

		std::set<Handle>::iterator getSonsBegin()
		{
			return std::begin(_childs);
		}
		
		std::set<Handle>::iterator getSonsEnd()
		{
			return std::end(_childs);
		}

	private:
		Handle _parent;
		std::set<Handle> _childs;
	};
}

#endif     //__GRAPH_NODE_HPP__