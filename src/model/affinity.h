/**
 * @file affinity.h
 * @author corbrayr (corbrayr@student.21-school.ru)
 * @brief
 * @version 0.1
 * @date 2024-03-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODEL_AFFINITY_H_
#define SRC_MODEL_AFFINITY_H_

#include <cmath>

#include "object.h"

namespace s21 {

// Builder Pattern

// Определение всех возможных преобразований
class Translation {
 public:
  void transform(ObjectData &obj, float tx, float ty, float tz);
  float moveToCenter(ObjectData &obj);
  void findMinMax(ObjectData &obj);
};

class Rotation {
 public:
  void transform(ObjectData &obj, float angle, char axis);
};

class Scaling {
 public:
  void transform(ObjectData &obj, float Sx, float Sy, float Sz);
};

class Transformator {
 public:
  Translation translation;
  Rotation rotation;
  Scaling scaling;
};

class TransformatorBuilder {
 public:
  TransformatorBuilder() { transformator = nullptr; };
  virtual ~TransformatorBuilder();
  virtual void createTransformator(){};
  virtual void buildTranslation(){};
  virtual void buildRotation(){};
  virtual void buildScaling(){};
  virtual Transformator *getTransformator() { return transformator; };

 protected:
  Transformator *transformator;
};

class AllTransformationBuilder : public TransformatorBuilder {
 public:
  void createTransformator() { transformator = new Transformator; };
  void buildTranslation() { transformator->translation = Translation(); };
  void buildRotation() { transformator->rotation = Rotation(); };
  void buildScaling() { transformator->scaling = Scaling(); };
};

class Director {
 public:
  Transformator *createTransformator(TransformatorBuilder &builder) {
    builder.createTransformator();
    builder.buildTranslation();
    builder.buildRotation();
    builder.buildScaling();
    return (builder.getTransformator());
  }
};
}  // namespace s21

/*
 * Director dr;
 * AllTransformationBuilder allBuilder;
 * Transformator *tr = dir.createTransformator( allBuilder );
 * tr->translation.transform(obj, x, y, z);
 * tr->rotation.transform(obj, angle, axis);
 * tr->scaling.transform(obj, Sx, Sy, Sz);
 */

#endif  // SRC_MODEL_AFFINITY_H_