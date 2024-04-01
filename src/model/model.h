#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "affinity.h"
#include "object.h"
#include "parser.h"

namespace s21 {
/**
 * @brief Representation of the MVC pattern model for a 3DViewer_2.0 project
 *
 */
class Model {
 public:
  Model();
  ~Model();

  void translate(ObjectData &obj, float tx, float ty, float tz);
  void toCenter(ObjectData &obj);
  void rotate(ObjectData &obj, float angle, char axis);
  void scale(ObjectData &obj, float Sx, float Sy, float Sz);
  bool parseObject(std::string filename, ObjectData &objectData);

 private:
  s21::Transformator *tr_;
  s21::FileReader *parser_;
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_