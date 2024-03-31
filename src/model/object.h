#ifndef SRC_MODEL_OBJECT_H_
#define SRC_MODEL_OBJECT_H_

#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class ObjectData {
 public:
  std::vector<float> vertexArray;
  std::vector<unsigned int> edgesArray;
  unsigned int vertexNumber;
  unsigned int edgesNumber;
  std::string name;
  std::array<float, 3> min;
  std::array<float, 3> max;
  float maxCoord;

  void addVertex(float x, float y, float z);
  void addEdge(unsigned int v1, unsigned int v2);
  void clear();
  // void print_object();
};
}  // namespace s21

#endif  // SRC_MODEL_OBJECT_H_