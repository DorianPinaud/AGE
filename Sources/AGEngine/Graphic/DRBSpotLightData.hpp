#pragma once

#include <glm/fwd.hpp>

#include "DRBData.hpp"

#include "Render/Properties/AutoProperty.hpp"

namespace AGE
{
	class Vec3;
	class Mat4;
	class Texture2D;

	struct DRBSpotLightData : public DRBData
	{
		DRBSpotLightData();
		virtual ~DRBSpotLightData();

		// Call that at init, it will add the property in Properties list
		// and keep a pointer on it to update it when spotlight transformation is modified
		void registerDirectionProperty(std::shared_ptr<AutoProperty<glm::vec3, Vec3>> directionProperty);

		// Call that at init, it will add the property in Properties list
		// and keep a pointer on it to update it when spotlight transformation is modified
		void registerPositionProperty(std::shared_ptr<AutoProperty<glm::vec3, Vec3>> positionProperty);

		// Call that at init, it will add the property in Properties list
		// and keep a pointer on it 
		void registerShadowMatrixProperty(std::shared_ptr<AutoProperty<glm::mat4, Mat4>> shadowMatrixProperty);

		void computePositionAndDirection(const glm::mat4 &transformation);

		inline std::shared_ptr<AutoProperty<glm::mat4, Mat4>> getShadowMatrixProperty() { return _shadowMatrixProperty; }

		// used by graphics pipeline, used don't have to set anything in it
		std::shared_ptr<Texture2D> shadowMap = nullptr;
	private:
		std::shared_ptr<AutoProperty<glm::vec3, Vec3>> _directionProperty = nullptr;
		std::shared_ptr<AutoProperty<glm::vec3, Vec3>> _positionProperty = nullptr;
		std::shared_ptr<AutoProperty<glm::mat4, Mat4>> _shadowMatrixProperty = nullptr;
	};
}