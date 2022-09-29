#include "dialog.h"

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, s21::SlimCalcController *calcController)
    : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  this->calcController = calcController;
  ui->label->setText(calcController->toString());
  ui->pushButton->setDisabled(false);
  draw();
}

Dialog::~Dialog() {
  delete ui;
  delete calcController;
}

void Dialog::set_disabled() { ui->pushButton->setDisabled(true); }

void Dialog::on_pushButton_clicked() {
  if (calcController != nullptr) {
    try {
      calcController->getResult(0);
      draw();
    } catch (std::exception &e) {
      ui->label->setText(e.what());
      set_disabled();
    }
  } else {
    ui->label->setText("model is null");
    ui->widget->clearGraphs();
    set_disabled();
  }
}

void Dialog::draw() {
  ui->widget->clearGraphs();
  QVector<double> x, y;

  double begin =
      std::min(ui->doubleSpinBox_2->value(), ui->doubleSpinBox_3->value());
  double end =
      std::max(ui->doubleSpinBox_2->value(), ui->doubleSpinBox_3->value());
  double dx = ui->doubleSpinBox_4->value();

  double xi = begin;
  while (xi < end) {
    x.push_back(xi);
    y.push_back(calcController->getY(xi));
    xi += dx;
  }

  auto it = std::minmax_element(y.begin(), y.end());
  double min = std::max(ui->doubleSpinBox_5->value() * (-1), *it.first);
  double max = std::min(ui->doubleSpinBox_5->value(), *it.second);
  if (min == max) {
    min = 0;
    if (max == 0) {
      max = 1;
      min = -1;
    }
  }

  ui->widget->xAxis->setRange(begin * 1.005, end * 1.005);
  ui->widget->yAxis->setRange(min * 1.005, max * 1.005);
  ui->widget->addGraph();

  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}
