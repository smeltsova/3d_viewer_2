#ifndef SRC_GLVIEW_H_
#define SRC_GLVIEW_H_

#include <QMouseEvent>
#include <QFileDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "./QtGifImage/gifimage/qgifimage.h"

#include "../model/affinity.h"
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
    void setXTranslate(const QString &new_x);
    void setYTranslate(const QString &new_y);
    void setZTranslate(const QString &new_z);
    void setXRotate(const QString &new_x);
    void setYRotate(const QString &new_y);
    void setZRotate(const QString &new_z);
    void setXScale(const QString &new_x);
    void setYScale(const QString &new_y);
    void setZScale(const QString &new_z);

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
    Transformator *tr;
    float xRot = 0, yRot = 0, zRot = 0;
    float dx = 0, dy = 0, dz = 0;
    float xScale = 1, yScale = 1, zScale = 1;
    void initSettings();
    int vertex_size = 10;
    int edge_size = 1;
    int vertex_mode = 1;
    int edge_mode = 0;
    int projection_type = 0;
    void setupPerspective();
    void drawPoints();
    void drawLines();
  };
}

#endif // SRC_GLVIEW_H_
