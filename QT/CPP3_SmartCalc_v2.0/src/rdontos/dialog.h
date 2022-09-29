#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVector>
#include <algorithm>

#include "slimcalccontroller.h"
//#include "../s21CalcController.h"
//#include "../s21CalcModel.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent, s21::SlimCalcController *calcController);
  ~Dialog();
 public slots:
  void set_disabled();

 private slots:
  void on_pushButton_clicked();
  void draw();

 private:
  Ui::Dialog *ui;
  s21::SlimCalcController *calcController;
};

#endif  // DIALOG_H
