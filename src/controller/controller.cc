#include "controller.h"

/**
 * @brief A method for translation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param tx - rotation coordinate
 * @param ty - rotation coordinate
 * @param tz - rotation coordinate
 */
void s21::Controller::translate(ObjectData &obj, float tx, float ty, float tz) {
  model_.translate(obj, tx, ty, tz);
}

/**
 * @brief The method for centering the object
 *
 * @param obj - representation of data about an `.obj` file
 */
void s21::Controller::toCenter(ObjectData &obj) { model_.toCenter(obj); }

/**
 * @brief A method for rotation an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param angle - the angle of rotation
 * @param axis - the axis of rotation
 */
void s21::Controller::rotate(ObjectData &obj, float angle, char axis) {
  model_.rotate(obj, angle, axis);
}

/**
 * @brief A method for scaling an object
 *
 * @param obj - representation of data about an `.obj` file
 * @param Sx - the scale on the x-axis
 * @param Sy - the scale on the y-axis
 * @param Sz - the scale on the z-axis
 */
void s21::Controller::scale(ObjectData &obj, float Sx, float Sy, float Sz) {
  model_.scale(obj, Sx, Sy, Sz);
}

/**
 * @brief A method for parsing an object file
 *
 * @param filename - the path to the file
 * @param objectData - representation of data about an `.obj` file
 * @return true - if the parsing is successful
 * @return false - if the parsing is failed
 */
bool s21::Controller::parseObject(std::string filename,
                                  ObjectData &objectData) {
  return model_.parseObject(filename, objectData);
}