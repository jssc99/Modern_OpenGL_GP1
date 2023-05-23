#include "../include/model.hpp"

Model::~Model()
{
	delete buffer;
}

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
			Vec3 v;
			file >> v.x >> v.y >> v.z;
			tmpVPos.push_back(v);
		}
		else if (beginLine == "vn")
		{
			Vec3 v;
			file >> v.x >> v.y >> v.z;
			tmpVNorm.push_back(v);
		}
		else if (beginLine == "vt")
		{
			Vec2 v;
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
			//cout << curLine << "." << endl;

			string i1 = curLine.substr(0, curLine.find(" ", 1)), i2, i3;

			size_t i1Length = i1.length() + 1;
			i2 = curLine.substr(i1Length, curLine.find(" ", i1Length) - i1Length);

			size_t i1i2Length = i1Length + i2.length() + 1;
			i3 = curLine.substr(i1i2Length, curLine.find(" ", i1i2Length) - i1i2Length);

			//cout << "i1 :" << i1 << "." << endl;
			//cout << "i2 :" << i2 << "." << endl;
			//cout << "i3 :" << i3 << "." << endl;

			createIndice(i1);
			uint32_t ind2 = createIndice(i2);
			uint32_t ind3 = createIndice(i3);

			if (curLine.length() > i1.length() + i2.length() + i3.length() + 2/*= spaces*/) {
				string i4 = curLine.substr(i1i2Length + i3.length() + 1, curLine.length());
				indices.push_back(ind2);
				indices.push_back(ind3);
				createIndice(i4);
				//cout << "i4 :" << i4 << "." << endl;
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

	//cout << "Test obj file:" << endl;
	//for (Vec3 v : tmpVPos)
	//    cout << "v: " << v.x << ", " << v.y << ", " << v.z << endl;
	//for (Vec3 v : tmpVNorm)
	//    cout << "vn: " << v.x << ", " << v.y << ", " << v.z << endl;
	//for (Vec2 v : tmpVText)
	//    cout << "vt: " << v.x << ", " << v.y << endl;

	//cout << "Indices:" << endl;
	//for (uint32_t i = 0; i < indices.size(); ++i) {
	//	cout << indices[i] << ", ";
	//	if (!((i + 1) % 3)) cout << '\n';
	//}
	//cout << endl;

	tmpVPos.clear();
	tmpVNorm.clear();
	tmpVText.clear();

	buffer = new Buffer(vertices, indices);
}

void Model::draw()
{
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);

	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t Model::createIndice(string& line)
{
	uint32_t pos = getPosString(line) - 1;
	uint32_t tex = getTexString(line) - 1;
	uint32_t nor = getNorString(line) - 1;

	Vertex v;
	v.Position = tmpVPos[pos];
	v.TextureUV = tmpVText[tex];
	v.Normal = tmpVNorm[nor];

	uint32_t ind = 0; bool found = false;
	for (uint32_t i = 0; i < vertices.size(); ++i)
		if (vertices[i].Position == v.Position &&
			vertices[i].TextureUV == v.TextureUV &&
			vertices[i].Normal == v.Normal) {
			ind = i;
			found = true;
		}

	if (!found) {
		vertices.push_back(v);
		ind = (uint32_t)vertices.size();
	}

	indices.push_back(ind);
	return ind;
}

uint32_t Model::getPosString(string line)
{
	return stoi(line.substr(0, line.find("/")));
}

uint32_t Model::getTexString(string line)
{
	line.erase(0, line.find("/") + 1);
	return stoi(line.substr(0, line.find("/")));
}

uint32_t Model::getNorString(string line)
{
	line.erase(0, line.find("/") + 1);
	line.erase(0, line.find("/") + 1);
	return stoi(line);
}