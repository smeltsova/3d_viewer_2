#include "view.h"

#include "./ui_mainwindow.h"

s21::MainWindow::MainWindow(s21::Controller &controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3DViewer_v2.0");

  timer = new QTimer;
  image = new QImage[50]{};

  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
  this->settingFile = QApplication::applicationDirPath() + "/settings.conf";

  connectSetup();
  loadSettings();
  initColors();
}

s21::MainWindow::~MainWindow() {
  setSettings();
  delete timer;
  delete[] image;
  delete ui;
}

void s21::MainWindow::connectSetup() {
  connect(ui->doubleSpinBox_translate_x, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setXTranslate);
  connect(ui->doubleSpinBox_translate_y, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setYTranslate);
  connect(ui->doubleSpinBox_translate_z, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setZTranslate);

  connect(ui->doubleSpinBox_rotate_x, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setXRotate);
  connect(ui->doubleSpinBox_rotate_y, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setYRotate);
  connect(ui->doubleSpinBox_rotate_z, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setZRotate);

  connect(ui->doubleSpinBox_scale_x, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setXScale);
  connect(ui->doubleSpinBox_scale_y, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setYScale);
  connect(ui->doubleSpinBox_scale_z, &QDoubleSpinBox::textChanged, this,
          &MainWindow::setZScale);

  connect(ui->horizontalScrollBar_size_v, &QScrollBar::valueChanged, ui->widget,
          &MyOpenGLWidget::changePointSize);
  connect(ui->horizontalScrollBar_size_e, &QScrollBar::valueChanged, ui->widget,
          &MyOpenGLWidget::changeLineSize);
}

void s21::MainWindow::on_pushButton_file_clicked() {
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr("(*.obj)"));
  QByteArray q_path = file.toLocal8Bit();
  char *result_path = q_path.data();
  ui->widget->obj.clear();
  resetPosition();
  if (controller_.parseObject(result_path, ui->widget->obj)) {
    ui->widget->fileopen = 1;
    ui->label_v_number->setText(QString::number(ui->widget->obj.vertexNumber));
    ui->label_e_number->setText(QString::number(ui->widget->obj.edgesNumber));
    ui->label_file->setText(QString::fromStdString(ui->widget->obj.name));
    ui->statusbar->showMessage(file);
    controller_.toCenter(ui->widget->obj);
    ui->horizontalScrollBar_translate_x->setMaximum(
        2 * round(1 + ui->widget->obj.maxCoord) * 10);
    ui->horizontalScrollBar_translate_x->setMinimum(
        -2 * round(1 + ui->widget->obj.maxCoord) * 10);
    ui->horizontalScrollBar_translate_y->setMaximum(
        2 * round(1 + ui->widget->obj.maxCoord) * 10);
    ui->horizontalScrollBar_translate_y->setMinimum(
        -2 * round(1 + ui->widget->obj.maxCoord) * 10);
    ui->horizontalScrollBar_translate_z->setMaximum(
        2 * round(1 + ui->widget->obj.maxCoord) * 10);
    ui->horizontalScrollBar_translate_z->setMinimum(
        -2 * round(1 + ui->widget->obj.maxCoord) * 10);
    // ui->widget->obj.print_object();
  } else {
    ui->widget->fileopen = 0;
    ui->label_v_number->setText("0");
    ui->label_e_number->setText("0");
    ui->label_file->setText("-");
    ui->statusbar->clearMessage();
  }
  ui->widget->update();
}

void s21::MainWindow::resetPosition() {
  ui->doubleSpinBox_translate_x->setValue(0);
  ui->doubleSpinBox_translate_y->setValue(0);
  ui->doubleSpinBox_translate_z->setValue(0);

  ui->doubleSpinBox_rotate_x->setValue(0);
  ui->doubleSpinBox_rotate_y->setValue(0);
  ui->doubleSpinBox_rotate_z->setValue(0);

  ui->doubleSpinBox_scale_x->setValue(1);
  ui->doubleSpinBox_scale_y->setValue(1);
  ui->doubleSpinBox_scale_z->setValue(1);
}

void s21::MainWindow::on_horizontalScrollBar_translate_x_valueChanged(
    int value) {
  ui->doubleSpinBox_translate_x->setValue(value / 10.0);
}

void s21::MainWindow::on_horizontalScrollBar_translate_y_valueChanged(
    int value) {
  ui->doubleSpinBox_translate_y->setValue(value / 10.0);
}

void s21::MainWindow::on_horizontalScrollBar_translate_z_valueChanged(
    int value) {
  ui->doubleSpinBox_translate_z->setValue(value / 10.0);
}

void s21::MainWindow::on_horizontalScrollBar_rotate_x_valueChanged(int value) {
  ui->doubleSpinBox_rotate_x->setValue(value);
}

void s21::MainWindow::on_horizontalScrollBar_rotate_y_valueChanged(int value) {
  ui->doubleSpinBox_rotate_y->setValue(value);
}

void s21::MainWindow::on_horizontalScrollBar_rotate_z_valueChanged(int value) {
  ui->doubleSpinBox_rotate_z->setValue(value);
}

void s21::MainWindow::on_horizontalScrollBar_scale_x_valueChanged(int value) {
  ui->doubleSpinBox_scale_x->setValue(value / 100.0);
}

void s21::MainWindow::on_horizontalScrollBar_scale_y_valueChanged(int value) {
  ui->doubleSpinBox_scale_y->setValue(value / 100.0);
}

void s21::MainWindow::on_horizontalScrollBar_scale_z_valueChanged(int value) {
  ui->doubleSpinBox_scale_z->setValue(value / 100.0);
}

void s21::MainWindow::on_doubleSpinBox_translate_x_valueChanged(double arg1) {
  ui->horizontalScrollBar_translate_x->setValue(round(arg1 * 10));
}

void s21::MainWindow::on_doubleSpinBox_translate_y_valueChanged(double arg1) {
  ui->horizontalScrollBar_translate_y->setValue(round(arg1 * 10));
}

void s21::MainWindow::on_doubleSpinBox_translate_z_valueChanged(double arg1) {
  ui->horizontalScrollBar_translate_z->setValue(round(arg1 * 10));
}

void s21::MainWindow::on_doubleSpinBox_rotate_x_valueChanged(double arg1) {
  ui->horizontalScrollBar_rotate_x->setValue(arg1);
}

void s21::MainWindow::on_doubleSpinBox_rotate_y_valueChanged(double arg1) {
  ui->horizontalScrollBar_rotate_y->setValue(arg1);
}

void s21::MainWindow::on_doubleSpinBox_rotate_z_valueChanged(double arg1) {
  ui->horizontalScrollBar_rotate_z->setValue(arg1);
}

void s21::MainWindow::on_doubleSpinBox_scale_x_valueChanged(double arg1) {
  ui->horizontalScrollBar_scale_x->setValue(round(arg1 * 100));
  if (ui->checkBox_scale->isChecked()) {
    ui->doubleSpinBox_scale_y->setValue(arg1);
    ui->doubleSpinBox_scale_z->setValue(arg1);
  }
}

void s21::MainWindow::on_doubleSpinBox_scale_y_valueChanged(double arg1) {
  ui->horizontalScrollBar_scale_y->setValue(round(arg1 * 100));
  if (ui->checkBox_scale->isChecked()) {
    ui->doubleSpinBox_scale_x->setValue(arg1);
    ui->doubleSpinBox_scale_z->setValue(arg1);
  }
}

void s21::MainWindow::on_doubleSpinBox_scale_z_valueChanged(double arg1) {
  ui->horizontalScrollBar_scale_z->setValue(round(arg1 * 100));
  if (ui->checkBox_scale->isChecked()) {
    ui->doubleSpinBox_scale_x->setValue(arg1);
    ui->doubleSpinBox_scale_y->setValue(arg1);
  }
}

void s21::MainWindow::on_radioButton_none_pressed() {
  ui->widget->changeVertexMode(0);
}

void s21::MainWindow::on_radioButton_circle_pressed() {
  ui->widget->changeVertexMode(1);
}

void s21::MainWindow::on_radioButton_square_pressed() {
  ui->widget->changeVertexMode(2);
}

void s21::MainWindow::on_radioButton_solid_pressed() {
  ui->widget->changeEdgeMode(0);
}

void s21::MainWindow::on_radioButton_dashed_pressed() {
  ui->widget->changeEdgeMode(1);
}

void s21::MainWindow::on_radioButton_parallel_pressed() {
  ui->widget->changeProjectionType(0);
}

void s21::MainWindow::on_radioButton_central_pressed() {
  ui->widget->changeProjectionType(1);
}

void s21::MainWindow::setXTranslate(const QString &new_x) {
  float new_dx = new_x.toFloat();
  controller_.translate(ui->widget->obj, new_dx - ui->widget->getDx(), 0, 0);
  ui->widget->setDx(new_dx);
  ui->widget->update();
}

void s21::MainWindow::setYTranslate(const QString &new_y) {
  float new_dy = new_y.toFloat();
  controller_.translate(ui->widget->obj, 0, new_dy - ui->widget->getDy(), 0);
  ui->widget->setDy(new_dy);
  ui->widget->update();
}

void s21::MainWindow::setZTranslate(const QString &new_z) {
  float new_dz = new_z.toFloat();
  controller_.translate(ui->widget->obj, 0, 0, new_dz - ui->widget->getDz());
  ui->widget->setDz(new_dz);
  ui->widget->update();
}

void s21::MainWindow::setXRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  controller_.rotate(ui->widget->obj, new_deg - ui->widget->getXRot(), 'x');
  ui->widget->setXRot(new_deg);
  ui->widget->update();
}

void s21::MainWindow::setYRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  controller_.rotate(ui->widget->obj, new_deg - ui->widget->getYRot(), 'y');
  ui->widget->setYRot(new_deg);
  ui->widget->update();
}

void s21::MainWindow::setZRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  controller_.rotate(ui->widget->obj, new_deg - ui->widget->getZRot(), 'z');
  ui->widget->setZRot(new_deg);
  ui->widget->update();
}

void s21::MainWindow::setXScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    controller_.scale(ui->widget->obj, new_scale / ui->widget->getXScale(), 1,
                      1);
    ui->widget->setXScale(new_scale);
    ui->widget->update();
  }
}

void s21::MainWindow::setYScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    controller_.scale(ui->widget->obj, 1, new_scale / ui->widget->getYScale(),
                      1);
    ui->widget->setYScale(new_scale);
    ui->widget->update();
  }
}

void s21::MainWindow::setZScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    controller_.scale(ui->widget->obj, 1, 1,
                      new_scale / ui->widget->getZScale());
    ui->widget->setZScale(new_scale);
    ui->widget->update();
  }
}

void s21::MainWindow::on_pushButton_change_color_vertices_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->widget->vertexColor = color;
    ui->graphicsView_v->setStyleSheet(
        QString("background-color: rgb(%1, %2, %3);")
            .arg(ui->widget->vertexColor.red())
            .arg(ui->widget->vertexColor.green())
            .arg(ui->widget->vertexColor.blue()));

    ui->widget->update();
  }
}

void s21::MainWindow::on_pushButton_change_color_edges_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->widget->edgeColor = color;
    ui->graphicsView_e->setStyleSheet(
        QString("background-color: rgb(%1, %2, %3);")
            .arg(ui->widget->edgeColor.red())
            .arg(ui->widget->edgeColor.green())
            .arg(ui->widget->edgeColor.blue()));
    ui->widget->update();
  }
}

void s21::MainWindow::on_pushButton_change_color_edges_2_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->widget->backgroundColor = color;
    ui->graphicsView_b->setStyleSheet(
        QString("background-color: rgb(%1, %2, %3);")
            .arg(ui->widget->backgroundColor.red())
            .arg(ui->widget->backgroundColor.green())
            .arg(ui->widget->backgroundColor.blue()));
    ui->widget->update();
  }
}

void s21::MainWindow::on_pushButton_reset_clicked() {
  ui->doubleSpinBox_translate_x->setValue(0);
  ui->doubleSpinBox_translate_y->setValue(0);
  ui->doubleSpinBox_translate_z->setValue(0);

  ui->doubleSpinBox_rotate_x->setValue(0);
  ui->doubleSpinBox_rotate_y->setValue(0);
  ui->doubleSpinBox_rotate_z->setValue(0);

  ui->doubleSpinBox_scale_x->setValue(1);
  ui->doubleSpinBox_scale_y->setValue(1);
  ui->doubleSpinBox_scale_z->setValue(1);

  ui->horizontalScrollBar_size_e->setValue(1);
  ui->horizontalScrollBar_size_v->setValue(10);

  ui->checkBox_scale->setChecked(false);
  ui->radioButton_circle->setChecked(true);
  ui->radioButton_solid->setChecked(true);
  ui->radioButton_parallel->setChecked(true);

  ui->radioButton_circle->pressed();
  ui->radioButton_solid->pressed();
  ui->radioButton_parallel->pressed();

  ui->widget->backgroundColor = QColorConstants::Black;
  ui->widget->edgeColor = QColorConstants::Green;
  ui->widget->vertexColor = QColorConstants::Red;
  initColors();

  QString file = ui->statusbar->currentMessage();
  QByteArray q_path = file.toLocal8Bit();
  char *result_path = q_path.data();
  ui->widget->obj.clear();
  if (controller_.parseObject(result_path, ui->widget->obj)) {
    controller_.toCenter(ui->widget->obj);
  } else {
    ui->widget->fileopen = 0;
    ui->statusbar->clearMessage();
  }
}

void s21::MainWindow::initColors() {
  ui->graphicsView_v->setStyleSheet(
      QString("background-color: rgb(%1, %2, %3);")
          .arg(ui->widget->vertexColor.red())
          .arg(ui->widget->vertexColor.green())
          .arg(ui->widget->vertexColor.blue()));
  ui->graphicsView_e->setStyleSheet(
      QString("background-color: rgb(%1, %2, %3);")
          .arg(ui->widget->edgeColor.red())
          .arg(ui->widget->edgeColor.green())
          .arg(ui->widget->edgeColor.blue()));
  ui->graphicsView_b->setStyleSheet(
      QString("background-color: rgb(%1, %2, %3);")
          .arg(ui->widget->backgroundColor.red())
          .arg(ui->widget->backgroundColor.green())
          .arg(ui->widget->backgroundColor.blue()));
}

void s21::MainWindow::setSettings() {
  QSettings settings(settingFile, QSettings::IniFormat);

  settings.beginGroup("Vertices");
  settings.setValue("circle", ui->radioButton_circle->isChecked());
  settings.setValue("square", ui->radioButton_square->isChecked());
  settings.setValue("none", ui->radioButton_none->isChecked());

  settings.setValue("size", ui->horizontalScrollBar_size_v->value());

  settings.setValue("color_1", ui->widget->vertexColor);
  settings.endGroup();

  settings.beginGroup("Edges");
  settings.setValue("solid", ui->radioButton_solid->isChecked());
  settings.setValue("dashed", ui->radioButton_dashed->isChecked());

  settings.setValue("thickness", ui->horizontalScrollBar_size_e->value());

  settings.setValue("color_2", ui->widget->edgeColor);
  settings.endGroup();

  settings.beginGroup("Background");
  settings.setValue("color_3", ui->widget->backgroundColor);

  settings.setValue("parallel", ui->radioButton_parallel->isChecked());
  settings.setValue("central", ui->radioButton_central->isChecked());
  settings.endGroup();
}

void s21::MainWindow::loadSettings() {
  if (QFile::exists(settingFile)) {
    QSettings settings(settingFile, QSettings::IniFormat);

    settings.beginGroup("Vertices");
    if (settings.value("circle").toBool()) {
      ui->radioButton_circle->setChecked(true);
      ui->widget->changeVertexMode(1);
    } else if (settings.value("square").toBool()) {
      ui->radioButton_square->setChecked(true);
      ui->widget->changeVertexMode(2);
    } else if (settings.value("none").toBool()) {
      ui->radioButton_none->setChecked(true);
      ui->widget->changeVertexMode(0);
    }
    ui->horizontalScrollBar_size_v->setValue(settings.value("size").toInt());
    ui->widget->vertexColor = settings.value("color_1").toString();
    settings.endGroup();

    settings.beginGroup("Edges");
    if (settings.value("solid").toBool()) {
      ui->radioButton_solid->setChecked(true);
      ui->widget->changeEdgeMode(0);
    } else if (settings.value("dashed").toBool()) {
      ui->radioButton_dashed->setChecked(true);
      ui->widget->changeEdgeMode(1);
    }
    ui->horizontalScrollBar_size_e->setValue(
        settings.value("thickness").toInt());
    ui->widget->edgeColor = settings.value("color_2").toString();
    settings.endGroup();

    settings.beginGroup("Background");
    ui->widget->backgroundColor = settings.value("color_3").toString();
    if (settings.value("parallel").toBool()) {
      ui->radioButton_parallel->setChecked(true);
      ui->widget->changeProjectionType(0);
    } else if (settings.value("central").toBool()) {
      ui->radioButton_central->setChecked(true);
      ui->widget->changeProjectionType(1);
    }
    settings.endGroup();
  }
}

void s21::MainWindow::on_pushButton_screenshot_clicked() {
  QDateTime date = date.currentDateTime();
  QString current_date = date.toString("dd.MM.yy_HH.mm");
  QString file = QFileDialog::getSaveFileName(this, "Save as...",
                                              "Screenshot_" + current_date,
                                              "BMP (*.bmp);;JPEG (*.jpeg)");
  ui->widget->grabFramebuffer().save(file);
}

void s21::MainWindow::on_pushButton_gif_clicked() {
  ui->pushButton_gif->setEnabled(false);
  timer->start(100);
}

void s21::MainWindow::slotTimer() {
  if (frame_count < 50) {
    image[frame_count] = ui->widget->grabFramebuffer();
    ++frame_count;
  } else {
    gif = new QGifImage;
    for (int i = 0; i < frame_count; ++i) {
      gif->addFrame(image[i].scaled(640, 480, Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation),
                    0);
    }
    QDateTime date = date.currentDateTime();
    QString current_date = date.toString("dd.MM.yy_HH.mm");
    QString file = QFileDialog::getSaveFileName(
        this, "Save GIF", "GIF_" + current_date, "GIF (*.gif)");
    gif->save(file);
    ui->pushButton_gif->setEnabled(true);
    timer->stop();
    frame_count = 0;
  }
}
