#ifndef SRC_MODEL_OBJECT_H_
#define SRC_MODEL_OBJECT_H_

#include <string>
#include <array>
#include <vector>

namespace s21 {
  class ObjectData {
    public:
      std::vector<float> vertexArray;
      std::vector<unsigned> edgesArray;
      unsigned vertexNumber;
      unsigned edgesNumber;
      std::string name;
      std::array<float, 3> min;
      std::array<float, 3> max;
      float maxCoord;
  };
}

#endif // SRC_MODEL_OBJECT_H_