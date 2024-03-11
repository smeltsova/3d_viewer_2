#include <gtest/gtest.h>
#include "../model/affinity.h"

TEST(AffinityTest, AffinityTranslateTest) {
  s21::ObjectData obj = {};
  std::array<float, 12> vertexModel = {0.4f,  1.2f,  0.98f, 1.1f,  1.22f, 1.5f,
                          0.06f, 0.07f, 0.3f,  21.2f, 34.6f, 23.8f};
  for (float var : vertexModel) {
    obj.vertexArray.push_back(var);
  }
  obj.vertexNumber = 4;
  std::array<float, 12> expectedResult = {0.9f,  2.2f,  0.68f, 1.6f,  2.22f, 1.2f,
                          0.56f, 1.07f, 0.00f, 21.7f, 35.6f, 23.5f};
  
  s21::Director dr;
  s21::AllTransformationBuilder allBuilder;
  s21::Transformator *tr = dr.createTransformator(allBuilder);
  tr->translation.transform(obj, 0.5f, 1.00f, -0.3f);
  for (size_t i = 0; i < 12; ++i) {
    EXPECT_FLOAT_EQ(obj.vertexArray[i], expectedResult[i]);
  }
}

TEST(AffinityTest, AffinityRotateX) {
  
}
