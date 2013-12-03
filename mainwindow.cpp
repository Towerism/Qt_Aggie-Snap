#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    createMenuFunctionality();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createMenuFunctionality() {

    connect(ui->action_Open_Image, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_Download_Image, SIGNAL(triggered()), SLOT(showNotImplemented()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Filter_Images, SIGNAL(triggered()), SLOT(showNotImplemented()));
    connect(ui->action_Delete_Image, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_About_AgSnap, SIGNAL(triggered()), SLOT(showNotImplemented()));
}

void MainWindow::showNotImplemented() {
}
