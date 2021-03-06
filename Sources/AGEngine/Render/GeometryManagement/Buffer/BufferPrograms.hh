#pragma once

#include <Utils/OpenGL.hh>
#include <Utils/StringID.hpp>
#include <Render/GeometryManagement/Buffer/Buffer.hh>
#include <Render/GeometryManagement/Data/Vertices.hh>
#include <Render/ProgramResources/IProgramResources.hh>
#include <Render/Buffer/VertexArray.hh>
#include <vector>

namespace AGE
{
	class Program;

	class BufferPrograms
	{
	public:
		BufferPrograms(std::vector<std::pair<GLenum, StringID>> const &types);
		BufferPrograms(BufferPrograms &&move);

	public:
		bool insert(Vertices &vertices);
		BufferPrograms &clear();
		size_t size() const;
		BufferPrograms &bind();
		BufferPrograms &unbind();
		BufferPrograms &update();
		std::vector<std::pair<GLenum, StringID>> const &get_types() const;
		std::vector<std::shared_ptr<Buffer>> const &get_buffers() const;

	private:
		std::vector<std::pair<GLenum, StringID>> _types;
		std::vector<std::shared_ptr<Buffer>> _buffers;
		Buffer _indices_buffer;
		VertexArray _vertex_array;
	};
}
