#include "dialog.h"

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  flag_name = 1;
}

Dialog::~Dialog() { delete ui; }

void Dialog::set_graph_in(QString str, stack *head, double begin, double end,
                          double h, double maxY) {
  if (flag_name == 1) {
    int flag = 1;
    double X, min = maxY, max = -maxY;
    if (maxY <= 0.001) {
      maxY = 1000000;
    }
    if (end < begin) {
      double tmp = begin;
      begin = end;
      end = tmp;
    }
    QVector<double> x, y;
    X = begin;
    while (X < end) {
      x.push_back(X);
      double Y = get_stack_value(head, X, &flag);
      y.push_back(Y);
      if (Y > max && Y <= maxY) max = Y;
      if (Y < min && Y >= -maxY) min = Y;
      X += h;
    }
    if (flag) {
      ui->label->setText(str);
      ui->widget->xAxis->setRange(begin * 1.005, end * 1.005);
      ui->widget->yAxis->setRange(min * 1.005, max * 1.005);
      ui->widget->addGraph();
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
      ui->widget->graph()->setData(x, y);
    } else {
      ui->label->setText("ERROR");
    }
    flag_name++;
  }
}
