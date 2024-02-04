#include "widget.h"
#include "../helpers/helpers.h"
#include "./ui_widget.h"

#include <filesystem>

Widget::Widget(QWidget *parent) : QWidget(parent) , ui(new Ui::Widget) {
  ui->setupUi(this);

  connect(ui->confirmationButton, &QPushButton::released, this, &Widget::ConfirmButton);
}

Widget::~Widget() {
    delete ui;
}

void Widget::ShowWindow(Ui::MainWindow *pUi, const std::string &action) {
  if (action == "restore") {
    GetAllJSONPaths(pathTo, pathFrom);
    ui->confirmationButton->setText("Restore contents!");
    setWindowTitle("Restore");
  } else {
    GetAllJSONPaths(pathFrom, pathTo);
    ui->confirmationButton->setText("Backup contents!");
    setWindowTitle("Backup");
  }
  parentUi = pUi;

  ui->confirmationInput->setText("");
  ui->pathFrom->setText(pathFrom.c_str());
  ui->pathTo->setText(pathTo.c_str());
  show();
}

void Widget::ConfirmButton() {
  if (ui->confirmationInput->text() == "\"confirm\"") {
    return;
  }

  if (not std::filesystem::exists(pathFrom)) {
    parentUi->statusBar->showMessage("Source directory does not exists", 5000);
    hide();
    return;
  }

  if (not std::filesystem::exists(pathTo)) {
    std::filesystem::create_directories(pathTo);
  }

  std::filesystem::copy_options opts = std::filesystem::copy_options::overwrite_existing
                                       | std::filesystem::copy_options::recursive;

  std::filesystem::copy(pathFrom, pathTo, opts);
  hide();
}
