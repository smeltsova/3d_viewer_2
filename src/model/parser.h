#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "object.h"

namespace s21 {

class FileReader {
 private:
  FileReader() {}
  FileReader(const FileReader &other) = delete;
  FileReader &operator=(const FileReader &other) = delete;

 public:
 ObjectData FileReader::parseObject(std::string filename);
 std::string readObjectName(const std::string& filename);

  //---------------------------
  int fillArrays(FILE *file, ObjectData *obj);
  int parsePoligon(char *line, ObjectData *obj);
  void free_ObjectData(ObjectData *obj);
};
}  // namespace s21

/**
 * Класс Одиночка предоставляет метод `GetInstance`, который ведёт себя как
 * альтернативный конструктор и позволяет клиентам получать один и тот же
 * экземпляр класса при каждом вызове.
 */
class Singleton {
  /**
   * Конструктор Одиночки всегда должен быть скрытым, чтобы предотвратить
   * создание объекта через оператор new.
   */

 protected:
  Singleton(const std::string value) : value_(value) {}

  static Singleton *singleton_;

  std::string value_;

 public:
  /**
   * Одиночки не должны быть клонируемыми.
   */
  Singleton(Singleton &other) = delete;
  /**
   * Singletons should not be assignable.
   */
  void operator=(const Singleton &) = delete;
  /**
   * Это статический метод, управляющий доступом к экземпляру одиночки. При
   * первом запуске, он создаёт экземпляр одиночки и помещает его в
   * статическое поле. При последующих запусках, он возвращает клиенту объект,
   * хранящийся в статическом поле.
   */

  static Singleton *GetInstance(const std::string &value);
  /**
   * Наконец, любой одиночка должен содержать некоторую бизнес-логику, которая
   * может быть выполнена на его экземпляре.
   */
  void SomeBusinessLogic() {
    // ...
  }

  std::string value() const { return value_; }
};

#endif  // SRC_MODEL_PARSER_H_