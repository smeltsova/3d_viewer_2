
#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "./QtGifImage/gifimage/qgifimage.h"

// #include "../model/affinity.h"
// // #include "../model/parser.h"
#include "../controller/controller.h"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21
{
  class MainWindow : public QMainWindow
  {
    Q_OBJECT

  public:
    MainWindow(s21::Controller &controller, QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void resetPosition();
    void initColors();
    void on_pushButton_file_clicked();
    void connectSetup();

    void on_horizontalScrollBar_rotate_x_valueChanged(int value);

    void on_horizontalScrollBar_rotate_y_valueChanged(int value);

    void on_horizontalScrollBar_rotate_z_valueChanged(int value);

    void on_horizontalScrollBar_translate_x_valueChanged(int value);

    void on_horizontalScrollBar_translate_y_valueChanged(int value);

    void on_horizontalScrollBar_translate_z_valueChanged(int value);

    void on_horizontalScrollBar_scale_x_valueChanged(int value);

    void on_horizontalScrollBar_scale_y_valueChanged(int value);

    void on_horizontalScrollBar_scale_z_valueChanged(int value);

    void on_doubleSpinBox_translate_x_valueChanged(double arg1);

    void on_doubleSpinBox_translate_y_valueChanged(double arg1);

    void on_doubleSpinBox_translate_z_valueChanged(double arg1);

    void on_doubleSpinBox_rotate_x_valueChanged(double arg1);

    void on_doubleSpinBox_rotate_y_valueChanged(double arg1);

    void on_doubleSpinBox_rotate_z_valueChanged(double arg1);

    void on_doubleSpinBox_scale_x_valueChanged(double arg1);

    void on_doubleSpinBox_scale_y_valueChanged(double arg1);

    void on_doubleSpinBox_scale_z_valueChanged(double arg1);

    void on_radioButton_none_pressed();

    void on_radioButton_square_pressed();

    void on_radioButton_circle_pressed();

    void on_radioButton_solid_pressed();

    void on_radioButton_dashed_pressed();

    void on_radioButton_parallel_pressed();

    void on_radioButton_central_pressed();

    void on_pushButton_change_color_vertices_clicked();

    void on_pushButton_change_color_edges_clicked();

    void on_pushButton_change_color_edges_2_clicked();

    void on_pushButton_reset_clicked();

    void loadSettings();

    void setSettings();

    void on_pushButton_screenshot_clicked();

    void on_pushButton_gif_clicked();

    void slotTimer();

    // void setXTranslate(const QString &new_x);
    void setYTranslate(const QString &new_y);
    void setZTranslate(const QString &new_z);
    void setXRotate(const QString &deg);
    void setYRotate(const QString &deg);
    void setZRotate(const QString &deg);
    void setXScale(const QString &scale);
    void setYScale(const QString &scale);
    void setZScale(const QString &scale);

  public slots:
      void setXTranslate(const QString &new_x);

  private:
    Ui::MainWindow *ui;
    QString settingFile;
    QTimer *timer;
    QGifImage *gif;
    QImage *image;
    int frame_count = 0;
    s21::Controller &controller_;
  };
}
#endif // SRC_VIEW_VIEW_H_
