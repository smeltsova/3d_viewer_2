/**
 * @file affinity.h
 * @author corbrayr (corbrayr@student.21-school.ru)
 * @brief a module for performing affine
 * transformations using the builder pattern
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

namespace s21
{
  /**
   * @brief The class contains methods for performing translation
   */
  class Translation
  {
  public:
    void transform(ObjectData &obj, float tx, float ty, float tz);
    float moveToCenter(ObjectData &obj);
    void findMinMax(ObjectData &obj);
  };

  /**
   * @brief The class contains methods for performing rotation
   */
  class Rotation
  {
  public:
    void transform(ObjectData &obj, float angle, char axis);
  };

  /**
   * @brief The class contains methods for performing scaling
   */
  class Scaling
  {
  public:
    void transform(ObjectData &obj, float Sx, float Sy, float Sz);
  };

  /**
   * @brief The class contains objects for affine transformations
   */
  class Transformator
  {
  public:
    Translation translation;
    Rotation rotation;
    Scaling scaling;
  };

  /**
   * @brief Implementation of the builder pattern
   * allows you to define a set of transformation objects
   */
  class TransformatorBuilder
  {
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

  /**
   * @brief A frequent builder that contains all the conversion objects
   */
  class AllTransformationBuilder : public TransformatorBuilder
  {
  public:
    void createTransformator() { transformator = new Transformator; };
    void buildTranslation() { transformator->translation = Translation(); };
    void buildRotation() { transformator->rotation = Rotation(); };
    void buildScaling() { transformator->scaling = Scaling(); };
  };

  /**
   * @brief A class that allows you to use a private builder
   */
  class Director
  {
  public:
    Transformator *createTransformator(TransformatorBuilder &builder)
    {
      builder.createTransformator();
      builder.buildTranslation();
      builder.buildRotation();
      builder.buildScaling();
      return (builder.getTransformator());
    }
  };
} // namespace s21

/*
 * `A simple example to use module`
 * Director dr;
 * AllTransformationBuilder allBuilder;
 * Transformator *tr = dir.createTransformator( allBuilder );
 * tr->translation.transform(obj, x, y, z);
 * tr->rotation.transform(obj, angle, axis);
 * tr->scaling.transform(obj, Sx, Sy, Sz);
 */

#endif // SRC_MODEL_AFFINITY_H_