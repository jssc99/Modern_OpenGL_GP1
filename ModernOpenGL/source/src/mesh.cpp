#include "../include/mesh.hpp"

using namespace Resources;
using namespace LowRenderer;

void Mesh::loadResource(fs::path filePath)
{
	DEBUG_LOG("loading: %s", filePath.string().c_str());
	std::ifstream file(filePath);
	ASSERT(file.is_open());
	path = filePath;

	while (!file.eof())
	{
		string curLine, beginLine;
		file >> beginLine;
		if (beginLine == "v")
		{
			vec3 v;
			file >> v.x >> v.y >> v.z;
			tmpVPos.push_back(v);
		}
		else if (beginLine == "vn")
		{
			vec3 v;
			file >> v.x >> v.y >> v.z;
			tmpVNor.push_back(v);
		}
		else if (beginLine == "vt")
		{
			vec2 v;
			file >> v.x >> v.y;
			tmpVTex.push_back(v);
		}
		else if (beginLine == "f")
		{
			string i1, i2, i3, i4;
			file >> i1 >> i2 >> i3;
			
			uint32_t ind1 = getIndice(i1), ind2 = getIndice(i2), ind3 = getIndice(i3);

			indices.push_back(ind1); indices.push_back(ind2); indices.push_back(ind3);

			while (file.peek() == ' ') file.get();

			if (file.peek() != '\n') {
				string i4; file >> i4;

				uint32_t ind4 = getIndice(i4);
				indices.push_back(ind1); indices.push_back(ind3); indices.push_back(ind4);

				while (file.peek() == ' ') file.get();

				if (file.peek() != '\n') {
					string i5; file >> i5;

					indices.push_back(ind1); indices.push_back(ind4); indices.push_back(getIndice(i5));
				}
			}
		}
		else
		{
			getline(file, curLine);
			//DEBUG_LOG("line not used while loading %s : %s", 
			//	filePath.string().c_str(), string(beginLine + curLine).c_str())
		}
	}
	file.close();
	DEBUG_LOG("%s : model pre-loaded", filePath.string().c_str());

	makeVertices(); 

	DEBUG_LOG("%s : model loaded", filePath.string().c_str());
}

bool fastCompare(string& s1, string& s2)
{
	unsigned int length = s1.length();
	if (length != s2.length())
		return 0;

	for (unsigned int i = 0; i < length; ++i)
		if (s1[i] != s2[i]) return 0;

	return 1;
}

uint32_t Mesh::getIndice(string& line)
{
	for (uint32_t i = 0; i < tmpIndices.size(); ++i)
		if (fastCompare(line, tmpIndices[i])) return i;
	//  else
	{
		tmpIndices.push_back(line);
		return (uint32_t)tmpIndices.size() - 1;
	}
}

uint32_t Mesh::getPosString(string line)
{
	line.erase(line.find('/'), line.length());
	return stoi(line) - 1;
}

uint32_t Mesh::getNorString(string line)
{
	if (tmpVNor.empty()) return 0;

	line.erase(0, line.find('/') + 1);
	line.erase(0, line.find('/') + 1);

	return stoi(line);
}

uint32_t Mesh::getTexString(string line)
{
	if (tmpVTex.empty()) return 0;

	line.erase(0, line.find('/') + 1);
	if (!tmpVNor.empty())
		line.erase(line.find('/'), line.length());

	if (line.empty() || line[0] == '/' || line[0] == ' ')
		return 0;
	return stoi(line);
}

void Mesh::makeVertices()
{
	if (tmpVNor.empty()) {
		tmpVNor.push_back(vec3(0.f));
		DEBUG_LOG("No normals found in file");
	}
	else
		tmpVNor.insert(tmpVNor.begin(), vec3(0.f));

	if (tmpVTex.empty()) {
		tmpVTex.push_back(vec2(0.f));
		DEBUG_LOG("No texture coords found in file");
	}
	else
		tmpVTex.insert(tmpVTex.begin(), vec2(0.f));

	for (unsigned int i = 0; i < tmpIndices.size(); ++i)
	{
		Vertex v = {
			tmpVPos[getPosString(tmpIndices[i])],
			tmpVNor[getNorString(tmpIndices[i])],
			tmpVTex[getTexString(tmpIndices[i])]
		};
		vertices.push_back(v);
	}

	tmpIndices.clear();
	tmpVPos.clear();
	tmpVNor.clear();
	tmpVTex.clear();
}