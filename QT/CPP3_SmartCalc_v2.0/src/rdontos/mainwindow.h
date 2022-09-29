#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <locale.h>

#include <QMainWindow>
#include <QStandardItemModel>

#include "creditcontroller.h"
#include "depositcontroller.h"
#include "dialog.h"
#include "slimcalccontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  // калькулятор
  void digits_numbers();
  void functions();
  void operators();
  void brackets();
  void unknowns();
  void on_radioButton_graph_clicked();
  void on_radioButton_value_clicked();
  void on_pushButton_clr_clicked();
  void on_pushButton_back_clicked();
  void on_pushButton_answer_clicked();
  // кредитный калькулятор
  void on_pushButton_credit_clicked();
  // депозитный калькулятор
  void on_pushButton_deposit_clicked();
  void on_pushButton_deposit_clear_clicked();
  void on_pushButton_deposit_add_clicked();

 signals:
  void set_disabled_replot();

 private:
  void init_slots();
  void update_edit(QString status_bar);

 private:
  Ui::MainWindow *ui;
  Dialog *dialog = nullptr;

  s21::SlimCalcController *slimCalcController = nullptr;
  s21::CreditController *creditController = nullptr;
  s21::DepositController *depositController = nullptr;
};
#endif  // MAINWINDOW_H
