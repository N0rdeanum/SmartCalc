#include "mainwindow.h"

#include "../backend/headers/helper.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);

  ui->graph->setBackground(Qt::GlobalColor::transparent);
  ui->graph->setAttribute(Qt::WA_OpaquePaintEvent, false);
  ui->graph->xAxis->setBasePen(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->yAxis->setBasePen(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->xAxis->setLabelColor(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->yAxis->setLabelColor(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->xAxis->setTickLabelColor(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->yAxis->setTickLabelColor(QColor(0xff, 0xff, 0xff, 0xff));
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  ui->graph->addGraph();
  //    ui->graph->graph(0)->setData(x, y);
  ui->graph->graph(0)->setPen(QPen(Qt::white));
  ui->graph->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
  ui->graph->replot();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_closed_bracket, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_square, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_remainder, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_string;
  QByteArray str;
  new_string = (ui->label->text());
  str = new_string.toLocal8Bit();
  new_string.push_back(button->text());
  ui->label->setText(new_string);
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->label->text().contains('.')))
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::on_pushButton_equals_clicked() {
  std::string str = ui->label->text().toStdString();
  std::string str_x = ui->lineEdit->text().toStdString();
  double new_str = QString(str_x.c_str()).toDouble();

  int status = 0;
  double res;
  status = calc(str.c_str(), &res, &new_str);

  if (status == 0)
    ui->label->setText(QString::number(res));
  else if (status == 1)
    ui->label->setText("ERROR");
  else
    ui->label->setText("UNDEFINED");
}

void MainWindow::on_pushButton_sin_clicked() {
  ui->label->setText(ui->label->text() + "sin");
}

void MainWindow::on_pushButton_cos_clicked() {
  ui->label->setText(ui->label->text() + "cos");
}

void MainWindow::on_pushButton_tan_clicked() {
  ui->label->setText(ui->label->text() + "tan");
}

void MainWindow::on_pushButton_asin_clicked() {
  ui->label->setText(ui->label->text() + "asin");
}

void MainWindow::on_pushButton_acos_clicked() {
  ui->label->setText(ui->label->text() + "acos");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  ui->label->setText(ui->label->text() + "sqrt");
}

void MainWindow::on_pushButton_log_clicked() {
  ui->label->setText(ui->label->text() + "log");
}

void MainWindow::on_pushButton_ln_clicked() {
  ui->label->setText(ui->label->text() + "ln");
}

void MainWindow::on_pushButton_c_clicked() { ui->label->clear(); }

void MainWindow::on_pushButton_x_clicked() {
  ui->label->setText(ui->label->text() + "x");
}

void MainWindow::on_pushButton_graph_clicked() {
  if (ui->label->text() != "ERROR") {
    double min = -10, max = 10;
    double minY = -10, maxY = 10;
    double h = 0;
    if (ui->label->text() != "") {
      if (ui->min->text() != "") {
        min = ui->min->text().toDouble();
      }
      if (ui->max->text() != "") {
        max = ui->max->text().toDouble();
      }
      if (ui->minY->text() != "") {
        minY = ui->minY->text().toDouble();
      }
      if (ui->maxY->text() != "") {
        maxY = ui->maxY->text().toDouble();
      }
      h = max - min;
      if (maxY - minY > h) {
        h = maxY - minY;
      }
      double temp_h = h;
      h = 0.01;
      QVector<double> x((int)(temp_h / h) + 1), y((int)(temp_h / h) + 1);
      int status = 0;
      std::string str = ui->label->text().toStdString();
      int i = 0;
      double X = min;
      double res = 0;
      for (; X <= max; X += h) {
        status = calc(str.c_str(), &res, &X);
        if (res <= maxY && res >= minY && res == res && !status) {
          x[i] = X;
          y[i] = res;
          i++;
        } else if (status) {
          break;
        }
      }
      if (!status) {
        // create graph and assign data to it:
        ui->graph->addGraph();
        ui->graph->graph(0)->setData(x, y);
        ui->graph->xAxis->setRange(min, max);
        ui->graph->yAxis->setRange(minY, maxY);
        ui->graph->replot();
      } else {
        QString error = "ERROR";
        ui->label->setText(error);
      }
    }
  }
}
