#pragma once

#include <assimp/Importer.hpp>
#include <assimp/types.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>

#include <iostream>

#include <Utils/OldFile.hpp>

#include "AssetdataSet.hpp"
#include "ConvertorStatusManager.hpp"
#include "CookingTask.hpp"

namespace AGE
{
	struct Skeleton;

	namespace AssimpLoader
	{
		static void replaceExtension(std::string &path, const std::string &extension)
		{
			auto lastindex = path.find_last_of(".");
			if (lastindex == std::string::npos)
				return;
			path = path.substr(0, lastindex);
			path += extension;
		}

		static glm::mat4 aiMat4ToGlm(const aiMatrix4x4 &m)
		{
			return glm::mat4(m.a1, m.b1, m.c1, m.d1, m.a2, m.b2, m.c2, m.d2, m.a3, m.b3, m.c3, m.d3, m.a4, m.b4, m.c4, m.d4);
		}

		static glm::vec4 aiColorToGlm(const aiColor4D &m)
		{
			return glm::vec4(m.r, m.g, m.b, m.a);
		}

		static glm::vec4 aiColorToGlm(const aiColor3D &m)
		{
			return glm::vec4(m.r, m.g, m.b, 1.0f);
		}

		static std::string aiStringToStd(const aiString &m)
		{
			return std::string(m.C_Str());
		}

		static bool Load(std::shared_ptr<CookingTask> cookingTask)
		{
			auto path = cookingTask->rawDirectory.path().string() + "\\" + cookingTask->dataSet->filePath.getFullName();
			if (!OldFile(path).exists())
			{
				std::cerr << "File [" << path << "] does not exists." << std::endl;
				return false;
			}
			auto tid = Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PushTask("Assimp : loading " + cookingTask->dataSet->filePath.getShortFileName());

			cookingTask->assimpScene = const_cast<aiScene*>(cookingTask->assimpImporter.ReadFile(
				path
				, aiProcess_Triangulate |
				aiProcess_GenNormals |
				aiProcess_CalcTangentSpace |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType |
				aiProcess_ImproveCacheLocality |
				aiProcess_OptimizeMeshes |
				aiProcess_FindDegenerates |
				aiProcess_FindInvalidData));
			if (cookingTask->assimpScene == nullptr)
			{
				Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PopTask(tid);
				std::cerr << "Assimp fail to load file [" << path << "] : " << cookingTask->assimpImporter.GetErrorString() << std::endl;
				return false;
			}
			Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PopTask(tid);
			return true;
		}
	}
}