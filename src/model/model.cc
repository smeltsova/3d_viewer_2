#include "model.h"

s21::Model::Model() {
  s21::Director dr;
  AllTransformationBuilder allBuilder;
  tr_ = dr.createTransformator(allBuilder);
  parser_ = FileReader::getInstance();
};

s21::Model::~Model(){};

/**
 * @brief A method for translation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param tx - rotation coordinate
 * @param ty - rotation coordinate
 * @param tz - rotation coordinate
 */
void s21::Model::translate(ObjectData &obj, float tx, float ty, float tz) {
  tr_->translation.transform(obj, tx, ty, tz);
}

/**
 * @brief The method for centering the object
 *
 * @param obj - representation of data about an `.obj` file
 */
void s21::Model::toCenter(ObjectData &obj) {
  tr_->translation.moveToCenter(obj);
}

/**
 * @brief A method for rotation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param angle - the angle of rotation
 * @param axis - the axis of rotation
 */
void s21::Model::rotate(ObjectData &obj, float angle, char axis) {
  tr_->rotation.transform(obj, angle, axis);
}

/**
 * @brief A method for scaling an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param Sx - the scale on the x-axis
 * @param Sy - the scale on the y-axis
 * @param Sz - the scale on the z-axis
 */
void s21::Model::scale(ObjectData &obj, float Sx, float Sy, float Sz) {
  tr_->scaling.transform(obj, Sx, Sy, Sz);
}

/**
 * @brief A method for parsing an object file
 *
 * @param filename - the path to the file
 * @param objectData - representation of data about an `.obj` file
 * @return true - if the parsing is successful
 * @return false - if the parsing is failed
 */
bool s21::Model::parseObject(std::string filename, ObjectData &objectData) {
  return parser_->parseObject(filename, objectData);
}