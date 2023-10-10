#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGradient>
#include <QMainWindow>
#include <QProperty>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digit_numbers();

  void on_pushButton_dot_clicked();

  void on_pushButton_equals_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_asin_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_ln_clicked();

  void on_pushButton_c_clicked();

  void on_pushButton_x_clicked();

  void on_pushButton_graph_clicked();

 private:
  Ui::SmartCalc *ui;

  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
