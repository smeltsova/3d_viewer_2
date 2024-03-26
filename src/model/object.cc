#include "object.h"

void s21::ObjectData::freeObject() {
  vertexArray.clear();
  edgesArray.clear();
  vertexNumber = 0;
  edgesNumber = 0;
  name.clear();
  for (auto element: min) {
    element = 0;
  }
  for (auto element: max) {
    element = 0;
  }
  maxCoord = 0;
}