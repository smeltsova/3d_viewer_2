#ifndef SRC_GLVIEW_H_
#define SRC_GLVIEW_H_

#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <algorithm>

#include "../controller/controller.h"
#include "../model/affinity.h"
#include "./QtGifImage/gifimage/qgifimage.h"
// #include "../model/parser.h"

namespace s21 {
class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  int fileopen = 0;
  ObjectData obj = {};
  QColor backgroundColor = QColorConstants::Black;
  QColor edgeColor = QColorConstants::Green;
  QColor vertexColor = QColorConstants::Red;

  void setDx(float value);
  void setDy(float value);
  void setDz(float value);
  float getDx();
  float getDy();
  float getDz();

  void setXRot(float value);
  void setYRot(float value);
  void setZRot(float value);
  float getXRot();
  float getYRot();
  float getZRot();

  void setXScale(float value);
  void setYScale(float value);
  void setZScale(float value);
  float getXScale();
  float getYScale();
  float getZScale();

  void changePointSize(int size);
  void changeLineSize(int size);
  void changeVertexMode(int mode);
  void changeEdgeMode(int mode);
  void changeProjectionType(int type);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  float xRot = 0, yRot = 0, zRot = 0;
  float dx = 0, dy = 0, dz = 0;
  float xScale = 1, yScale = 1, zScale = 1;
  int vertex_size = 10;
  int edge_size = 1;
  int vertex_mode = 1;
  int edge_mode = 0;
  int projection_type = 0;
  void initSettings();
  void setupPerspective();
  void drawPoints();
  void drawLines();
};
}  // namespace s21

#endif  // SRC_GLVIEW_H_
