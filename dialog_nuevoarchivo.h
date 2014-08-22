#ifndef DIALOG_NUEVOARCHIVO_H
#define DIALOG_NUEVOARCHIVO_H
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class dialog_nuevoarchivo;
}

class dialog_nuevoarchivo : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_nuevoarchivo(MainWindow *parent = 0);
    ~dialog_nuevoarchivo();

private slots:
    void on_agregarCampo_boton_clicked();

    void on_crearArchivo_boton_clicked();

private:
    MainWindow* mw;
    Ui::dialog_nuevoarchivo *ui;
};

#endif // DIALOG_NUEVOARCHIVO_H
