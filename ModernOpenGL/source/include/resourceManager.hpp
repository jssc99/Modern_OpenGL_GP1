#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "IResource.hpp"
#include <vector>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	IResource createR(std::string name);
	IResource getR(std::string name);
	void deleteR(std::string name);

private:
	std::vector<IResource*> resources;
};
#endif 