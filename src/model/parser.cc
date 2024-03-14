#include "parser.h"

#include <iostream>

namespace s21 {

FileReader* FileReader::getInstance() {
  if (!instance) {
    instance = new FileReader();
  }
  return instance;
}

ObjectData FileReader::parseObject(std::string filename) {
  file_.open(filename);
  if (!file_.is_open()) {
    throw std::runtime_error("Failed to open file");  //?
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
    std::cout << line;
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
    // Skip the slash and the following indices
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
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

// using namespace s21;

// //FileReader* FileReader::instance = nullptr;

// int main() {
//   // Get the singleton instance of FileReader
//   FileReader* fileReader = FileReader::getInstance();

//   ObjectData objectData = fileReader->parseObject("cube.obj");

//   // Example usage
//   std::cout << "Vertex count: " << objectData.vertexNumber << std::endl;
//   std::cout << "Edge count: " << objectData.edgesNumber << std::endl;
//   std::cout << "Name: " << objectData.name << std::endl;

//   ObjectData objectData2 = fileReader->parseObject("dragon.obj");

//   // Example usage
//   std::cout << "Vertex count: " << objectData2.vertexNumber << std::endl;
//   std::cout << "Edge count: " << objectData2.edgesNumber << std::endl;
//   std::cout << "Name: " << objectData2.name << std::endl;

//   return 0;
// }
