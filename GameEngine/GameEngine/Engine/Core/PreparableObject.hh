#pragma once

#include <Geometry/Mesh.hpp>
#include <Geometry/Material.hpp>
#include <Utils/Containers/Vector.hpp>
#include <Core/PrepareKey.hpp>
#include <Utils/AABoundingBox.hh>

namespace AGE
{

	struct PreparableObject
	{
		bool hasMoved;
		bool active;
		PrepareKey key;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 scale;
		glm::quat orientation;
		PreparableObject();
		virtual ~PreparableObject();
	};

}