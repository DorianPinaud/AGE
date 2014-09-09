#include <Render/OpenGLTask.hh>
#include <Utils/OpenGL.hh>
#include <glm/glm.hpp>
#include <assert.h>
#include <memory>
#include <string>
#include <Core/Drawable.hh>
#include <Render/Render.hh>
#include <Render/GeometryManager.hh>
#include <Render/MaterialManager.hh>

#define CONVERT(type, index) (*((type *)data[index]))

namespace gl
{

	void setScissor(void **data)
	{
		glScissor((*(glm::ivec4 *)data)[0], (*(glm::ivec4 *)data)[1], (*(glm::ivec4 *)data)[2], (*(glm::ivec4 *)data)[3]);
	}

	void setClearValue(void **data)
	{
		glClearColor(CONVERT(glm::vec4, 0).r, CONVERT(glm::vec4, 0).g, CONVERT(glm::vec4, 0).b, CONVERT(glm::vec4, 0).a);
		glClearDepth(CONVERT(float, 1));
		glClearStencil(CONVERT(unsigned char, 2));
	}

	void setColorMask(void **data)
	{
		glColorMaski(CONVERT(GLuint, 0), CONVERT(glm::bvec4, 1)[0], CONVERT(glm::bvec4, 1)[1], CONVERT(glm::bvec4, 1)[2], CONVERT(glm::bvec4, 1)[3]);
	}

	void setDepthMask(void **data)
	{
		glDepthMask(CONVERT(bool, 0));
	}

	void setStencilMask(void **data)
	{
		glStencilMaskSeparate(GL_FRONT, CONVERT(uint8_t, 0));
		glStencilMaskSeparate(GL_BACK, CONVERT(uint8_t, 1));
	}

	void clear(void **data)
	{
		GLenum colorBit = CONVERT(bool, 0) ? GL_COLOR_BUFFER_BIT : 0;
		GLenum depthBit = CONVERT(bool, 1) ? GL_DEPTH_BUFFER_BIT : 0;
		GLenum stencilBit = CONVERT(bool, 2) ? GL_STENCIL_BUFFER_BIT : 0;
		glClear(colorBit | depthBit | stencilBit);
	}

	void setTest(void **data)
	{
		if (CONVERT(bool, 0)) { glEnable(GL_SCISSOR_TEST); }
		else { glDisable(GL_SCISSOR_TEST); }
		if (CONVERT(bool, 1)) { glEnable(GL_STENCIL_TEST); }
		else { glDisable(GL_STENCIL_TEST); }
		if (CONVERT(bool, 2)) { glEnable(GL_DEPTH_TEST); }
		else { glDisable(GL_DEPTH_TEST); }
	}

	void setStencilFunctionFrontFace(void **data)
	{
		glStencilFuncSeparate(GL_FRONT, CONVERT(GLenum, 0), CONVERT(int, 1), CONVERT(uint8_t, 2));
	}

	void setStencilOperationFrontFace(void **data)
	{
		glStencilOpSeparate(GL_FRONT, CONVERT(GLenum, 0), CONVERT(GLenum, 1), CONVERT(GLenum, 2));
	}

	void setStencilFunctionBackFace(void **data)
	{
		glStencilFuncSeparate(GL_BACK, CONVERT(GLenum, 0), CONVERT(int, 1), CONVERT(uint8_t, 2));
	}

	void setStencilOperationBackFace(void **data)
	{
		glStencilOpSeparate(GL_BACK, CONVERT(GLenum, 0), CONVERT(GLenum, 1), CONVERT(GLenum, 2));
	}

	void setStencilFunction(void **data)
	{
		glStencilFunc(CONVERT(GLenum, 0), CONVERT(int, 1), CONVERT(uint8_t, 2));
	}

	void setStencilOperation(void **data)
	{
		glStencilOp(CONVERT(GLenum, 0), CONVERT(GLenum, 1), CONVERT(GLenum, 2));
	}

	void setBlend(void **data)
	{
		if (CONVERT(bool, 1))
			glEnablei(GL_BLEND, CONVERT(int, 0));
		else
			glDisablei(GL_BLEND, CONVERT(int, 0));
	}

	void setBlendEquationSeparate(void **data)
	{
		glBlendEquationSeparate(CONVERT(GLenum, 0), CONVERT(GLenum, 1));
	}

	void setBlendEquation(void **data)
	{
		glBlendEquation(CONVERT(GLenum, 0));
	}

	void setBlendFuncSeparate(void **data)
	{
		glBlendFuncSeparate(CONVERT(GLenum, 0), CONVERT(GLenum, 1), CONVERT(GLenum, 2), CONVERT(GLenum, 3));
	}

	void setBlendFunc(void **data)
	{
		glBlendFunc(CONVERT(GLenum, 0), CONVERT(GLenum, 1));
	}

	void setBlendConstant(void **data)
	{
		glBlendColor(CONVERT(glm::vec4, 0)[0], CONVERT(glm::vec4, 0)[1], CONVERT(glm::vec4, 0)[2], CONVERT(glm::vec4, 0)[4]);
	}

	void setUniformMat4(void **data)
	{
		glUniformMatrix4fv(CONVERT(unsigned int, 0), 1, GL_FALSE, (const float *)&(CONVERT(glm::mat4, 1)));
	}

	void setUniformMat3(void **data)
	{
		glUniformMatrix3fv(CONVERT(unsigned int, 0), 1, GL_FALSE, (const float *)&(CONVERT(glm::mat3, 1)));
	}

	void setUniformUint(void **data)
	{
		glUniform1i(CONVERT(unsigned int, 0), CONVERT(int, 1));
	}

	void setBlockBinding(void **data)
	{
		glUniformBlockBinding(CONVERT(GLuint, 0), CONVERT(GLuint, 1), CONVERT(GLuint, 2));
	}

	void setUniformFloat(void **data)
	{
		glUniform1f(CONVERT(unsigned int, 0), CONVERT(float, 1));
	}

	void setUniformVec4(void **data)
	{
		glUniform4f(CONVERT(unsigned int, 0), CONVERT(glm::vec4, 1).x, CONVERT(glm::vec4, 1).y, CONVERT(glm::vec4, 1).z, CONVERT(glm::vec4, 1).w);
	}

	void setUniformSampler(void **data)
	{
		glActiveTexture(GL_TEXTURE0 + CONVERT(GLuint, 0));
		glBindTexture(CONVERT(GLenum, 1), CONVERT(GLint, 2));
	}

	void setUniformMat4byLocation(void **data)
	{
		RenderOffScreen::Draw &draw = *CONVERT(RenderOffScreen::Draw *, 0);
		Key<Uniform> const &key = CONVERT(Key<Uniform>, 1);
		size_t location = CONVERT(size_t, 2);
		draw.shader.setUniform(key, draw.locationStorage.getLocation<glm::mat4>(location));
	}

	void setUniformMat3byLocation(void **data)
	{
		RenderOffScreen::Draw &draw = *CONVERT(RenderOffScreen::Draw *, 0);
		Key<Uniform> const &key = CONVERT(Key<Uniform>, 1);
		size_t location = CONVERT(size_t, 2);
		draw.shader.setUniform(key, draw.locationStorage.getLocation<glm::mat3>(location));
	}

	void setUniformFloatbyLocation(void **data)
	{
		RenderOffScreen::Draw &draw = *CONVERT(RenderOffScreen::Draw *, 0);
		Key<Uniform> const &key = CONVERT(Key<Uniform>, 1);
		size_t location = CONVERT(size_t, 2);
		draw.shader.setUniform(key, draw.locationStorage.getLocation<float>(location));
	}

	void setUniformVec4byLocation(void **data)
	{
		RenderOffScreen::Draw &draw = *CONVERT(RenderOffScreen::Draw *, 0);
		Key<Uniform> const &key = CONVERT(Key<Uniform>, 1);
		size_t location = CONVERT(size_t, 2);
		draw.shader.setUniform(key, draw.locationStorage.getLocation<glm::vec4>(location));
	}

	void draw(void **data)
	{
		RenderPass::Draw &draw = *CONVERT(RenderPass::Draw *, 0);

		for (size_t index = draw.start; index < draw.end; ++index)
		{
			AGE::Drawable const &object = (*draw.toRender)[index];
			draw.materialManager.setShader(object.material, draw.shader);
			draw.shader.update(object.transformation);
			draw.geometryManager.draw(draw.mode, object.mesh.indices, object.mesh.vertices);
		}
	}

	Task::Task()
		: nbrParams(0), 
		params(NULL), 
		sizeParams(NULL), 
		func(NULL),
		update(true),
		indexToTarget(0)
	{
	}

	void Task::clear()
	{
		func = NULL;
		for (size_t index = 0; index < nbrParams; ++index)
			delete params[index];
		if (params)
			delete[] params;
		params = NULL;
		if (sizeParams)
			delete[] sizeParams;
		sizeParams = NULL;
		nbrParams = 0;
		update = false;
		indexToTarget = 0;
	}

	bool Task::isExec()
	{
		return (func == NULL ? false : true);
	}
}