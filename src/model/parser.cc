#include "parser.h"

#include <iostream>

namespace s21 {

  /**
   * @brief Method for getting the FileReader object
   *
   * @return FileReader*
   */
  FileReader *FileReader::getInstance()
  {
    if (!instance)
    {
      instance = new FileReader();
    }
    return instance;
}

/**
 * @brief A method for parsing an object file
 *
 * @param filename - the path to the file
 * @param objectData - representation of data about an `.obj` file
 * @return true - if the parsing is successful
 * @return false - if the parsing is failed
 */
bool FileReader::parseObject(std::string filename, ObjectData &objectData) {
  try {
    file_.open(filename);
    if (!file_.is_open()) {
      throw std::runtime_error("Failed to open file: " + filename);
    }
    objectData.clear();
    objectData.name = readObjectName(filename);
    parseVerticesAndFaces(objectData);
    file_.close();
    return true;
  } catch (...) {
    return false;
  }
}

/**
 * @brief The method returns the name of the object to be read
 *
 * @param filename - the path to the readable object
 * @return std::string
 */
std::string FileReader::readObjectName(const std::string &filename) {
  std::string name;
  size_t lastSlash = filename.find_last_of('/');
  if (lastSlash != std::string::npos) {
    name = filename.substr(lastSlash + 1);
  } else {
    name = filename;
  }
  return name;
}

/**
 * @brief The method reads the vertices and faces of an object
 *
 * @param objectData - representation of data about an `.obj` file
 */
void FileReader::parseVerticesAndFaces(ObjectData &objectData) {
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

/**
 * @brief A method for parsing vertices
 *
 * @param iss - the string file stream
 * @param objectData - representation of data about an `.obj` file
 */
void FileReader::parseVertex(std::istringstream &iss, ObjectData &objectData) {
  float x, y, z;
  iss >> x >> y >> z;
  objectData.addVertex(x, y, z);
}

/**
 * @brief A method for parsing faces
 *
 * @param iss - the string file stream
 * @param objectData - representation of data about an `.obj` file
 */
void FileReader::parseFace(std::istringstream &iss, ObjectData &objectData) {
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

// int main() {
//   // Get the singleton instance of FileReader
//   s21::FileReader* fileReader = s21::FileReader::getInstance();

//   s21::ObjectData objectData;
//   fileReader->parseObject("cube.obj", objectData);

//   // Example usage
//   std::cout << "Vertex count: " << objectData.vertexNumber << std::endl;
//   std::cout << "Edge count: " << objectData.edgesNumber << std::endl;
//   std::cout << "Name: " << objectData.name << std::endl;

//   fileReader->parseObject("dragon.obj", objectData);

//   // Example usage
//   std::cout << "Vertex count: " << objectData.vertexNumber << std::endl;
//   std::cout << "Edge count: " << objectData.edgesNumber << std::endl;
//   std::cout << "Name: " << objectData.name << std::endl;

//   return 0;
// }
