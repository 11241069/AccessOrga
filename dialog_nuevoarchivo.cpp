#include "dialog_nuevoarchivo.h"
#include "ui_dialog_nuevoarchivo.h"
#include "mainwindow.h"
#include "campos.h"
#include "header.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
using std::ofstream;
using std::string;
using std::stringstream;

dialog_nuevoarchivo::dialog_nuevoarchivo(MainWindow *parent) :
    QDialog(parent),

    ui(new Ui::dialog_nuevoarchivo)
{
    ui->setupUi(this);
    mw = parent;
}

dialog_nuevoarchivo::~dialog_nuevoarchivo()
{
    delete ui;
}

void dialog_nuevoarchivo::on_agregarCampo_boton_clicked()
{

    int key = 1;
    if(ui->bool_esllave->isEnabled())
        key = 0;
    Campos campo = Campos(ui->name_campo->text(), ui->tipo_campo->currentText(),
                              ui->long_campo->value(), key);
    mw->campos.append(campo);
    ui->name_campo->setText("");
    ui->tipo_campo->setCurrentIndex(0);
    ui->long_campo->setValue(0);
    ui->bool_esllave->setEnabled(false);

}

void dialog_nuevoarchivo::on_crearArchivo_boton_clicked()
{

    if(ui->nombre_archivo->text() == ""){
        QMessageBox::critical(this, "Error", "Archivo sin Nombre");
    }else if(mw->campos.size() <= 0){
        QMessageBox::critical(this, "Error", "Debe agregar al menos 1 campo");
    }else{
        QFile file(ui->nombre_archivo->text());
        int size_registro = 0;
        Header header = Header(ui->nombre_archivo->text(), mw->campos.size());

         if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

         QTextStream out(&file);
         out << mw->campos.size() << "\n";

         for(int i = 0; i < mw->campos.size(); i++){
             out << mw->campos.at(i).getNombre_campo() << ","
                     << mw->campos.at(i).getTipo() << ","
                     << mw->campos.at(i).getLongitud() << ","
                     << mw->campos.at(i).getEsllave() << "\n";
                        size_registro += mw->campos.at(i).getLongitud();
         }
              out << '&'<<"-1"<<'\n';
              file.flush();
              file.close();
         ui->nombre_archivo->setText("");
         QMessageBox::information(this, "Finalizado", "Archivo creado con exito");
         mw->campos.clear();//Remover todos los campos para que este vacia cuando se crea un archivo nuevo
         this->close();
        }


}

