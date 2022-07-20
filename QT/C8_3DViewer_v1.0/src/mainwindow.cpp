#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

const int max_w = 960;
const int max_h = 720;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusbar->showMessage("Необходимо открыть файл", 0);
  scene = new QGraphicsScene();
  ui->graphicsView->setScene(scene);
  scene->setSceneRect(-(max_w / 2), -(max_h / 2), max_w, max_h);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  head_v = NULL;
  head_f = NULL;
  gif_num = 0;
  initSettings();
}

MainWindow::~MainWindow() {
  stack_destroy(&head_v);
  stack_i_destroy(&head_f);
  settings->sync();
  delete ui;
}

// основное задание

void MainWindow::openModel(QString filename) {
  QByteArray ba = filename.toLocal8Bit();
  char *str = ba.data();
  stack_destroy(&head_v);
  stack_i_destroy(&head_f);
  FILE *f = is_file_exist(str);
  if (f != NULL) {
    read_file(f, &head_v, &head_f, &max);
    fclose(f);
    int count_v = stack_get_count(head_v);
    int count_f = stack_i_get_count(head_f);
    ui->statusbar->showMessage(
        "Файл: " + filename.toUtf8() +
            "  Количество вершин: " + QString::number(count_v) +
            "  Количество полигонов: " + QString::number(count_f),
        0);
    ui->lineEdit_file->setText(filename.toUtf8());
    ui->horizontalSlider->setValue((int)((max_h / 2) / (max * 1.1)));
    ui->horizontalSlider_2->setValue((int)(10.0 * max));
    ui->horizontalSlider_2->setMinimum((int)(5.0 * max));

    drawModel();
  }
}

void MainWindow::drawModel() {
  double scale = ui->horizontalSlider->value();
  double z_point = scale * ui->horizontalSlider_2->value();
  scene->clear();
  ui->graphicsView->centerOn(0, 0);
  stack_i *ptr = head_f;
  while (ptr != NULL) {
    QPolygonF pol;
    for (unsigned int i = 0; i < ptr->n; i++) {
      matrix_t *point = stack_get_i(head_v, ptr->arr[i]);
      double x = point->matrix[0][0] * scale;
      double y = -(point->matrix[1][0] * scale);
      double z = (point->matrix[2][0]) * scale;
      if (ui->radioButton_central->isChecked()) {
        pol << QPointF(x / (1 - z / (z_point)), y / (1 - z / (z_point)));
      } else {
        pol << QPointF(x, y);
      }
    }
    scene->addPolygon(pol, pen_line);
    ptr = ptr->next;
  }
  if (type_v != 0)
    drawPoint();
  if (ui->checkBox->isChecked()) {
    QPen pen(QColorConstants::Red);
    scene->addEllipse(-3, -3, 6, 6, pen);
  }
  scene->update();
  if (ui->pushButton_record->text() == "Стоп") {
    saveImage(getGifName());
  }
}

void MainWindow::drawPoint() {
  stack_v *ptr = head_v;
  double scale = ui->horizontalSlider->value();
  double z_point = scale * ui->horizontalSlider_2->value();
  while (ptr != NULL) {
    matrix_t *point = &(ptr->matrix);
    double x = point->matrix[0][0] * scale;
    double y = -(point->matrix[1][0] * scale);
    double z = (point->matrix[2][0]) * scale;

    if (ui->radioButton_central->isChecked()) {
      x = x / (1 - z / (z_point));
      y = y / (1 - z / (z_point));
    }
    if (type_v == 1) {
      scene->addEllipse(x - size_v, y - size_v, 2 * size_v, 2 * size_v,
                        color_v);
    } else
      scene->addRect(x - size_v, y - size_v, 2 * size_v, 2 * size_v, color_v);
    ptr = ptr->next;
  }
}

void MainWindow::on_pushButton_file_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Выберите файл с моделью", QDir::currentPath(),
      "3d model (*.obj) ;; All files (*.*)");
  if (!filename.isNull()) {
    qDebug() << "selected file path : " << filename.toUtf8();
    openModel(filename);
  }
}

void MainWindow::on_pushButton_rotation_clicked() {
  stack_matrix_mult(&head_v,
                    matrix_get_rotation(
                        M_PI / 180.0 * ui->doubleSpinBox_rotation_x->value(),
                        M_PI / 180.0 * ui->doubleSpinBox_rotation_y->value(),
                        M_PI / 180.0 * ui->doubleSpinBox_rotation_z->value()));
  drawModel();
}

void MainWindow::on_pushButton_shift_clicked() {
  stack_matrix_mult(&head_v,
                    matrix_get_shift(ui->doubleSpinBox_shift_x->value(),
                                     ui->doubleSpinBox_shift_y->value(),
                                     ui->doubleSpinBox_shift_z->value()));
  drawModel();
}

void MainWindow::on_pushButton_scale_clicked() {
  stack_matrix_mult(&head_v,
                    matrix_get_scaling(ui->doubleSpinBox_scale_x->value()/100.0,
                                       ui->doubleSpinBox_scale_y->value()/100.0,
                                       ui->doubleSpinBox_scale_z->value()/100.0));
  drawModel();
}

// нижнее меню установки настроек
void MainWindow::on_pushButton_clicked() { drawModel(); }
void MainWindow::on_horizontalSlider_sliderReleased() { drawModel(); }
void MainWindow::on_horizontalSlider_2_sliderReleased() { drawModel(); }
void MainWindow::on_checkBox_stateChanged(int arg1) {
  settings->setValue("Centr/type", arg1);
  drawModel();
}

// bonus 2
// ________________________________________________________________________

void MainWindow::initSettings() {
  settings = new QSettings("setting.conf", QSettings::IniFormat);
  settings->sync();
  scene->setBackgroundBrush(
      settings->value("Background/color", QColorConstants::White)
          .value<QColor>());

  pen_line.setColor(
      settings->value("Line/color", QColorConstants::Blue).value<QColor>());

  pen_line.setWidth(settings->value("Line/size", 1).value<int>());

  ui->spinBox_line->setValue(settings->value("Line/size", 1).value<int>());

  ui->comboBox_line->setCurrentIndex(
      settings->value("Line/style", 1).value<int>());

  color_v =
      settings->value("Vertex/color", QColorConstants::Green).value<QColor>();

  size_v = settings->value("Vertex/size", 5).value<int>();
  ui->spinBox_point->setValue(size_v);

  type_v = settings->value("Vertex/type", 0).value<int>();
  ui->comboBox_point->setCurrentIndex(type_v);

  if (0 == settings->value("Projection/type", 0).value<int>()) {
    ui->radioButton_central->setChecked(true);
  } else {
    ui->radioButton_parallel->setChecked(true);
  }

  if (0 == settings->value("Centr/type", 0).value<int>()) {
    ui->checkBox->setChecked(false);
  } else {
    ui->checkBox->setChecked(true);
  }

  height = settings->value("Gif/height", 480).value<int>();
  width = settings->value("Gif/width", 640).value<int>();
  if (height == 480) {
    ui->radioButton->setChecked(true);
  } else {
    ui->radioButton_2->setChecked(true);
  }
  settings->sync();
}

void MainWindow::on_radioButton_central_clicked() {
  drawModel();
  settings->setValue("Projection/type", 0);
}
void MainWindow::on_radioButton_parallel_clicked() {
  drawModel();
  settings->setValue("Projection/type", 1);
}

void MainWindow::on_pushButton_bckg_color_clicked() {
  QColorDialog dlg(this);
  dlg.setWindowTitle("Цвет фона");
  dlg.setCurrentColor(QColorConstants::Gray);
  if (dlg.exec() == QColorDialog::Accepted) {
    qDebug() << dlg.selectedColor();
    scene->setBackgroundBrush(dlg.selectedColor());
    settings->setValue("Background/color", dlg.selectedColor());
    scene->update();
  }
}

void MainWindow::on_pushButton_line_color_clicked() {
  QColorDialog dlg(this);
  dlg.setWindowTitle("Цвет линии");
  dlg.setCurrentColor(QColorConstants::Blue);
  if (dlg.exec() == QColorDialog::Accepted) {
    pen_line.setColor(dlg.selectedColor());
    settings->setValue("Line/color", dlg.selectedColor());
  }
  drawModel();
}

void MainWindow::on_pushButton_point_color_clicked() {
  QColorDialog dlg(this);
  dlg.setWindowTitle("Цвет точек");
  dlg.setCurrentColor(QColorConstants::Green);
  if (dlg.exec() == QColorDialog::Accepted) {
    qDebug() << dlg.selectedColor();
    color_v = dlg.selectedColor();
    settings->setValue("Vertex/color", dlg.selectedColor());
  }
  if (type_v != 0)
    drawModel();
}

void MainWindow::on_comboBox_line_currentIndexChanged(int index) {
  switch (index) {
  case 0:
    pen_line.setStyle(Qt::NoPen);
    break;
  case 1:
    pen_line.setStyle(Qt::SolidLine);
    break;
  case 2:
    pen_line.setStyle(Qt::DashLine);
    break;
  case 3:
    pen_line.setStyle(Qt::DotLine);
    break;
  case 4:
    pen_line.setStyle(Qt::DashDotLine);
    break;
  case 5:
    pen_line.setStyle(Qt::DashDotDotLine);
    break;
  default:
    pen_line.setStyle(Qt::SolidLine);
  }
  settings->setValue("Line/style", index);
  drawModel();
}

void MainWindow::on_comboBox_point_currentIndexChanged(int index) {
  type_v = index;
  settings->setValue("Vertex/type", index);
  drawModel();
}

void MainWindow::on_spinBox_line_valueChanged(int arg1) {
  pen_line.setWidth(arg1);
  settings->setValue("Line/size", arg1);
  drawModel();
}

void MainWindow::on_spinBox_point_valueChanged(int arg1) {
  size_v = arg1;
  settings->setValue("Vertex/size", arg1);
  if (type_v != 0)
    drawModel();
}

// bonus 3
// ________________________________________________________________________

void MainWindow::saveImage(QString filename) {
  if (!filename.isNull()) {
    qDebug() << filename;
    QImage image(scene->width(), scene->height(),
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    if (!image.save(filename)) {
      qDebug() << "SAVE ERROR!";
    }
    painter.end();
  }
}

QString MainWindow::getGifName() {
  QString filename = QDir::currentPath() + "/gif/gif_frame_" +
                     QString::number(gif_num) + ".bmp";
  gif_num++;
  return filename;
}

void MainWindow::on_pushButton_save_img_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, "Выберите файл с моделью", QDir::homePath(),
      "Images(*.bmp) ;; Images(*.jpg) ;; All files (*.*)");
  saveImage(filename);
}

void MainWindow::on_pushButton_record_clicked() {
  QDir dir(QDir::currentPath() + "/gif");
  if (ui->pushButton_record->text() == "Запись") {
    qDebug() << "Запись";
    ui->pushButton_record->setText("Стоп");
    if (!dir.exists()) {
      dir.mkpath(".");
    }
    if (ui->checkBox_gif->isChecked()) {
      QMessageBox msgBox;
      msgBox.setText("Процесс может занимать много времени, в зависимости, от "
                     "сложности модели. Установите поворот нужной оси, кратный 50 кадрам (7.2)");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int res = msgBox.exec();
      if (res == QMessageBox::Ok) {
        //ui->doubleSpinBox_rotation_y->setValue(360.0 / 50.0);
        for (int i = 0; i < 50; i++) {
          on_pushButton_rotation_clicked();
        }
        on_pushButton_record_clicked();
      }
    } else {
      saveImage(getGifName());
    }
  } else if (ui->pushButton_record->text() == "Стоп") {
    qDebug() << "Стоп";
    ui->pushButton_record->setText("Удалить");
    ui->pushButton_save_gif->setEnabled(true);
  } else if (ui->pushButton_record->text() == "Удалить") {
    qDebug() << "Удалить";
    dir.removeRecursively();
    ui->pushButton_record->setText("Запись");
    ui->pushButton_save_gif->setEnabled(false);
    gif_num = 0;
  }
}

void MainWindow::on_pushButton_save_gif_clicked() {
  qDebug() << "Cохранить";
  QString filename = QFileDialog::getSaveFileName(
      this, "Выберите место сохранения gif", QDir::homePath(),
      "Gif(*.gif) ;; All files (*.*)");
  if (!filename.isNull()) {
    ui->pushButton_record->setText("Запись");
    ui->pushButton_save_gif->setEnabled(false);
    qDebug() << filename;
    QGifImage gif(QSize(width, height));
    //    QVector<QRgb> ctable;
    //    ctable << qRgb(255, 255, 255) << qRgb(0, 0, 0) << qRgb(255, 0, 0)
    //           << qRgb(0, 255, 0) << qRgb(0, 0, 255) << qRgb(255, 255, 0)
    //           << qRgb(0, 255, 255) << qRgb(255, 0, 255);
    //    gif.setGlobalColorTable(ctable, Qt::black);
    //    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);
    for (int i = 0; i < gif_num; ++i) {
      QString filenameimage =
          QDir::currentPath() + "/gif/gif_frame_" + QString::number(i) + ".bmp";

      QImage image(filenameimage, "BMP");
      if (ui->radioButton->isChecked())
        image = image.scaled(width, height, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
      gif.addFrame(image, 100);
    }
    gif.save(filename);
    QDir dir(QDir::currentPath() + "/gif");
    dir.removeRecursively();
    gif_num = 0;
  }
}

void MainWindow::on_radioButton_clicked() {
  settings->setValue("Gif/height", height = 480);
  settings->setValue("Gif/width", width = 640);
}

void MainWindow::on_radioButton_2_clicked() {
  settings->setValue("Gif/height", height = max_h);
  settings->setValue("Gif/width", width = max_w);
}
