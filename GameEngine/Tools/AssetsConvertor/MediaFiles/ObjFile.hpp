#ifndef  __OBJ_FILE_HPP__
# define __OBJ_FILE_HPP__

#include <MediaFiles/AMediaFile.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>

struct ObjFile : public AMediaFile
{
	ObjFile() : AMediaFile()
	{
		type = typeid(ObjFile).hash_code();
	}
	virtual ~ObjFile(){}
	struct Geometry
	{
		std::string                 name;
		std::vector<glm::vec4>		vertices;	// vertices positions
		std::vector<glm::vec4>		normals;	// normals
		std::vector<glm::vec4>		colors;		// vertices colors
		std::vector<glm::vec2>		uvs;		// texture coordinates
		std::vector<unsigned int>	indices;	// indices
	};
	std::vector<Geometry> geometries;
	unsigned int test;
	//	std::vector<MaterialFile> materials;

	virtual void serialize(std::ofstream &s)
	{
		{
			cereal::JSONOutputArchive ar(s);
			ar(type);
//		}
//		{
//			cereal::JSONOutputArchive ar(s);
			ar(*this);
		}
    }

	virtual AMediaFile *unserialize(cereal::JSONInputArchive &ar)
	{
		AMediaFile *res = new ObjFile();
		ar(static_cast<ObjFile&>(*res));
		return res;
	}

	template <typename Archive>
	void serialize(Archive &ar)
	{
		ar(test);
	}
};

#endif   //__OBJ_FILE_HPP__