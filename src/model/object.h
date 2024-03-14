#ifndef SRC_MODEL_OBJECT_H_
#define SRC_MODEL_OBJECT_H_

#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class ObjectData {
 public:
  std::vector<float> vertexArray{};
  std::vector<unsigned> edgesArray{};
  unsigned vertexNumber{};
  unsigned edgesNumber{};
  std::string name{};
  std::array<float, 3> min{};
  std::array<float, 3> max{};
  float maxCoord{};

  void addVertex(float x, float y, float z) {
    vertexArray.push_back(x);
    vertexArray.push_back(y);
    vertexArray.push_back(z);
    vertexNumber++;
  }

  void addEdge(unsigned v1, unsigned v2) {
    edgesArray.push_back(v1);
    edgesArray.push_back(v2);
    edgesNumber++;
  }
};
}  // namespace s21

#endif  // SRC_MODEL_OBJECT_H_