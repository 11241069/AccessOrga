#include "agregararchivo.h"
#include "ui_agregararchivo.h"

AgregarArchivo::AgregarArchivo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarArchivo)
{
    ui->setupUi(this);
}

AgregarArchivo::~AgregarArchivo()
{
    delete ui;
}
