#pragma once

#include "../include/texture.hpp"
#include "../include/shader.hpp"

#include "IResource.hpp"
#include <map>

namespace Resources {
	class ResourceManager
	{
	public:
		ResourceManager() {};
		~ResourceManager() {
			for (auto it = resources.begin(); it != resources.end();) {
				it = resources.erase(it);
			}
		};

		template <class T> T* createR(string name);

		template <class T> T* getR(string name);

		void deleteR(string name);

		fs::path findPath(string name);

	private:
		std::map<string, std::unique_ptr<IResource>> resources;
	};

	template<class T>
	T* ResourceManager::createR(string name)
	{
		// find resource in files
		// if not found
		// return nullptr
		// if resource already exist
		// replace & return it
		// else
		// load it to resources
		// return it

		fs::path pathFile = findPath(name);

		if (pathFile == "")
		{
			DEBUG_LOG("%s :file not found", name.c_str());
			return nullptr;
		}

		if (resources[name])
		{
			DEBUG_LOG("%s :resource already exist, reloading resource", name.c_str());
			resources[name]->loadResource(pathFile);
			return (T*)resources[name].get();
		}

		resources[name] = std::make_unique<T>();
		resources[name]->loadResource(pathFile);

		return (T*)resources[name].get();
	}

	template <class T>
	T* ResourceManager::getR(string name)
	{
		if (resources[name])
			return (T*)resources[name].get();

		DEBUG_LOG("%s :was NOT found in resourceManager\n", name.c_str());
		return nullptr;
	}

	void ResourceManager::deleteR(string name)
	{
		if (resources[name]) {
			resources.erase(name);
			DEBUG_LOG("%s :has been delete from resourceManager\n", name.c_str());
			return;
		}

		DEBUG_LOG("%s :was NOT deleted from resourceManager, item NOT found\n", name.c_str());
	}

	fs::path ResourceManager::findPath(string name)
	{
		for (fs::path file : fs::recursive_directory_iterator(fs::current_path()))
			if (file.filename().string().find(name) != string::npos)
				return file;
		return fs::path();
	}
}