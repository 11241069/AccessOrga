#ifndef DIALOG_ABRIRARCHIVOS_H
#define DIALOG_ABRIRARCHIVOS_H
#include <QTableWidget>
#include "mainwindow.h"
#include "header.h"
#include <QDialog>
#include <QMap>
#include <QList>
#include <QString>
#include "btree.h"
#include "btreenode.h"
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

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    MainWindow* mw;
    Ui::dialog_abrirArchivos *ui;
    Header header;
    Header header_compactar;
    QString a;
    BTree ArbolB=BTree(32);
    void updateIndex();
    bool eliminarRegistro(QString);
    bool rewrite(QString, int &availlist, QString);
    QString leerRegistro();

};

#endif // DIALOG_ABRIRARCHIVOS_H
