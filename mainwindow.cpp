#include <iostream>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    createMenuFunctionality();
    synchronizeBrowseControls();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createMenuFunctionality() {
    connect(ui->action_Open_Image, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_Download_Image, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Filter_Images, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_Delete_Image, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
    connect(ui->action_About_AgSnap, SIGNAL(triggered()), this, SLOT(showNotImplemented()));
}

void MainWindow::synchronizeBrowseControls() {
    connect(ui->previousButton, SIGNAL(clicked()), this, SLOT(decrementLibrarySlider()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(incrementLibrarySlider()));
}

void MainWindow::showNotImplemented() {
    QMessageBox::information(this, "Uh oh!", "Functionality to be implemented...");
}

void MainWindow::increaseLibrarySlider(int value) {
    QSlider* slider = ui->librarySlider;
    slider->setValue(slider->value() + value);
}

void MainWindow::decrementLibrarySlider() { increaseLibrarySlider(-1); }
void MainWindow::incrementLibrarySlider() { increaseLibrarySlider(1); }
