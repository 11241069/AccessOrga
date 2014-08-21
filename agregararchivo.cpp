#include "agregararchivo.h"
#include "ui_agregararchivo.h"

AgregarArchivo::AgregarArchivo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarArchivo)
{
    campos=QList<Campo>();
    ui->setupUi(this);

}

AgregarArchivo::~AgregarArchivo()
{
    delete ui;
}

void AgregarArchivo::on_pushButton_2_clicked()
{
    Campo campoagregando = Campo();
    campoagregando.nombrecampo=ui->JLine_NombreCampo->text();
    campoagregando.esllave=ui->CB_llave->isChecked();
    campoagregando.tipo=ui->CB_Tipo->itemText(ui->CB_Tipo->currentIndex());
    campoagregando.longitud=(ui->SB_Longitud->text().toInt());
    campos.append(campoagregando);
}


void AgregarArchivo::on_pushButton_clicked()
{
    Archivo archivonuevo = Archivo();
    QFile* a =new QFile(ui->JText_NombreArchivo->text());
    archivonuevo.camposset(&campos);
    archivonuevo.qfileset(a);
}
