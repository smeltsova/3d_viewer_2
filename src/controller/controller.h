#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(s21::Model &model) : model_(model){};
  ~Controller(){};

  void translate(ObjectData &obj, float tx, float ty, float tz);
  void toCenter(ObjectData &obj);
  void rotate(ObjectData &obj, float angle, char axis);
  void scale(ObjectData &obj, float Sx, float Sy, float Sz);

  bool parseObject(std::string filename, ObjectData &objectData);

 private:
  s21::Model &model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_