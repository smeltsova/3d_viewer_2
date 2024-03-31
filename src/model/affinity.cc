#include "affinity.h"

s21::TransformatorBuilder::~TransformatorBuilder() {
  if (transformator) {
    delete transformator;
  }
};

/**
 * @brief A method for finding minimum/maximum vertices
 *
 * @param obj - representation of data about an `.obj` file
 */
void s21::Translation::findMinMax(ObjectData &obj) {
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
  for (i = 3; i < obj.vertexNumber * 3; i += 3) {
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

/**
 * @brief The method for centering the object
 *
 * @param obj - representation of data about an `.obj` file
 * @return float - the maximum coordinates of the vertex
 */
float s21::Translation::moveToCenter(ObjectData &obj) {
  findMinMax(obj);
  std::array<float, 3> center = {0};
  center[0] = (obj.min[0] + obj.max[0]) / 2;
  center[1] = (obj.min[1] + obj.max[1]) / 2;
  center[2] = (obj.min[2] + obj.max[2]) / 2;
  transform(obj, -center[0], -center[1], -center[2]);
  float dx = obj.max[0] - center[0];
  float dy = obj.max[1] - center[1];
  float dz = obj.max[2] - center[2];
  float dmax = dx > dy ? dx : dy;
  dmax = dmax > dz ? dmax : dz;
  dmax *= 1.10;
  obj.maxCoord = dmax;
  return dmax;
}

/**
 * @brief A method for translation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param tx - rotation coordinate
 * @param ty - rotation coordinate
 * @param tz - rotation coordinate
 */
void s21::Translation::transform(ObjectData &obj, float tx, float ty,
                                 float tz) {
  size_t size = obj.vertexNumber * 3;
  for (size_t i = 0; i < size; i += 3) {
    obj.vertexArray[i] += tx;
    obj.vertexArray[i + 1] += ty;
    obj.vertexArray[i + 2] += tz;
  }
}

/**
 * @brief A method for rotation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param angle - the angle of rotation
 * @param axis - the axis of rotation
 */
void s21::Rotation::transform(ObjectData &obj, float angle, char axis) {
  angle = angle / 180 * M_PI;
  size_t size = obj.vertexNumber * 3;
  for (size_t i = 0; i < size; i += 3) {
    float x = obj.vertexArray[i];
    float y = obj.vertexArray[i + 1];
    float z = obj.vertexArray[i + 2];
    if (axis == 'x') {
      obj.vertexArray[i + 1] = y * cos(angle) - z * sin(angle);
      obj.vertexArray[i + 2] = y * sin(angle) + z * cos(angle);
    } else if (axis == 'y') {
      obj.vertexArray[i] = x * cos(angle) + z * sin(angle);
      obj.vertexArray[i + 2] = -x * sin(angle) + z * cos(angle);
    } else if (axis == 'z') {
      obj.vertexArray[i] = x * cos(angle) - y * sin(angle);
      obj.vertexArray[i + 1] = x * sin(angle) + y * cos(angle);
    }
  }
}

/**
 * @brief A method for scaling an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param Sx - the scale on the x-axis
 * @param Sy - the scale on the y-axis
 * @param Sz - the scale on the z-axis
 */
void s21::Scaling::transform(ObjectData &obj, float Sx, float Sy, float Sz) {
  size_t size = obj.vertexNumber * 3;
  for (size_t i = 0; i < size; i += 3) {
    obj.vertexArray[i] *= Sx;
    obj.vertexArray[i + 1] *= Sy;
    obj.vertexArray[i + 2] *= Sz;
  }
}
