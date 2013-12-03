#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showNotImplemented();
    void decrementLibrarySlider();
    void incrementLibrarySlider();

private:
    Ui::MainWindow *ui;
    void createMenuFunctionality();
    void synchronizeBrowseControls();
    void increaseLibrarySlider(int value);
};

#endif // MAINWINDOW_H
