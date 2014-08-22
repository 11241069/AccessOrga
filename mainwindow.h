#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "campos.h"
#include "mainwindow.h"
#include <QList>
#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QList <Campos> campos;
    QTableWidget *tabla2;
    QString archivo;
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

};

#endif // MAINWINDOW_H
