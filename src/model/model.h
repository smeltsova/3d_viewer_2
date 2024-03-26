#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "object.h"
#include "affinity.h"
// #include "parser.h"

namespace s21 {
  class Model {
    public:
      Model();
      ~Model();

      void translate(ObjectData &obj, float tx, float ty, float tz);
      void toCenter(ObjectData &obj);
      void rotate(ObjectData &obj, float angle, char axis);
      void scale(ObjectData &obj, float Sx, float Sy, float Sz);

    private:
      s21::Transformator *tr_;
      // s21::Parser parser_;
  };
}

#endif // SRC_MODEL_MODEL_H_