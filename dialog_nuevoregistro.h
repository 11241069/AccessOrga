#ifndef DIALOG_NUEVOREGISTRO_H
#define DIALOG_NUEVOREGISTRO_H
#include "mainwindow.h"
#include "header.h"
#include <QDialog>

namespace Ui {
class dialog_nuevoRegistro;
}

class dialog_nuevoRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_nuevoRegistro(MainWindow *parent = 0);
    ~dialog_nuevoRegistro();

private slots:
    void on_tableWidget_3_activated(const QModelIndex &index);

    void on_cargar_tabla1_clicked();

    void on_cargar_tabla2_clicked();

    void on_cruzar_tablas_clicked();

private:
    MainWindow* mw;
    Header header_file1;
    Header header_file2;
    Ui::dialog_nuevoRegistro *ui;
    bool cargarTabla1();
    bool cargarTabla2();
    bool updateIndexFile1();
    bool updateIndexFile2();
};

#endif // DIALOG_NUEVOREGISTRO_H
