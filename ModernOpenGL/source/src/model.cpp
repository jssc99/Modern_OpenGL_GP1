#include "../include/model.hpp"

void Model::loadResource(fs::path filePath)
{
	DEBUG_LOG("loading %s", filePath.string().c_str());
	std::ifstream file(filePath);
	ASSERT(file.is_open());
	path = filePath;

	string curLine, beginLine;

	while (!file.eof())
	{
		string prevLine = beginLine;
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
			tmpVNorm.push_back(v);
		}
		else if (beginLine == "vt")
		{
			vec2 v;
			file >> v.x >> v.y;
			tmpVText.push_back(v);
		}
		else if (beginLine == "f")
		{
			// get and reformat current line for clean use
			while (file.peek() == ' ')
				file.get();
			getline(file, curLine);
			while (curLine[curLine.length() - 1] == ' ')
				curLine.resize(curLine.length() - 1);

			string i1 = curLine.substr(0, curLine.find(" ", 1)), i2, i3;

			size_t i1Length = i1.length() + 1;
			i2 = curLine.substr(i1Length, curLine.find(" ", i1Length) - i1Length);

			size_t i1i2Length = i1Length + i2.length() + 1;
			i3 = curLine.substr(i1i2Length, curLine.find(" ", i1i2Length) - i1i2Length);

			uint32_t ind1 = getIndice(i1);
			uint32_t ind2 = getIndice(i2);
			uint32_t ind3 = getIndice(i3);

			indices.push_back(ind1);
			indices.push_back(ind2);
			indices.push_back(ind3);

			if (curLine.length() > i1.length() + i2.length() + i3.length() + 2/*= spaces*/) {
				string i4 = curLine.substr(i1i2Length + i3.length() + 1, curLine.length());
				indices.push_back(getIndice(i4));
				indices.push_back(ind3);
				indices.push_back(ind1);
			}
		}
		else
		{
			getline(file, curLine);
			curLine = beginLine + curLine;
			//DEBUG_LOG("line not used while loading %s : %s", filePath.string().c_str(), curLine.c_str())
		}
		beginLine = "";
	}

	tmpVPos.clear();
	tmpVNorm.clear();
	tmpVText.clear();

	buffer = new Buffer(vertices, indices);
}

void Model::draw()
{
	glBindVertexArray(buffer->VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

uint32_t Model::getIndice(string& line)
{
	uint32_t pos = getPosString(line) - 1;
	uint32_t nor = getNorString(line) - 1;
	uint32_t tex = getTexString(line) - 1;

	Vertex v;
	v.position = tmpVPos[pos];
	v.normal = tmpVNorm[nor];
	v.textureUV = tmpVText[tex];

	uint32_t ind = 0; bool found = false;
	for (uint32_t i = 0; i < vertices.size(); ++i)
		if (vertices[i].position == v.position &&
			vertices[i].normal == v.normal &&
			vertices[i].textureUV == v.textureUV) {
			ind = i;
			found = true;
		}

	if (!found) {
		vertices.push_back(v);
		ind = (uint32_t)vertices.size() - 1;
	}

	return ind;
}

uint32_t Model::getPosString(string line)
{
	return stoi(line.substr(0, line.find("/")));
}

uint32_t Model::getNorString(string line)
{
	line.erase(0, line.find("/") + 1);
	line.erase(0, line.find("/") + 1);
	return stoi(line.substr(0, line.find("/")));
}

uint32_t Model::getTexString(string line)
{
	line.erase(0, line.find("/") + 1);
	return stoi(line);
}