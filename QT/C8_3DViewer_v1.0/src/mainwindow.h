#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgifimage.h"
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QImage>
#include <QMainWindow>
#include <QPainter>
#include <QSettings>

extern "C" {
#include "parser.h"
#include "s21_matrix.h"
#include "stack.h"
#include "stack_i.h"
}

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

  void openModel(QString filename); // парсинг файла filename
  void drawModel(); // отрисовка полигонов (плоскостей)
  void drawPoint(); // отрисовка вершин (векторов)

  void initSettings();
  // установка настроек по умолчанию, чтение настроек из файла. Bonus 2

  void saveImage(QString filename);
  // сохранение  QGraphicsScene в файл png, jpg. Bonus 3
  QString getGifName();
  // генерирует имя для кадра gif

private slots:
  // основная часть задания
  void on_pushButton_file_clicked();     // открытие модели
  void on_pushButton_rotation_clicked(); // вращение
  void on_pushButton_shift_clicked();    // сдвиг
  void on_pushButton_scale_clicked();    // масштабирование

  // нижнее меню установки настроек
  void on_horizontalSlider_sliderReleased(); // масштаб
  void on_horizontalSlider_2_sliderReleased(); // отдаление наблюдателя по 0Z
                                               // при центральной проекции
  void on_checkBox_stateChanged(int arg1); // отрисовка центра
  void on_pushButton_clicked();            // перерисовать

  // bonus 2

  // проекция
  void on_radioButton_central_clicked(); // центральная проекция
  void on_radioButton_parallel_clicked(); // параллельная проекция

  // фон
  void on_pushButton_bckg_color_clicked(); // изменение цвета фона

  // линия
  void on_pushButton_line_color_clicked(); // изменение цвета линии
  void on_comboBox_line_currentIndexChanged(int index); // изменение типа линии
  void on_spinBox_line_valueChanged(int arg1); // изменение толщины линии

  // вершины
  void on_pushButton_point_color_clicked(); // изменение цвета вершины
  void on_comboBox_point_currentIndexChanged(int index); // изменение типа
  void on_spinBox_point_valueChanged(int arg1); // изменение размера вершины

  // bonus 3
  void on_pushButton_save_img_clicked(); // сохранение в файл png, jpg.
  void on_pushButton_record_clicked(); // запись, удаление кадров для gif.
  void on_pushButton_save_gif_clicked(); // сохранение в файл gif

  void on_radioButton_clicked();

  void on_radioButton_2_clicked();

private:
  Ui::MainWindow *ui; // форма
  stack_v *head_v; // указатель на список вершин (векторов)
  stack_i *head_f; // указатель на список полигонов (плоскостей)
  QGraphicsScene *scene; // графическая сцена для отрисовки, хранит в себе
                         // полигоны и фигуры вершин
  double max; // максимальное значение отдаления по осям 0X, 0Y, 0Z используется
              // для автоматического масштабирования на поле scene

  QColor color_v;      // цвет вершины
  int size_v;          // размер вершины
  int type_v;          // тип вершины
  QPen pen_line;       // цвет, тип, размер линии
  QSettings *settings; // сохранение настроек
  int gif_num;         // счетчик кадров gif анимации
  int height;          // ширина gif
  int width;           // высота gif
};
#endif // MAINWINDOW_H
