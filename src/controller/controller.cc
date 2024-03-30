#include "controller/controller.h"

void s21::Controller::translate(ObjectData &obj, float tx, float ty, float tz) {
  model_.translate(obj, tx, ty, tz);
}

void s21::Controller::toCenter(ObjectData &obj) {
  model_.toCenter(obj);
}

void s21::Controller::rotate(ObjectData &obj, float angle, char axis) {
  model_.rotate(obj, angle, axis);
}

void s21::Controller::scale(ObjectData &obj, float Sx, float Sy, float Sz) {
  model_.scale(obj, Sx, Sy, Sz);
}

bool s21::Controller::parseObject(std::string filename, ObjectData &objectData) {
  return model_.parseObject(filename, objectData);
}