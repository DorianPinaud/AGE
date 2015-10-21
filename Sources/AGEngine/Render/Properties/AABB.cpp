#include <Render/Properties/AABB.hpp>
#include <Render/ProgramResources/Types/Uniform/Vec3.hh>
#include <mutex>

namespace AGE
{

	AABB::AABB(glm::vec3 const &aabb) :
		AProperty(std::string("AABB")),
		_aabb(aabb)
	{

	}

	AABB::AABB(AABB &&move) :
		AProperty(std::move(move)),
		_aabb(move._aabb)
	{

	}

	AABB &AABB::operator=(glm::vec3 const &other)
	{
		if (_aabb != other) {
			_aabb = other;
		}
		return (*this);
	}

	void AABB::update(Vec3 *res, AABB *aabb)
	{
		*res = aabb->_aabb;
	}

	void AABB::instanciedUpdate(Vec3 *, AABB *)
	{
		assert(false && "implement me");
	}

	glm::vec3 const & AABB::get()
	{
		return (_aabb);
	}

	AABB & AABB::set(glm::vec3 const &mat)
	{
		_aabb = mat;
		return (*this);
	}
}
