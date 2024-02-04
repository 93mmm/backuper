#include "mainwindow.h"
#include "../helpers/helpers.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->backupButton, &QPushButton::released, this, &MainWindow::BackupButtonHandler);
  connect(ui->changeBackupPathButton, &QPushButton::released, this, &MainWindow::ChangeBackupPathButtonHandler);

  connect(ui->restoreButton, &QPushButton::released, this, &MainWindow::RestoreButtonHandler);
  connect(ui->changeRestorePathButton, &QPushButton::released, this, &MainWindow::ChangeRestorePathButtonHandler);
  
  std::string path;
  if (GetJSONPath("backup", path)) {
    ui->statusBar->showMessage("Error occurred", 5000);
  }
  ui->backupPath->setText(path.c_str());

  if (GetJSONPath("restore", path)) {
    ui->statusBar->showMessage("Error occurred", 5000);
  }
  ui->restorePath->setText(path.c_str());
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::BackupButtonHandler() {
  w.ShowWindow(ui, "backup");
}

void MainWindow::ChangeBackupPathButtonHandler() {
  std::string dir = GetPathFromUser("backup");
  if (dir == "") {
    return;
  }
  ui->backupPath->setText(dir.c_str());
}

void MainWindow::RestoreButtonHandler() {
  w.ShowWindow(ui, "restore");
}

void MainWindow::ChangeRestorePathButtonHandler() {
  std::string dir = GetPathFromUser("restore");
  if (dir == "") {
    return;
  }
  ui->restorePath->setText(dir.c_str());
}

std::string MainWindow::GetPathFromUser(const char *action) {
  std::string dir;
  if (GetJSONPath(action, dir)) {
    ui->statusBar->showMessage("Error occurred", 5000);
  }

  dir = QFileDialog::getExistingDirectory(this, "Select Folder", dir.c_str()).toStdString();
  if (dir == "") {
    return "";
  }

  if (SetJSONPath(action, dir)) {
    ui->statusBar->showMessage("Error occurred", 5000);
  }

  return dir;
}
