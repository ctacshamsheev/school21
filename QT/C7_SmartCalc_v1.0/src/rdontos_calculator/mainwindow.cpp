#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_num_0, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_1, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_2, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_3, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_4, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_5, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_6, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_7, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_8, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_num_9, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_radioButton_2_clicked() {
  ui->doubleSpinBox->setEnabled(true);
  ui->doubleSpinBox_2->setEnabled(false);
  ui->doubleSpinBox_3->setEnabled(false);
  ui->doubleSpinBox_4->setEnabled(false);
  ui->doubleSpinBox_5->setEnabled(false);
}

void MainWindow::on_radioButton_clicked() {
  ui->doubleSpinBox->setEnabled(false);
  ui->doubleSpinBox_2->setEnabled(true);
  ui->doubleSpinBox_3->setEnabled(true);
  ui->doubleSpinBox_4->setEnabled(true);
  ui->doubleSpinBox_5->setEnabled(true);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  str += button->text() + "(";
  ui->statusbar->showMessage(button->text() + "(", 0);
  ui->lineEdit->setText(str);
  list.append(button->text() + "(");
  // qDebug() << "";
  // QList<QString>::iterator i;
  // for (i = list.begin(); i != list.end(); ++i)
  //  qDebug() << *i;
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  str += button->text();
  ui->statusbar->showMessage(button->text(), 0);
  ui->lineEdit->setText(str);
  list.append(button->text());
}

void MainWindow::on_pushButton_clr_clicked() {
  str.clear();
  list.clear();
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->statusbar->clearMessage();
}

void MainWindow::on_pushButton_back_clicked() {
  if (!list.isEmpty()) {
    list.pop_back();
    str.clear();
    QList<QString>::iterator i;
    for (i = list.begin(); i != list.end(); ++i) str += *i;
    ui->lineEdit->setText(str);
  } else {
    on_pushButton_clr_clicked();
  }
}

void MainWindow::on_pushButton_answer_clicked() {
  stack *head = NULL;
  double x = ui->doubleSpinBox->value();
  QByteArray ba = ui->lineEdit->text().toLocal8Bit();
  char *str = ba.data();
  char input_str[256] = {0};

  int i;
  for (i = 0; i < 255 && *str; i++) {
    input_str[i] = *str;
    str++;
  }
  input_str[i] = '\n';
  input_str[i + 1] = '\0';

  double ans = 0.0;

  if (checking_brackets(input_str) && parse(input_str, &head)) {
    printf("INPUT :");
    output_stack(head);
    stack *out_list = get_polish(head);
    stack *out_stack = revers_stack(&out_list);
    printf("POLISH:");
    output_stack(out_stack);

    int flag = 1;
    ans = get_stack_value(out_stack, x, &flag);
    if (flag == 1) {
      ui->lineEdit_2->setText(QString::number(ans, 'g'));
      if (ui->radioButton->isChecked()) {
        if (ui->doubleSpinBox_4->value() < 0.00001) {
          ui->doubleSpinBox_4->setValue(0.01);
        }
        ui->statusbar->showMessage("= (Graph)", 0);
        dialog = new Dialog;
        connect(this, &MainWindow::set_graph, dialog, &Dialog::set_graph_in);
        emit set_graph(
            ui->lineEdit->text(), out_stack, ui->doubleSpinBox_2->value(),
            ui->doubleSpinBox_3->value(), ui->doubleSpinBox_4->value(),
            ui->doubleSpinBox_5->value());
        dialog->show();
      }
      printf("ANSVER: %f\n\n", ans);
    } else {
      ui->lineEdit_2->setText("STACK ERROR");
    }
    destroy_stack(&out_list);
    destroy_stack(&out_stack);
  } else {
    ui->lineEdit_2->setText("PARSE ERROR");
  }
  destroy_stack(&head);
}

void add_table(double d, QStandardItemModel *model, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model->setItem(i, j, item);
}

// кредитный калькулятор
void MainWindow::on_pushButton_clicked() {
  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels = QObject::tr(
                           "Сумма платежа;Платеж по основному долгу;Платеж "
                           "по процентам;Остаток долга")
                           .simplified()
                           .split(";");
  model->setHorizontalHeaderLabels(labels);

  double amount = ui->doubleSpinBox_amount->value();  // сумма кредита
  int term = ui->spinBox_term->value();               // срок кредита
  double rate = ui->doubleSpinBox_rate->value();  // процентная ставка
  double sum_over_payment = 0.0;  // сумма переплаты
  double monthly_rate = (rate / 12) / 100;  // процентная ставка в месяц
  double sum_all = 0.0;        // общая сумма выплат
  double tmp_amount = amount;  // остаток долга

  if (ui->radioButton_annuity_credit->isChecked()) {
    double sum_payment =
        roundf(amount * (monthly_rate / (1 - pow(1 + monthly_rate, -term))) *
               100) /
        100;
    sum_over_payment = sum_payment * term - amount;
    for (int i = 0; i < term; i++) {
      double overpayment = tmp_amount * monthly_rate;
      double payment = roundf((sum_payment - overpayment) * 100) / 100;
      tmp_amount -= payment;
      add_table(sum_payment, model, i, 0);
      add_table(payment, model, i, 1);
      add_table(overpayment, model, i, 2);
      add_table(tmp_amount, model, i, 3);
    }
  } else {
    double payment = amount / term;
    for (int i = 0; i < term; i++) {
      double overpayment = tmp_amount * monthly_rate;
      tmp_amount = tmp_amount - payment;
      sum_over_payment += overpayment;
      double sum_payment = payment + overpayment;

      add_table(sum_payment, model, i, 0);
      add_table(payment, model, i, 1);
      add_table(overpayment, model, i, 2);
      add_table(tmp_amount, model, i, 3);
    }
  }

  sum_all = sum_over_payment + amount;
  ui->lineEdit_4->setText(QString::number(sum_over_payment, 'f', 2));
  ui->lineEdit_3->setText(QString::number(sum_all, 'f', 2));

  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

void MainWindow::on_radioButton_differentiated_credit_clicked() {}

void f(QStandardItemModel *model, struct depos it, int i) {
  QStandardItem *item = new QStandardItem(it.pay_date.toString("dd MMM yyyy"));
  model->setItem(i, 0, item);
  add_table(it.payment, model, i, 2);
}

void MainWindow::on_pushButton_2_clicked() {
  ui->statusbar->clearMessage();
  double amount = ui->doubleSpinBox_amount_2->value();  // сумма депозита
  int term = ui->spinBox_term_2->value();           // срок депозита
  double rate = ui->doubleSpinBox_rate_2->value();  // процентная ставка
  // double monthly_rate = (rate / 12) / 100; // процентная ставка в месяц
  double sum_all = 0.0;        // общая сумма выплат
  double tmp_amount = amount;  // текущий депозит

  double accrued_deposit = 0.0;  // начисленные проценты
  double replenishment_deposit = 0.0;  // пополнение

  QDate begin_date = ui->dateEdit->date();  // дата вклада
  QDate current_date = begin_date;
  QDate end_date = current_date.addMonths(term);

  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels =
      QObject::tr("Дата;Начислено процентов;Вклад пополнен;Остаток вклада")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);
  QStandardItem *item = 0;

  struct depos t;
  t.payment = amount;
  t.pay_date = begin_date;
  // pay_list.append(t);

  int flag = 1;
  for (int i = 0; i < pay_list.count(); i++) {
    if (pay_list[i].pay_date < begin_date || pay_list[i].pay_date > end_date) {
      ui->statusbar->showMessage("DATE ERROR", 0);
      flag = 0;
      // break;
    }
  }
  if (flag) {
    f(model, t, 0);
    int i = 1;
    while (term > 0) {
      current_date = current_date.addMonths(1);
      term--;

      accrued_deposit = roundf(tmp_amount * (rate / 100.0) *
                               ((double)begin_date.daysTo(current_date) /
                                (double)current_date.daysInYear()) *
                               100.0) /
                        100.0;

      for (int j = 0; j < pay_list.count(); j++) {
        if (pay_list[j].pay_date < current_date &&
            pay_list[j].pay_date >= begin_date) {
          f(model, pay_list[j], i);
          i++;
          // pay_list.removeAt(j);
          accrued_deposit +=
              roundf(pay_list[j].payment * (rate / 100.0) *
                     ((double)pay_list[j].pay_date.daysTo(current_date) /
                      (double)current_date.daysInYear()) *
                     100.0) /
              100.0;
          tmp_amount += pay_list[j].payment;
        }
      }

      if (tmp_amount < 0) {
        ui->statusbar->showMessage("SUMM ERROR", 0);
        break;
      }
      sum_all += accrued_deposit;

      // дата
      item = new QStandardItem(current_date.toString("dd MMM yyyy"));
      model->setItem(i, 0, item);
      // начислено процентов
      add_table(accrued_deposit, model, i, 1);
      if (ui->checkBox->isChecked()) {
        replenishment_deposit = accrued_deposit;
        tmp_amount += accrued_deposit;
      }
      // пополнение
      add_table(replenishment_deposit, model, i, 2);
      // остаток
      add_table(tmp_amount, model, i, 3);
      begin_date = current_date;
      i++;
    }
    item = new QStandardItem("Сумма проц:");
    model->setItem(i, 0, item);
    add_table(sum_all, model, i, 1);
    item = new QStandardItem("Вклад:");
    model->setItem(i, 2, item);
    add_table(tmp_amount, model, i, 3);
    QString str =
        "Сумма к концу срока:" + QString::number(sum_all + tmp_amount, 'f', 2);
    ui->statusbar->showMessage(str, 0);
  } else {
    for (int i = 0; i < pay_list.count(); i++) {
      struct depos it = pay_list[i];
      f(model, it, i);
    }
  }

  ui->tableView_2->setModel(model);
  ui->tableView_2->resizeColumnsToContents();
  ui->tableView_2->show();
}

void MainWindow::on_pushButton_4_clicked() {
  pay_list.clear();
  QStandardItemModel *model = new QStandardItemModel();
  ui->tableView_2->setModel(model);
  ui->tableView_2->show();
}

void MainWindow::on_pushButton_3_clicked() {
  struct depos t;
  t.pay_date = ui->dateEdit_2->date();
  t.payment = ui->doubleSpinBox_amount_3->value();
  if (ui->radioButton_take->isChecked()) {
    t.payment *= -1;
  }
  pay_list.append(t);
  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels =
      QObject::tr("Дата;Начислено процентов;Вклад пополнен;Остаток вклада")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);
  for (int i = 0; i < pay_list.count(); i++) {
    for (int j = 0; j < pay_list.count(); j++) {
      if (pay_list[i].pay_date < pay_list[j].pay_date) {
        pay_list.swapItemsAt(i, j);
      }
    }
  }
  for (int i = 0; i < pay_list.count(); i++) {
    struct depos it = pay_list[i];
    f(model, it, i);
  }
  ui->tableView_2->setModel(model);
  ui->tableView_2->resizeColumnsToContents();
  ui->tableView_2->show();
}
