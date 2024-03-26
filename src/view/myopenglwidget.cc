#include "myopenglwidget.h"

// s21::MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
//   Director dr;
//   AllTransformationBuilder allBuilder;
//   trObject = dr.createTransformator( allBuilder );
// }

// s21::MyOpenGLWidget::~MyOpenGLWidget() {
//   obj.freeObject();
//   delete trObject;
// }

void s21::MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
}

void s21::MyOpenGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setupPerspective();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (fileopen) {
    glVertexPointer(3, GL_FLOAT, 0, &obj.vertexArray);
    glEnableClientState(GL_VERTEX_ARRAY);
    drawPoints();
    drawLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void s21::MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type == 0) {
    glOrtho(-1, 1, -1, 1, 1, 3);
  } else if (projection_type == 1) {
    glFrustum(-1, 1, -1, 1, 1, 3);
  }
}

void s21::MyOpenGLWidget::setupPerspective() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection_type == 0) {
    glOrtho(-obj.maxCoord, obj.maxCoord, -obj.maxCoord, obj.maxCoord,
            -2 * obj.maxCoord, obj.maxCoord * 5);
  } else if (projection_type == 1) {
    GLdouble zNear = 0.01;
    GLdouble zFar = obj.maxCoord * 10;
    GLdouble fovY = 60;
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    glTranslatef(0, 0, -2.5 * obj.maxCoord);
  }
}

void s21::MyOpenGLWidget::drawPoints() {
  if (vertex_mode != 0) {
    if (vertex_mode == 1) glEnable(GL_POINT_SMOOTH);
    glPointSize(vertex_size);
    glColor3d(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glDrawArrays(GL_POINTS, 0, obj.vertexNumber);
    if (vertex_mode == 1) glDisable(GL_POINT_SMOOTH);
  }
}
void s21::MyOpenGLWidget::drawLines() {
  if (edge_mode == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }
  glColor3d(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
  glLineWidth(edge_size);
  glDrawElements(GL_LINES, 2 * obj.edgesNumber, GL_UNSIGNED_INT,
                 &obj.edgesArray);
  if (edge_mode == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void s21::MyOpenGLWidget::changePointSize(int size) {
  vertex_size = size;
  update();
}

void s21::MyOpenGLWidget::changeLineSize(int size) {
  edge_size = size;
  update();
}

void s21::MyOpenGLWidget::changeVertexMode(int mode) {
  vertex_mode = mode;
  update();
}

void s21::MyOpenGLWidget::changeEdgeMode(int mode) {
  edge_mode = mode;
  update();
}

void s21::MyOpenGLWidget::changeProjectionType(int type) {
  projection_type = type;
  update();
}
