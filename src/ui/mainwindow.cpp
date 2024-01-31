#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->backupButton, &QPushButton::released, this, &MainWindow::BackupButtonHandler);
  connect(ui->changeBackupPathButton, &QPushButton::released, this, &MainWindow::ChangeBackupPathButtonHandler);

  connect(ui->restoreButton, &QPushButton::released, this, &MainWindow::RestoreButtonHandler);
  connect(ui->changeRestorePathButton, &QPushButton::released, this, &MainWindow::ChangeRestorePathButtonHandler);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::BackupButtonHandler() {
  // TODO: Are you shure want to backup your world?
  printf("backup button\n");
}

void MainWindow::ChangeBackupPathButtonHandler() {
  // TODO: Window with folder selection
  printf("backup path button\n");

}

void MainWindow::RestoreButtonHandler() {
  // TODO: Are you shure want to restore your world?
  printf("restore button\n");

}

void MainWindow::ChangeRestorePathButtonHandler() {
  // TODO: Window with folder selection
  printf("restore path button\n");
  
}

