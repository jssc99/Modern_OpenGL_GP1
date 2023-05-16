#include "../include/resourceManager.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

IResource ResourceManager::createR(std::string name)
{
	// TEXTURES
	// .png, .jpg

	// SHADERS
	// .vert VERTEX
	// .frag FRAGMENT

	// 


	return IResource();
}

IResource ResourceManager::getR(std::string name)
{
	return IResource();
}

void ResourceManager::deleteR(std::string name)
{
	for (int i = 0; i < resources.size(); ++i)
		if (resources[i]->name.compare(name)) {
			resources.erase(resources.begin() + i);
			DEBUG_LOG(name << " has been delete from resourceManager\n");
			return;
		}

	DEBUG_LOG(name << " was NOT delete from resourceManager, item NOT found\n");
}