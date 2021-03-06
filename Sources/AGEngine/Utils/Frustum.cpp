#pragma once

#include "Frustum.hh"
#include <glm/glm.hpp>

namespace AGE
{

	void	Frustum::buildPlanes()
	{
		_planes[PLANE_NEAR].setCoefficients(
			_viewProj[0][2] + _viewProj[0][3],
			_viewProj[1][2] + _viewProj[1][3],
			_viewProj[2][2] + _viewProj[2][3],
			_viewProj[3][2] + _viewProj[3][3]);
		_planes[PLANE_FAR].setCoefficients(
			-_viewProj[0][2] + _viewProj[0][3],
			-_viewProj[1][2] + _viewProj[1][3],
			-_viewProj[2][2] + _viewProj[2][3],
			-_viewProj[3][2] + _viewProj[3][3]);
		_planes[PLANE_BOTTOM].setCoefficients(
			_viewProj[0][1] + _viewProj[0][3],
			_viewProj[1][1] + _viewProj[1][3],
			_viewProj[2][1] + _viewProj[2][3],
			_viewProj[3][1] + _viewProj[3][3]);
		_planes[PLANE_TOP].setCoefficients(
			-_viewProj[0][1] + _viewProj[0][3],
			-_viewProj[1][1] + _viewProj[1][3],
			-_viewProj[2][1] + _viewProj[2][3],
			-_viewProj[3][1] + _viewProj[3][3]);
		_planes[PLANE_LEFT].setCoefficients(
			_viewProj[0][0] + _viewProj[0][3],
			_viewProj[1][0] + _viewProj[1][3],
			_viewProj[2][0] + _viewProj[2][3],
			_viewProj[3][0] + _viewProj[3][3]);
		_planes[PLANE_RIGHT].setCoefficients(
			-_viewProj[0][0] + _viewProj[0][3],
			-_viewProj[1][0] + _viewProj[1][3],
			-_viewProj[2][0] + _viewProj[2][3],
			-_viewProj[3][0] + _viewProj[3][3]);
	}

	void Frustum::setMatrix(const glm::mat4 &viewProj)
	{
		if (_viewProj != viewProj)
		{
			_viewProj = viewProj;
			buildPlanes();
		}
	}

	bool Frustum::checkCollision(AABoundingBox const &aabb) const
	{
		for (int i = 0; i < PLANE_END; i++)
		{
			if (_planes[i].getPointDistance(aabb.getPositivePoint(_planes[i].getNormal())) < 0)
				return (false);
		}
		return (true);
	}

	bool Frustum::checkCollision(Sphere const &sphere) const
	{
		assert(!"Not implemented");
		return (false);
	}

	bool Frustum::checkCollision(glm::vec4 const &sphere) const
	{


		for (int i = 0; i < PLANE_END; i++)
		{
			float dist = _planes[i].getPointDistance(glm::vec3(sphere));

			if (dist + sphere.w < 0)
				return (false);
		}
		return (true);
	}

	bool Frustum::checkCollision(Frustum const &frustum) const
	{
		assert(!"Not implemented");
		return (false);
	}


}