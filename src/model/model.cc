#include "model.h"

s21::Model::Model() {
  s21::Director dr;
  AllTransformationBuilder allBuilder;
  tr_ = dr.createTransformator( allBuilder );
  parser_ = FileReader::getInstance();
};

s21::Model::~Model() {
  delete tr_;
};

void s21::Model::translate(ObjectData &obj, float tx, float ty, float tz) {
  tr_->translation.transform(obj, tx, ty, tz);
}

void s21::Model::toCenter(ObjectData &obj) {
  tr_->translation.moveToCenter(obj);
}

void s21::Model::rotate(ObjectData &obj, float angle, char axis) {
  tr_->rotation.transform(obj, angle, axis);
}

void s21::Model::scale(ObjectData &obj, float Sx, float Sy, float Sz) {
  tr_->scaling.transform(obj, Sx, Sy, Sz);
}

bool s21::Model::parseObject(std::string filename, ObjectData &objectData) {
  return parser_->parseObject(filename, objectData);
}