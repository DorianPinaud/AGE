#include "Material.hh"

Material::Material(MaterialManager *manager, const std::string &name)
	: _manager(manager)
	, _name(name)
{}

Material::~Material()
{}

Material &Material::pushShader(const std::string &shader)
{
	_shaders.push_back(shader);
	return *this;
}

const std::vector<std::string> &Material::getShaders() const
{
	return _shaders;
}

void Material::addObject(Components::MeshRenderer *object)
{
	_meshs.insert(object);
}

void Material::removeObject(Components::MeshRenderer *object)
{
	_meshs.erase(object);
}
