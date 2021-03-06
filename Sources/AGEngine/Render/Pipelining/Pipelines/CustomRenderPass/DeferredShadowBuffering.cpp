#include <Render/Pipelining/Pipelines/CustomRenderPass/DeferredShadowBuffering.hh>

#include <memory>

#include <Render/Textures/Texture2D.hh>
#include <Render/OpenGLTask/OpenGLState.hh>
#include <Render/GeometryManagement/Painting/Painter.hh>
#include <Render/ProgramResources/Types/Uniform/Mat4.hh>
#include <Render/ProgramResources/Types/Uniform/Vec1.hh>
#include <Core/ConfigurationManager.hpp>
#include <Core/Engine.hh>
#include <Configuration.hpp>
#include <Threads/RenderThread.hpp>
#include <Threads/ThreadManager.hpp>
#include <Render/OcclusionTools/DepthMapHandle.hpp>
#include <Render/OcclusionTools/DepthMap.hpp>
#include <Render/Pipelining/Pipelines/PipelineTools.hh>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphic/DRBCameraDrawableList.hpp"
#include "Graphic/DRBMeshData.hpp"
#include "Graphic/DRBSkinnedMesh.hpp"

#include "Render/Textures/TextureBuffer.hh"
#include "Render/ProgramResources/Types/Uniform/Sampler/SamplerBuffer.hh"

#include <Render\Pipelining\Pipelines\CustomRenderPass\ShadowMapCollection.hpp>

#include <Render/Pipelining/Pipelines/IRenderingPipeline.hh>
#include <Render/Pipelining/RenderInfos/SpotlightRenderInfos.hpp>


#define DEFERRED_SHADING_SHADOW_BUFFERING_VERTEX "deferred_shading/deferred_shading_get_shadow_buffer.vp"
#define DEFERRED_SHADING_SHADOW_BUFFERING_VERTEX_SKINNED "deferred_shading/deferred_shading_get_shadow_buffer_skinned.vp"
#define DEFERRED_SHADING_SHADOW_BUFFERING_FRAG "deferred_shading/deferred_shading_get_shadow_buffer.fp"

namespace AGE
{
	enum Programs
	{
		PROGRAM_BUFFERING = 0,
		PROGRAM_BUFFERING_SKINNED = 1,
		PROGRAM_NBR
	};

	DeferredShadowBuffering::DeferredShadowBuffering(glm::uvec2 const &screenSize, std::shared_ptr<PaintingManager> painterManager, IRenderingPipeline *pipeline) :
		FrameBufferRender(screenSize.x, screenSize.y, painterManager)
	{
		_pipeline = pipeline;

		auto confManager = GetEngine()->getInstance<ConfigurationManager>();
		auto shaderPath = confManager->getConfiguration<std::string>("ShadersPath");
		_programs.resize(PROGRAM_NBR);

		{
			// you have to set shader directory in configuration path
			AGE_ASSERT(shaderPath != nullptr);
			auto vertexShaderPath = shaderPath->getValue() + DEFERRED_SHADING_SHADOW_BUFFERING_VERTEX;
			auto fragmentShaderPath = shaderPath->getValue() + DEFERRED_SHADING_SHADOW_BUFFERING_FRAG;
			_programs[PROGRAM_BUFFERING] = std::make_shared<Program>(Program(StringID("program_shadow_buffering", 0xd24fab7f2d0c323d),
			{
				std::make_shared<UnitProg>(vertexShaderPath, GL_VERTEX_SHADER),
				std::make_shared<UnitProg>(fragmentShaderPath, GL_FRAGMENT_SHADER)
			}));
		}
		{
			// you have to set shader directory in configuration path
			AGE_ASSERT(shaderPath != nullptr);
			auto vertexShaderPath = shaderPath->getValue() + DEFERRED_SHADING_SHADOW_BUFFERING_VERTEX_SKINNED;
			auto fragmentShaderPath = shaderPath->getValue() + DEFERRED_SHADING_SHADOW_BUFFERING_FRAG;
			_programs[PROGRAM_BUFFERING_SKINNED] = std::make_shared<Program>(Program(StringID("program_shadow_buffering", 0xd24fab7f2d0c323d),
			{
				std::make_shared<UnitProg>(vertexShaderPath, GL_VERTEX_SHADER),
				std::make_shared<UnitProg>(fragmentShaderPath, GL_FRAGMENT_SHADER)
			}));
		}
	}

	void DeferredShadowBuffering::init()
	{
		// We dont want to take the skinned or transparent meshes
		_forbidden[AGE_SKINNED] = true;
		_forbidden[AGE_SEMI_TRANSPARENT] = true;

		_positionBuffer = createRenderPassOutput<TextureBuffer>(_maxInstanciedShadowCaster, GL_RGBA32F, _sizeofMatrix, GL_DYNAMIC_DRAW);

		_programs[PROGRAM_BUFFERING]->get_resource<SamplerBuffer>(StringID("model_matrix_tbo", 0x6532aea46fc01c3a))->addInstanciedAlias("model_matrix");
	}


	void DeferredShadowBuffering::renderPass(const DRBCameraDrawableList &/*infos*/)
	{
		//@PROUT
		SCOPE_profile_gpu_i("DeferredShadowBuffering render pass");
		SCOPE_profile_cpu_i("RenderTimer", "DeferredShadowBuffering render pass");

		OpenGLState::glEnable(GL_CULL_FACE);
		OpenGLState::glCullFace(GL_FRONT);
		OpenGLState::glDepthMask(GL_TRUE);
		OpenGLState::glDepthFunc(GL_LEQUAL);
		OpenGLState::glDisable(GL_BLEND);
		OpenGLState::glDisable(GL_STENCIL_TEST);
		OpenGLState::glEnable(GL_DEPTH_TEST);
		OpenGLState::glDepthMask(GL_TRUE);
		OpenGLState::glDepthFunc(GL_LESS);

		_programs[PROGRAM_BUFFERING]->use();

		auto passInfos = _pipeline->getSpotlightRenderInfos();

		// handle the number of sample
		auto w = _frame_buffer.width(); auto h = _frame_buffer.height();
		glViewport(0, 0, w, h);

		int i = 0;
		// we render instancied occluders
		for (auto &spot : passInfos->getSpotlights())
		{
			SCOPE_profile_gpu_i("Spotlight regular pass");
			SCOPE_profile_cpu_i("RenderTimer", "Spotlight regular pass");

			auto spotLightPtr = spot.meshs;

			auto depth = ShadowMapCollection::getDepthBuffer(i++, w, h);
			_frame_buffer.attachment(*depth.get(), GL_DEPTH_STENCIL_ATTACHMENT);
			glClear(GL_DEPTH_BUFFER_BIT);

			_programs[PROGRAM_BUFFERING]->get_resource<Mat4>(StringID("light_matrix", 0x9c8229a430a9c8a9)).set(spotLightPtr->getCommandOutput()._spotLightMatrix);
			_programs[PROGRAM_BUFFERING]->get_resource<SamplerBuffer>(StringID("model_matrix_tbo", 0x6532aea46fc01c3a)).set(_positionBuffer);
			auto matrixOffset = _programs[PROGRAM_BUFFERING]->get_resource<Vec1>(StringID("matrixOffset", 0xb870d9a9a2c195f7));

			_positionBuffer->resetOffset();


			std::shared_ptr<Painter> painter = nullptr;
			Key<Vertices> verticesKey;

			// draw for the spot light selected
			auto &generator = spotLightPtr->getCommandOutput();
			auto &occluders = generator._commands;
			std::size_t occluderCounter = 0;

			_positionBuffer->set((void*)(generator._datas.data()), generator._datas.size() > _maxInstanciedShadowCaster ? _maxInstanciedShadowCaster : generator._datas.size());

			while (occluderCounter < occluders.size())
			{
				auto &current = occluders[occluderCounter];

				Key<Painter> painterKey;
				UnConcatenateKey(current.verticeKey, painterKey, verticesKey);

				if (painterKey.isValid())
				{
					painter = _painterManager->get_painter(painterKey);
					painter->instanciedDrawBegin(_programs[PROGRAM_BUFFERING]);
					matrixOffset.set(float(current.from));
					painter->instanciedDraw(GL_TRIANGLES, _programs[PROGRAM_BUFFERING], verticesKey, current.size);
					painter->instanciedDrawEnd();
				}
				++occluderCounter;
			}
		}

		i = 0;
		// we render instancied occluders
		for (auto &spot : passInfos->getSpotlights())
		{
			SCOPE_profile_gpu_i("Spotlight skinned pass");
			SCOPE_profile_cpu_i("RenderTimer", "Spotlight skinned pass");

			auto spotLightPtr = spot.skinnedMeshs;

			if (spotLightPtr->getCommandOutput()._commands.size() == 0)
			{
				continue;
			}

			auto depth = ShadowMapCollection::getDepthBuffer(i++, w, h);

			_frame_buffer.attachment(*depth.get(), GL_DEPTH_STENCIL_ATTACHMENT);
			_programs[PROGRAM_BUFFERING_SKINNED]->get_resource<Mat4>(StringID("light_matrix", 0x9c8229a430a9c8a9)).set(spotLightPtr->getCommandOutput()._spotLightMatrix);
			_programs[PROGRAM_BUFFERING_SKINNED]->get_resource<SamplerBuffer>(StringID("model_matrix_tbo", 0x6532aea46fc01c3a)).set(_positionBuffer);
			_programs[PROGRAM_BUFFERING_SKINNED]->get_resource<SamplerBuffer>(StringID("bones_matrix_tbo", 0x3a7f8c7debc73024)).set(GetRenderThread()->getBonesTexture());
			auto matrixOffset = _programs[PROGRAM_BUFFERING_SKINNED]->get_resource<Vec1>(StringID("matrixOffset", 0xb870d9a9a2c195f7));
			auto bonesOffset = _programs[PROGRAM_BUFFERING_SKINNED]->get_resource<Vec1>(StringID("bonesOffset", 0xc8c5f289dcfef0cf));

			_positionBuffer->resetOffset();


			std::shared_ptr<Painter> painter = nullptr;
			Key<Vertices> verticesKey;

			// draw for the spot light selected
			auto &generator = spotLightPtr->getCommandOutput();
			auto &occluders = generator._commands;
			std::size_t occluderCounter = 0;

			_positionBuffer->set((void*)(generator._datas.data()), generator._datas.size() > _maxInstanciedShadowCaster ? _maxInstanciedShadowCaster : generator._datas.size());

			while (occluderCounter < occluders.size())
			{
				auto &current = occluders[occluderCounter];

				Key<Painter> painterKey;
				UnConcatenateKey(current.verticeKey, painterKey, verticesKey);

				if (painterKey.isValid())
				{
					painter = _painterManager->get_painter(painterKey);
					painter->instanciedDrawBegin(_programs[PROGRAM_BUFFERING_SKINNED]);
					matrixOffset.set(float(current.from));
					bonesOffset.set(float(current.bonesIndex));
					painter->instanciedDraw(GL_TRIANGLES, _programs[PROGRAM_BUFFERING_SKINNED], verticesKey, current.size);
					painter->instanciedDrawEnd();
				}
				++occluderCounter;
			}
		}
	}
}
