#pragma once

#include <glm/glm.hpp>
#include <Components/Component.hh>
#include <Utils/GlmSerialization.hpp>
#include <cereal/types/string.hpp>
#include <Core/PrepareKey.hpp>

namespace Component
{
	struct CameraComponent : public ComponentBase<CameraComponent>
	{
		CameraComponent();
		virtual ~CameraComponent();
		CameraComponent(CameraComponent const &o);
		CameraComponent	&operator=(CameraComponent const &o);
		
		void init(AScene *scene);
		virtual void reset(AScene *scene);

		void setProjection(const glm::mat4 &);
		const glm::mat4 &getProjection() const;

		template <typename Archive> void save(Archive &ar) const;
		template <typename Archive> void load(Archive &ar);

	private:
		AScene *_scene = nullptr;
		glm::mat4 _projection;
		AGE::PrepareKey _key;
	};

	template <typename Archive>
	void CameraComponent::save(Archive &ar) const
	{
		ar(cereal::make_nvp("projection", _projection));
	}

	template <typename Archive>
	void CameraComponent::load(Archive &ar)
	{
		ar(_projection);
	}
}
