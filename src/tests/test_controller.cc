#include <gtest/gtest.h>

#include "../controller/controller.h"

TEST(ControllerTest, controller_test_1) {
  s21::Model model;
  s21::Controller controller(model);
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

  controller.translate(obj, 0.5f, 1.00f, -0.3f);
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], expectedResult[i]);
  }
}

TEST(ControllerTest, controller_test_2) {
  s21::Model model;
  s21::Controller controller(model);
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
  controller.rotate(obj, angle, 'x');
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

TEST(ControllerTest, controller_test_3) {
  s21::Model model;
  s21::Controller controller(model);
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
  controller.scale(obj, 0.5f, 1.00f, -0.5f);
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], expectedResult[i]);
  }
}

TEST(ControllerTest, controller_test_4) {
  s21::Model model;
  s21::Controller controller(model);
  s21::ObjectData obj = {};
  EXPECT_EQ(controller.parseObject("models/test3.obj", obj), true);

  controller.toCenter(obj);
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