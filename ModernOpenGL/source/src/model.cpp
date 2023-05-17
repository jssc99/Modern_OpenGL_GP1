#include "../include/model.hpp"

void Model::loadResource(fs::path filePath)
{
    // TODO check file opened
    std::ifstream file(filePath);
    path = filePath;

    string curLine, beginLine;
    int vTracker = 0;
    while (!file.eof())
    {
        string prevLine = beginLine;
        file >> beginLine;
        if (beginLine.compare(prevLine))
            vTracker = 0;

        if (beginLine == "v")
        {
            Vertex v;
            file >> v.Position.x >> v.Position.y >> v.Position.z;
            vertices.push_back(v);
        }
        else if (beginLine == "vt")
        {
            file >> vertices[vTracker].TextureUV.x >> vertices[vTracker].TextureUV.y;
            vTracker++;
        }
        else if (beginLine == "vn")
        {
            file >> vertices[vTracker].Normal.x >> vertices[vTracker].Normal.y >> vertices[vTracker].Normal.z;
            vTracker++;
        }
        else if (beginLine == "f")
        {
            // TODO
        }
        else 
        {
            getline(file, curLine);
            curLine = beginLine + curLine;
            DEBUG_LOG("line not used while loading %s : %s", filePath.string().c_str(), curLine.c_str())
        }
    }

    cout << "Test obj file:" << endl;
    for (Vertex v : vertices) {
        cout << "v: " << v.Position.x << ", " << v.Position.y << ", " << v.Position.z << endl;
        cout << "vn: " << v.Normal.x << ", " << v.Normal.y << ", " << v.Normal.z << endl;
        cout << "vt: " << v.TextureUV.x << ", " << v.TextureUV.y << endl << endl;
    }
}
