#ifndef DIALOG_ABRIRARCHIVOS_H
#define DIALOG_ABRIRARCHIVOS_H
#include <QTableWidget>
#include "mainwindow.h"
#include "header.h"
#include <QDialog>
#include <QList>
#include <QString>
namespace Ui {
class dialog_abrirArchivos;
}

class dialog_abrirArchivos : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_abrirArchivos(MainWindow *parent = 0);
    QTableWidget *tabla;
    ~dialog_abrirArchivos();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    MainWindow* mw;
    Ui::dialog_abrirArchivos *ui;
    Header header;
    QString a;
};

#endif // DIALOG_ABRIRARCHIVOS_H
