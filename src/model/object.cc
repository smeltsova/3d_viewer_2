#include "object.h"

void s21::ObjectData::addVertex(float x, float y, float z) {
  vertexArray.push_back(x);
  vertexArray.push_back(y);
  vertexArray.push_back(z);
  vertexNumber++;
}

void s21::ObjectData::addEdge(unsigned v1, unsigned v2) {
  edgesArray.push_back(v1);
  edgesArray.push_back(v2);
  edgesNumber++;
}

void s21::ObjectData::clear() {
  vertexArray.clear();
  edgesArray.clear();
  vertexNumber = 0;
  edgesNumber = 0;
  name.clear();
  min.fill(0);
  max.fill(0);
  maxCoord = 0;
}

// void s21::ObjectData::print_object() {
//   std::cout << "Vertex number: " << vertexNumber << std::endl;
//   std::cout << "Vertex vector len: " << vertexArray.size() << std::endl;
//   for (auto element : vertexArray) {
//     std::cout << element << " ";
//   }
//   std::cout << std::endl;

//   std::cout << "Edges number: " << edgesNumber << std::endl;
//   std::cout << "Edges vector len: " << edgesArray.size() << std::endl;
//   for (auto element : edgesArray) {
//     std::cout << element << " ";
//   }
//   std::cout << std::endl;

//   for (int i = 0; i < 3; i++) {
//     std::cout << min[i] << " ";
//   }
//   std::cout << std::endl;

//   for (int i = 0; i < 3; i++) {
//     std::cout << max[i] << " ";
//   }
//   std::cout << std::endl;

//   std::cout << "MaxCoord: " << maxCoord << std::endl;
//   std::cout << "Name: " << name << std::endl;
// }