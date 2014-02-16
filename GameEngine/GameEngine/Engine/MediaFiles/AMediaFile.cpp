#include <MediaFiles/AMediaFile.hpp>
#include <MediaFiles/MaterialFile.hpp>
#include <MediaFiles/ObjFile.hpp>
#include <MediaFiles/TextureFile.hpp>
#include <MediaFiles/CubeMapFile.hpp>
#include <MediaFiles/CollisionShapeStaticFile.hpp>
#include <MediaFiles/CollisionShapeDynamicFile.hpp>
#include <MediaFiles/CollisionBoxFile.hpp>
#include <MediaFiles/CollisionSphereFile.hpp>
#include <thread>
#include <memory>

std::shared_ptr<AssetsManager> AMediaFile::_manager = nullptr;

void AMediaFile::loadFromList(const File &file)
{
	assert(file.exists() == true && "File does not exist.");

	std::ifstream ifs(file.getFullName(), std::ios::binary);
	cereal::JSONInputArchive ar(ifs);
	std::multimap<std::size_t, std::string> list;
	ar(list);

	std::vector<std::thread> threads;
	for (auto &e : list)
	{
		threads.push_back(std::thread([e]()
		{
			AMediaFile::loadFromFile<cereal::BinaryInputArchive>(File(e.second));
		}));
	}
	std::for_each(std::begin(threads), std::end(threads), [](std::thread &t){t.join(); });
}
std::shared_ptr<AMediaFile> AMediaFile::get(const std::string &name)
{
	return _manager->get(name);
}

std::shared_ptr<AMediaFile> AMediaFile::loadBulletFile(const File &file)
{
		assert(file.exists() == true && "File does not exist.");
		std::shared_ptr<AMediaFile> res{ nullptr };
		res = _manager->get(file.getShortFileName());
		if (res != nullptr)
			return res;
		if (file.getShortFileName().find("collision_shape_static") != std::string::npos)
		{
				res = std::make_shared<CollisionShapeStaticFile>();
				static_cast<CollisionShapeStaticFile&>(*res.get()).unserialize(file);
		}
		else if (file.getShortFileName().find("collision_shape_dynamic") != std::string::npos)
		{
				res = std::make_shared<CollisionShapeDynamicFile>();
				static_cast<CollisionShapeDynamicFile&>(*res.get()).unserialize(file);
		}
		else if (file.getShortFileName().find("collision_sphere") != std::string::npos)
		{
				res = std::make_shared<CollisionSphereFile>();
				static_cast<CollisionSphereFile&>(*res.get()).unserialize(file);
		}
		else if (file.getShortFileName().find("collision_box") != std::string::npos)
		{
				res = std::make_shared<CollisionBoxFile>();
				static_cast<CollisionBoxFile&>(*res.get()).unserialize(file);
		}
		assert(res != nullptr && "Unknown MediaFile type.");
		assert(_manager != nullptr && "Media Manager is not set.");
		res->path = file.getFullName();
		res->name = file.getShortFileName();
		_manager->add(res);
		return res;
}

void AMediaFile::serializeAsBulletFile(std::ofstream &s)
{
	if (_type == COLLISION_SHAPE_STATIC)
	{
		static_cast<CollisionShapeStaticFile*>(this)->serialize(s);
	}
	else if (_type == COLLISION_SHAPE_DYNAMIC)
	{
		static_cast<CollisionShapeDynamicFile*>(this)->serialize(s);
	}
	else if (_type == COLLISION_BOX)
	{
		static_cast<CollisionBoxFile*>(this)->serialize(s);
	}
	else if (_type == COLLISION_SPHERE)
	{
		static_cast<CollisionSphereFile*>(this)->serialize(s);
	}
}