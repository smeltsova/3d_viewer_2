#include <QApplication>

#include "model/model.h"
#include "controller/controller.h"
#include "view/myopenglwidget.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  s21::Model model;
  s21::Controller controller(model);
  s21::MainWindow w(controller);
  w.show();
  return a.exec();
}
