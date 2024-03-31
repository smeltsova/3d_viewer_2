#include <gtest/gtest.h>

#include "../model/parser.h"

TEST(ParserTest, Test1) {
  s21::FileReader* fileReader = s21::FileReader::getInstance();
  s21::ObjectData got = {};
  EXPECT_EQ(fileReader->parseObject("models/test1.obj", got), true);
  std::vector<float> v = {1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f};
  std::vector<unsigned> e = {};
  s21::ObjectData exp = {v, e, 2, 0, "test1.obj", {0}, {0}, 0};

  for (size_t i = 0; i < 6; i++) {
    EXPECT_FLOAT_EQ(exp.vertexArray[i], got.vertexArray[i]);
  }
  EXPECT_EQ(exp.vertexNumber, got.vertexNumber);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.name, got.name);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.maxCoord, got.maxCoord);
}

TEST(ParserTest, Test2) {
  s21::FileReader* fileReader = s21::FileReader::getInstance();
  s21::ObjectData got = {};

  EXPECT_EQ(fileReader->parseObject("models/test2.obj", got), true);

  std::vector<float> v = {};
  std::vector<unsigned> e = {1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 1, 2, 2, 3, 3, 1};
  for (int i = 0; i < 16; i++) e[i]--;
  s21::ObjectData exp = {v, e, 0, 8, "test2.obj", {0}, {0}, 0};

  for (size_t i = 0; i < 8; i++) {
    EXPECT_FLOAT_EQ(exp.edgesArray[i], got.edgesArray[i]);
  }
  EXPECT_EQ(exp.vertexNumber, got.vertexNumber);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.name, got.name);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.maxCoord, got.maxCoord);
}

TEST(ParserTest, Test3) {
  s21::FileReader* fileReader = s21::FileReader::getInstance();
  s21::ObjectData got = {};

  EXPECT_EQ(fileReader->parseObject("models/cube.obj", got), true);
  std::vector<float> v = {
      2,           -0.984852, 1.00842,   5.96046e-08, -0.984852, 1.00842,
      5.96046e-08, -0.984852, -0.991578, 5.96046e-08, 1.01515,   -0.991578,
      5.96046e-08, 1.01515,   1.00842,   2,           1.01515,   1.00842,
      2,           1.01515,   -0.991577, 2,           -0.984852, -0.991578};
  std::vector<unsigned> e = {
      1, 2, 2, 3, 3, 1, 4, 5, 5, 6, 6, 4, 7, 6, 6, 1, 1, 7, 6, 5, 5, 2, 2, 6,
      2, 5, 5, 4, 4, 2, 8, 3, 3, 4, 4, 8, 8, 1, 1, 3, 3, 8, 7, 4, 4, 6, 6, 7,
      8, 7, 7, 1, 1, 8, 1, 6, 6, 2, 2, 1, 3, 2, 2, 4, 4, 3, 7, 8, 8, 4, 4, 7};
  for (int i = 0; i < 72; i++) e[i]--;
  s21::ObjectData exp = {v, e, 24 / 3, 72 / 2, "cube.obj", {0}, {0}, 0};

  for (size_t i = 0; i < 24 / 3; i++) {
    EXPECT_FLOAT_EQ(exp.vertexArray[i], got.vertexArray[i]);
  }
  for (size_t i = 0; i < 72 / 2; i++) {
    EXPECT_FLOAT_EQ(exp.edgesArray[i], got.edgesArray[i]);
  }
  EXPECT_EQ(exp.vertexNumber, got.vertexNumber);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.name, got.name);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.maxCoord, got.maxCoord);
}

TEST(ParserTest, TestNothing) {
  s21::FileReader* fileReader = s21::FileReader::getInstance();
  s21::ObjectData got = {};

  EXPECT_EQ(fileReader->parseObject("models/nothing.obj", got), true);
  s21::ObjectData exp = {{}, {}, 0, 0, "nothing.obj", {0}, {0}, 0};

  EXPECT_EQ(exp.vertexArray.size(), 0);
  EXPECT_EQ(got.vertexArray.size(), 0);
  EXPECT_EQ(exp.edgesArray.size(), 0);
  EXPECT_EQ(got.edgesArray.size(), 0);
  EXPECT_EQ(exp.vertexNumber, got.vertexNumber);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.name, got.name);
  EXPECT_EQ(exp.edgesNumber, got.edgesNumber);
  EXPECT_EQ(exp.maxCoord, got.maxCoord);
}

TEST(ParserTest, TestNoFile) {
  s21::FileReader* fileReader = s21::FileReader::getInstance();
  s21::ObjectData got = {};

  EXPECT_EQ(fileReader->parseObject("nofile.obj", got), false);
}

// TEST(ParserTest, TestReadName) {
//   s21::FileReader* fileReader = s21::FileReader::getInstance();
//   char *got = NULL;

//   EXPECT_EQ(readName("some_file.obj", got), true);
//   EXPECT_EQ("some_file.obj", got);
//   if (got) free(got);
// }
