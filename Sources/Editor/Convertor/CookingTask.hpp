#pragma once

#include <PxPhysicsAPI.h>

#include "AssetDataSet.hpp"

namespace AGE
{
	struct CookingTask
	{
		CookingTask(std::shared_ptr<AssetDataSet> _dataSet)
		{
			dataSet = _dataSet;
			dataSet->isConverting = true;
			taskId = Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PushTask("In active conversion : " + dataSet->filePath.getShortFileName());
		}

		~CookingTask()
		{
			auto tid = Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PushTask("Releasing memory for : " + dataSet->filePath.getShortFileName());
			assimpImporter.FreeScene();
			animations.clear();
			materials.clear();
			textures.clear();
			Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PopTask(tid);
			Singleton<AGE::AE::ConvertorStatusManager>::getInstance()->PopTask(taskId);
			dataSet->isConverting = false;
		}

		//Directory
		std::tr2::sys::directory_entry rawDirectory;
		std::tr2::sys::directory_entry serializedDirectory;

		std::set<std::string> texturesPath;

		//Ptrs
		std::shared_ptr<Skeleton> skeleton = nullptr;
		AGE::Vector<std::shared_ptr<AnimationData>> animations;
		std::shared_ptr<MeshData> mesh = nullptr;
		AGE::Vector<std::shared_ptr<MaterialData>> materials;
		AGE::Vector<std::shared_ptr<TextureData>> textures;
		std::shared_ptr<btConvexHullShape> convexShape;
		std::shared_ptr<btBvhTriangleMeshShape> concaveShape;
		std::vector<physx::PxConvexMesh *> physxConvexShapes;
		std::vector<physx::PxTriangleMesh *> physxConcaveShapes;

		//Assimp
		aiScene* assimpScene = nullptr;
		Assimp::Importer assimpImporter;
		std::shared_ptr<AssetDataSet> dataSet;

		std::size_t taskId;
	};
}