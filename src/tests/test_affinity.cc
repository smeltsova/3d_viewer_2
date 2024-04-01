#include <gtest/gtest.h>

#include "../model/affinity.h"
#include "../model/parser.h"

TEST(AffinityTest, AffinityTranslateTest) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,
                                       1.22f, 1.5f,  0.06f, 0.07f,
                                       0.3f,  21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.9f,  2.2f,  0.68f, 1.6f,
                                          2.22f, 1.2f,  0.56f, 1.07f,
                                          0.00f, 21.7f, 35.6f, 23.5f};

  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->translation.transform(obj, 0.5f, 1.00f, -0.3f);
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], expectedResult[i]);
  }
}

TEST(AffinityTest, AffinityRotateX) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,
                                       1.22f, 1.5f,  0.06f, 0.07f,
                                       0.03f, 21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.4f,  1.2f,  0.98f, 1.1f,
                                          1.22f, 1.5f,  0.06f, 0.07f,
                                          0.03f, 21.2f, 34.6f, 23.8f};
  float angle = 90.0f;
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->rotation.transform(obj, angle, 'x');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < obj.vertexNumber * 3; i += 3) {
    float y = expectedResult[i + 1];
    float z = expectedResult[i + 2];
    float waitValue1 = y * cos(angle) - z * sin(angle);
    float waitValue2 = y * sin(angle) + z * cos(angle);

    EXPECT_FLOAT_EQ(obj.vertexArray[i + 1], waitValue1);
    EXPECT_FLOAT_EQ(obj.vertexArray[i + 2], waitValue2);
  }
}

TEST(AffinityTest, AffinityRotateY) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,
                                       1.22f, 1.5f,  0.06f, 0.07f,
                                       0.03f, 21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.4f,  1.2f,  0.98f, 1.1f,
                                          1.22f, 1.5f,  0.06f, 0.07f,
                                          0.03f, 21.2f, 34.6f, 23.8f};
  float angle = 90.0f;
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->rotation.transform(obj, angle, 'y');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < obj.vertexNumber * 3; i += 3) {
    float x = expectedResult[i];
    float z = expectedResult[i + 2];
    float waitValue1 = x * cos(angle) + z * sin(angle);
    float waitValue2 = -x * sin(angle) + z * cos(angle);

    EXPECT_FLOAT_EQ(obj.vertexArray[i], waitValue1);
    EXPECT_FLOAT_EQ(obj.vertexArray[i + 2], waitValue2);
  }
}

TEST(AffinityTest, AffinityRotateZ) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,
                                       1.22f, 1.5f,  0.06f, 0.07f,
                                       0.03f, 21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.4f,  1.2f,  0.98f, 1.1f,
                                          1.22f, 1.5f,  0.06f, 0.07f,
                                          0.03f, 21.2f, 34.6f, 23.8f};
  float angle = 90.0f;
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->rotation.transform(obj, angle, 'z');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < obj.vertexNumber * 3; i += 3) {
    float x = expectedResult[i];
    float y = expectedResult[i + 1];
    float waitValue1 = x * cos(angle) - y * sin(angle);
    float waitValue2 = x * sin(angle) + y * cos(angle);

    EXPECT_FLOAT_EQ(obj.vertexArray[i], waitValue1);
    EXPECT_FLOAT_EQ(obj.vertexArray[i + 1], waitValue2);
  }
}

TEST(AffinityTest, AffinityScaling) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,
                                       1.22f, 1.5f,  0.06f, 0.07f,
                                       0.03f, 21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.2f,    1.2f,   -0.49f, 0.55f,
                                          1.22f,   -0.75f, 0.03f,  0.07f,
                                          -0.015f, 10.6f,  34.6f,  -11.9f};

  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->scaling.transform(obj, 0.5f, 1.00f, -0.5f);
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], expectedResult[i]);
  }
}

TEST(AffinityTest, AffinityMoveToCenter_1) {
  s21::ObjectData obj = {};
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  s21::FileReader *parser = s21::FileReader::getInstance();
  EXPECT_EQ(parser->parseObject("models/test3.obj", obj), true);

  tr->translation.moveToCenter(obj);
  EXPECT_FLOAT_EQ(obj.maxCoord, 1.1);

  std::vector<float> v = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  std::vector<unsigned> e = {0, 1, 1, 2, 2, 3, 3, 0};
  s21::ObjectData exp = {v, e, 4, 4, "test3.obj", {0}, {0}, 0};

  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], exp.vertexArray[i]);
  }
  for (size_t i = 0; i < 8; ++i) {
    EXPECT_EQ(obj.edgesArray[i], exp.edgesArray[i]);
  }
}

TEST(AffinityTest, AffinityMoveToCenter_2) {
  s21::ObjectData obj = {};
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  s21::FileReader *parser = s21::FileReader::getInstance();
  EXPECT_EQ(parser->parseObject("models/nothing.obj", obj), true);

  tr->translation.moveToCenter(obj);
  EXPECT_FLOAT_EQ(obj.maxCoord, 0);

  EXPECT_EQ(obj.vertexArray.size(), 0lu);
  EXPECT_EQ(obj.edgesArray.size(), 0lu);
}