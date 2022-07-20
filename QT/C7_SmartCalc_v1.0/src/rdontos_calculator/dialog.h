#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
extern "C" {
#include "../parser.h"
#include "../polish_notation.h"
#include "../s21_calc.h"
#include "../stack.h"
}

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

 public:
  Ui::Dialog *ui;

 private:
  int flag_name;

 public slots:
  void set_graph_in(QString str, stack *head, double begin, double end,
                    double dh, double maxY);
};

#endif  // DIALOG_H
