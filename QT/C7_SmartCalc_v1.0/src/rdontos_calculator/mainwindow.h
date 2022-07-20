#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <dialog.h>

#include <QMainWindow>
#include <QStandardItemModel>

#include "qdatetime.h"

extern "C" {
#include "../parser.h"
#include "../polish_notation.h"
#include "../s21_calc.h"
#include "../stack.h"
}

//#include <QCustomPlot.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct depos {
  QDate pay_date;
  double payment;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digits_numbers();
  void functions();
  void on_radioButton_2_clicked();
  void on_radioButton_clicked();
  void on_pushButton_clr_clicked();
  void on_pushButton_back_clicked();
  void on_pushButton_answer_clicked();
  void on_pushButton_clicked();
  void on_radioButton_differentiated_credit_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_3_clicked();

 signals:
  void set_graph(QString, stack *, double, double, double, double);

 private:
  Ui::MainWindow *ui;
  QString str;
  QList<QString> list;
  QList<struct depos> pay_list;
  Dialog *dialog;
};
#endif  // MAINWINDOW_H
