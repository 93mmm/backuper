#pragma once

#include <QMainWindow>

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
  void BackupButtonHandler();
  void ChangeBackupPathButtonHandler();

  void RestoreButtonHandler();
  void ChangeRestorePathButtonHandler();

private:
  Ui::MainWindow *ui;
  std::string GetPathFromUser(const char *action);
};
