#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../include/texture.hpp"
#include "../include/shader.hpp"

#include "IResource.hpp"
#include <map>

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	template <class T>
	T* createR(string nameFile);

	template <class T>
	T* getR(string nameFile);

	void deleteR(string nameFile);

private:
	std::map<string, IResource*> resources;
};

fs::path findPath(string nameFile)
{
	for (fs::path file : fs::recursive_directory_iterator(fs::current_path()))
		if (!file.filename().string().compare(nameFile))
			return file;
	return fs::path();
}

template<class T>
T* ResourceManager::createR(string nameFile)
{
	// algo:
	// if resource already exist 
	// replace with & return new one
	// else
	// find resource in files
	// if not found
	// return nullptr
	// if found
	// load it
	// add it to resources
	// return it

	if (resources[nameFile])
	{
		resources[nameFile] = new T();
		resources[nameFile]->loadFromPath();
		return (T*)resources[nameFile];
	}

	fs::path pathFile = findPath(nameFile);

	if (pathFile == "")
	{
		DEBUG_LOG("file not found: %s", nameFile);
		return nullptr;
	}

	resources[nameFile] = new T();
	resources[nameFile]->loadResource(pathFile);

	return (T*)resources[nameFile];
}

template <class T>
T* ResourceManager::getR(string name)
{
	if (resources[name])
		return &resources[name];

	DEBUG_LOG("%s was NOT found in resourceManager\n", name);
	return nullptr;
}

void ResourceManager::deleteR(string name)
{
	if (resources[name]) {
		delete resources[name];
		resources.erase(name);
		DEBUG_LOG("%s has been delete from resourceManager\n", name);
		return;
	}

	DEBUG_LOG("%s was NOT deleted from resourceManager, item NOT found\n", name);
}
#endif 