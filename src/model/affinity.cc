#include "affinity.h"

void s21::Transformator::findMinMax(ObjectData &obj) {
  unsigned i = 0;
  if (obj.vertexNumber != 0) {
    obj.min[0] = obj.vertexArray[0];
    obj.max[0] = obj.vertexArray[0];
    obj.min[1] = obj.vertexArray[1];
    obj.max[1] = obj.vertexArray[1];
    obj.min[2] = obj.vertexArray[2];
    obj.max[2] = obj.vertexArray[2];
  } else {
    obj.min[0] = 0;
    obj.max[0] = 0;
    obj.min[1] = 0;
    obj.max[1] = 0;
    obj.min[2] = 0;
    obj.max[2] = 0;
  }
  for (i = 3; i < obj.vertex_number * 3; i += 3) {
    if (obj.min[0] > obj.vertexArray[i]) obj.min[0] = obj.vertexArray[i];
    if (obj.max[0] < obj.vertexArray[i]) obj.max[0] = obj.vertexArray[i];
    if (obj.min[1] > obj.vertexArray[i + 1])
      obj.min[1] = obj.vertexArray[i + 1];
    if (obj.max[1] < obj.vertexArray[i + 1])
      obj.max[1] = obj.vertexArray[i + 1];
    if (obj.min[2] > obj.vertexArray[i + 2])
      obj.min[2] = obj.vertexArray[i + 2];
    if (obj.max[2] < obj.vertexArray[i + 2])
      obj.max[2] = obj.vertexArray[i + 2];
  }
}

// float s21::Affinity::moveToCenter() {
  
//   findMinMax(obj);
//   float center[3] = {0};
//   center[0] = (obj->min[0] + obj->max[0]) / 2;
//   center[1] = (obj->min[1] + obj->max[1]) / 2;
//   center[2] = (obj->min[2] + obj->max[2]) / 2;
//   translation(obj, -center[0], -center[1], -center[2]);
//   float dx = obj->max[0] - center[0];
//   float dy = obj->max[1] - center[1];
//   float dz = obj->max[2] - center[2];
//   float dmax = dx > dy ? dx : dy;
//   dmax = dmax > dz ? dmax : dz;
//   dmax *= 1.10;
//   obj->max_coord = dmax;
//   return dmax;
// }

void s21::Translation::transform(ObjectData &obj, float &x, float &y, float &z) {

}