#ifndef DIALOG_NUEVOREGISTRO_H
#define DIALOG_NUEVOREGISTRO_H
#include "mainwindow.h"

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

private:
    MainWindow* mw;
    Ui::dialog_nuevoRegistro *ui;
};

#endif // DIALOG_NUEVOREGISTRO_H
