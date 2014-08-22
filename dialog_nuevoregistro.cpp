#include "dialog_nuevoregistro.h"
#include "ui_dialog_nuevoregistro.h"
#include "mainwindow.h"

dialog_nuevoRegistro::dialog_nuevoRegistro(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::dialog_nuevoRegistro)
{
    ui->setupUi(this);
    mw = parent;
}

dialog_nuevoRegistro::~dialog_nuevoRegistro()
{
    delete ui;
}
