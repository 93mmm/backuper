#pragma once
#include "ui_mainwindow.h"
#include <QWidget>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  void ShowWindow(Ui::MainWindow *pUi, const std::string &action);

private slots:
  void ConfirmButton();

private:
  Ui::Widget *ui;
  Ui::MainWindow *parentUi;
  std::string pathFrom,
              pathTo;
};
