#pragma once

#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Entities/EntityTypedef.hpp>
#include <Core/PrepareKey.hpp>
#include <cstring>
#include <array>

class AScene;

namespace AGE
{
	struct Link
	{
		const glm::vec3 &getPosition() const { return _position; }
		const glm::vec3 &getScale() const { return _scale; }
		const glm::quat &getOrientation() const { return _orientation; }

		// Used by modules like physic, do not use it to set object position, use setPosition instead
		void internalSetPosition(const glm::vec3 &v);
		// Used by modules like physic, do not use it to set object scale, use setScale instead
		void internalSetScale(const glm::vec3 &v);
		// Used by modules like physic, do not use it to set object orientation, use setOrientation instead
		void internalSetOrientation(const glm::quat &v);

		inline bool userModified()
		{
			auto ret = _userModification; _userModification = false; return ret;
		}

		void setPosition(const glm::vec3 &v);
		void setScale(const glm::vec3 &v);
		void setOrientation(const glm::quat &v);

		void registerOctreeObject(const PrepareKey &key);
		void unregisterOctreeObject(const PrepareKey &key);
	public:
		const glm::mat4 &getTransform();
	private:
		bool _userModification = false;
		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _orientation;
		glm::mat4 _trans;
		bool _computeTrans;
		std::array<PrepareKey, MAX_CPT_NUMBER> _octreeObjects;
	public:
		void *_octree;
	public:
		Link();
		void reset();

		friend class AScene;
	};
}