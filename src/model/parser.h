#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#include "object.h"

namespace s21
{

  class FileReader
  {
  private:
    FileReader() {}
    FileReader(const FileReader &) = delete;
    FileReader &operator=(const FileReader &) = delete;

    inline static FileReader *instance = nullptr;
    std::ifstream file_{};

  public:
    static FileReader *getInstance();
    bool parseObject(std::string filename, ObjectData &objectData);
    std::string readObjectName(const std::string &filename);
    void parseVerticesAndFaces(ObjectData &objectData);
    void parseVertex(std::istringstream &iss, ObjectData &objectData);
    void parseFace(std::istringstream &iss, ObjectData &objectData);
  };
} // namespace s21

#endif // SRC_MODEL_PARSER_H_