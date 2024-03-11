#include "parser.h"

namespace s21 {
ObjectData FileReader::parseObject(std::string filename) {
  file_.open(filename);
  if (!file_.is_open()) {
    throw std::runtime_error("Failed to open file"); //?
  }
  ObjectData objectData;
  objectData.name = readObjectName(filename);
  parseVerticesAndFaces(objectData);
  file_.close();
  return objectData;
}

std::string FileReader::readObjectName(const std::string& filename) {
  std::string name;
  size_t lastSlash = filename.find_last_of('/');
  if (lastSlash != std::string::npos) {
    name = filename.substr(lastSlash + 1);
  } else {
    name = filename;
  }
  return name;
}

void FileReader::parseVerticesAndFaces(ObjectData& objectData) {
  std::string line;
  while (std::getline(file_, line)) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;
    if (token == "v") {
      parseVertex(iss, objectData);
    } else if (token == "f") {
      parseFace(iss, objectData);
    }
  }
}

void FileReader::parseVertex(std::istringstream& iss, ObjectData& objectData) {
  float x, y, z;
  iss >> x >> y >> z;
  objectData.addVertex(x, y, z);
}

void FileReader::parseFace(std::istringstream& iss, ObjectData& objectData) {
  std::vector<unsigned> vertices;
  unsigned index;
  while (iss >> index) {
    vertices.push_back(index - 1);  // OBJ uses 1-based indexing
  }

  // Add edges for polygons
  for (size_t i = 0; i < vertices.size(); ++i) {
    unsigned v1 = vertices[i];
    unsigned v2 =
        vertices[(i + 1) % vertices.size()];  // Wrap around to the first
                                              // vertex for the last edge
    objectData.addEdge(v1, v2);
  }
}

}  // namespace s21
