#pragma once

#include <Utils/OpenGL.hh>
#include <Utils/Dependency.hpp>
#include <OpenGL/Key.hh>
#include <OpenGL/MemoryBlocksGPU.hh>
#include <map>
#include <vector>

namespace gl
{
	class Shader;

	//!\file ShadingManager.hh
	//!\author Dorian Pinaud
	//!\version v1.0
	//!\class ShadingManager
	//!\brief Handle the shading of the object
	class ShadingManager : public Dependency
	{
	public:
		ShadingManager();
		~ShadingManager();

		// shader handling
		Key<Shader> addShader(std::string const &compute);
		Key<Shader> addShader(std::string const &frag, std::string const &vert);
		Key<Shader> addShader(std::string const &frag, std::string const &vert, std::string const &geometry);
		ShadingManager &rmShader(Key<Shader> const &shader);
		Key<Shader> const &getShader(size_t index) const;
		
		Key<Uniform> addShaderUniform(Key<Shader> const &shader, std::string const &flag);
		template <typename TYPE> Key<Uniform> addShaderUniform(Key<Shader> const &shader, std::string const &flag, T const &data);
		ShadingManager &rmShaderUniform(Key<Shader> const &shader, Key<Uniform> const &uniform);
		Key<Uniform> const &getShaderUniform(Key<Shader> const &shader, size_t index);
		template <typename TYPE> ShadingManager &setShaderUniform(Key<Shader> const &shader; Key<Uniform> const &uniform, TYPE const &data);
		
		//Key<Sampler> addShaderSampler(Key<Shader> const &shader, std::string const &flag);
		//template <typename TYPE> Key<Sampler> addShaderSampler(Key<Shader> const &shader, std::string const &flag, TYPE const &data);
		//ShadingManager &rmShaderSampler(Key<Shader> const &shader, Key<Sampler> const &sampler);
		//Key<Sampler> const &getShaderSampler(Key<Shader> const &shader, size_t index);
		//template <typename TYPE> ShadingManager &setShaderSampler(Key<Shader> const &shader; Key<Sampler> const &sampler, TYPE const &data);

		// handling Uniform Block
		//Key<UniformBlock> addUniformBlock();
		//ShadingManager &rmUniformBlock(Key<UniformBlock> const &uniformBlock)
		//Key<UniformBlock> const &getUniformBlock(size_t index) const;
		//template <typename TYPE> Key<UniformBlock> const &setUniformBlock(size_t index, TYPE const &data) const;


		//pipeline handling
		//Key<Pipeline> addPipeline(size_t nbrShader, Key<Shader> *shaders);
		//ShadingManager &rmPipeline(Key<Pipeline> const &pipeline);
		//Key<Pipeline> const &getPipeline(size_t index) const;
	private:
		std::map<Key<Shader>, Shader> _shaders;

		//std::map<key<UniformBlock>, UniformBuffer> _uniformBlocks;
		std::vector<MemoryBlocksGPU> _memoryUniformBlock;
		//std::map<Key<Pipeline>, Pipeline> _pipelines;
	};
}