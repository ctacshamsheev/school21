#include "mainwindow.h"

#include "ui_mainwindow.h"

// ___________________ калькулятор ___________________
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_ALL, "en_US.UTF-8");
  ui->setupUi(this);
  this->init_slots();
  this->depositController = new s21::DepositController();
  slimCalcController = new s21::SlimCalcController();
}

MainWindow::~MainWindow() {
  delete slimCalcController;
  delete creditController;
  delete depositController;
  delete ui;
}

void MainWindow::update_edit(QString status_bar) {
  ui->statusbar->showMessage(status_bar, 0);
  ui->lineEdit_2->setText("");
  ui->lineEdit->setText(slimCalcController->toString());
  if (dialog != nullptr) {
    // emit set_disabled_replot();
  }
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  slimCalcController->putFunctions(button->text());
  slimCalcController->putBracket("(");
  update_edit(button->text() + "(");
}

void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();
  slimCalcController->putOperations(button->text());
  update_edit(button->text());
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  try {
    slimCalcController->putNumber(button->text());
    update_edit(button->text());
    if (ui->radioButton_value->isChecked()) {
      on_pushButton_answer_clicked();
    }
  } catch (std::exception &e) {
    on_pushButton_clr_clicked();
    ui->lineEdit_2->setText("invalid input number");
  }
}

void MainWindow::brackets() {
  QPushButton *button = (QPushButton *)sender();
  slimCalcController->putBracket(button->text());
  update_edit(button->text());
}

void MainWindow::unknowns() {
  QPushButton *button = (QPushButton *)sender();
  slimCalcController->putUnknown(button->text());
  update_edit(button->text());
}

void MainWindow::on_pushButton_clr_clicked() {
  slimCalcController->clear();
  update_edit("clear");
}

void MainWindow::on_pushButton_back_clicked() {
  slimCalcController->clearBack();
  update_edit("clearBack");
}

void MainWindow::on_pushButton_answer_clicked() {
  update_edit("answer");
  try {
    double ans = slimCalcController->getResult(ui->doubleSpinBox->value());
    if (std::fabs(ans) > 1000000)
      ui->lineEdit_2->setText(QString::number(ans, 'g', 10));
    else
      ui->lineEdit_2->setText(QString::number(ans, 'g'));
    if (ui->radioButton_graph->isChecked()) {
      ui->statusbar->showMessage("graph", 0);

      s21::SlimCalcController *copyControler =
          new s21::SlimCalcController(*slimCalcController);
      copyControler->getResult(0);
      dialog = new Dialog(nullptr, copyControler);

      connect(this, &MainWindow::set_disabled_replot, dialog,
              &Dialog::set_disabled);
      dialog->show();
    }
  } catch (std::invalid_argument &e) {
    ui->lineEdit_2->setText(e.what());
  }
}

void MainWindow::on_radioButton_value_clicked() {
  ui->doubleSpinBox->setEnabled(true);
}

void MainWindow::on_radioButton_graph_clicked() {
  ui->doubleSpinBox->setEnabled(false);
}

void MainWindow::init_slots() {
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
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(unknowns()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(brackets()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(brackets()));
}

//___________________ кредитный калькулятор ___________________

void MainWindow::on_pushButton_credit_clicked() {
  ui->statusbar->clearMessage();
  if (creditController == nullptr) {
    delete creditController;
  }
  creditController = new s21::CreditController(
      ui->doubleSpinBox_amount->value(), ui->spinBox_term->value(),
      ui->doubleSpinBox_rate->value(),
      ui->radioButton_annuity_credit->isChecked());

  QStringList labels = QObject::tr(
                           "Сумма платежа;Платеж по основному долгу;Платеж "
                           "по процентам;Остаток долга")
                           .simplified()
                           .split(";");

  ui->lineEdit_4->setText(
      QString::number(creditController->getSumOverPayment(), 'f', 2));
  ui->lineEdit_3->setText(
      QString::number(creditController->getSumAll(), 'f', 2));
  QStandardItemModel *model = creditController->getCreditModel();

  model->setHorizontalHeaderLabels(labels);
  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

//___________________ депозитный калькулятор ___________________

void MainWindow::on_pushButton_deposit_clicked() {
  ui->statusbar->clearMessage();
  double amount = ui->doubleSpinBox_amount_2->value();  // сумма депозита
  int term = ui->spinBox_term_2->value();           // срок депозита
  double rate = ui->doubleSpinBox_rate_2->value();  // процентная ставка
  QDate begin_date = ui->dateEdit->date();          // дата вклада
  bool isCapital = ui->checkBox->isChecked();  // капитализация процентов

  try {
    QStandardItemModel *model = depositController->getDepositModel(
        amount, term, rate, begin_date, isCapital);
    QStringList labels =
        QObject::tr("Дата;Начислено процентов;Вклад пополнен;Остаток вклада")
            .simplified()
            .split(";");
    model->setHorizontalHeaderLabels(labels);

    QString str = "Сумма к концу срока: " +
                  QString::number(depositController->getAmount(), 'f', 2) +
                  "\tПроценты: " +
                  QString::number(depositController->getSumAll(), 'f', 2);
    ui->statusbar->showMessage(str, 0);

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->show();
  } catch (std::invalid_argument &e) {
    on_pushButton_deposit_clear_clicked();
    ui->statusbar->showMessage(e.what(), 0);
  }
}

void MainWindow::on_pushButton_deposit_clear_clicked() {
  ui->tableView_2->setModel(depositController->getClear());
  ui->tableView_2->show();
}

void MainWindow::on_pushButton_deposit_add_clicked() {
  QDate pay_date = ui->dateEdit_2->date();
  double payment = ui->doubleSpinBox_amount_3->value();
  if (ui->radioButton_take->isChecked()) {
    payment *= -1;
  }
  QStandardItemModel *model = depositController->getItem(pay_date, payment);

  QStringList labels =
      QObject::tr("Дата;Начислено процентов;Вклад пополнен;Остаток вклада")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);
  ui->tableView_2->setModel(model);
  ui->tableView_2->resizeColumnsToContents();
  ui->tableView_2->show();
}
