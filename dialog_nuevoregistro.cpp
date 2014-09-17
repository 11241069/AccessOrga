#include "dialog_nuevoregistro.h"
#include "ui_dialog_nuevoregistro.h"
#include <QDebug>
#include <QFileDialog>
#include "header.h"
#include <QTextStream>
#include <QMessageBox>

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

void dialog_nuevoRegistro::on_tableWidget_3_activated(const QModelIndex &index)
{

}

bool dialog_nuevoRegistro::cargarTabla1(){

    QStringList lectura;
    QString archivo = QFileDialog::getOpenFileName(this, tr("Open File"));
    header_file1 = Header(archivo);
    QFile filelectura(header_file1.direccion);
    QFile archivo_index(header_file1.nombre_archivo + ".libx");
    archivo_index.setFileName(header_file1.nombre_archivo + ".libx");
    if (!archivo_index.open(QIODevice::WriteOnly | QIODevice::Text)){

    }
    if(!filelectura.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream in(&filelectura);
    int bandera=0;
    while(!in.atEnd()){
        if(header_file1.inicio_registro<=bandera){
            lectura+=in.readLine();
        }else{
            in.readLine();
        }
        bandera++;
    }
    ui->tabla1->setColumnCount(header_file1.campos.size());
    ui->tabla1->setRowCount(1);

    QStringList headers;


    for(int i = 0; i < header_file1.campos.size(); i++){
        headers.append(header_file1.campos.at(i).getNombre_campo());

    }

    ui->tabla1->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < header_file1.campos.size(); i++){
        ui->tabla1->setColumnWidth(i, 200);

    }

    //leer registros del archivo y agregarlos a la tabla
    in.seek(header_file1.inicio_registro);
    int longitud_registro = header_file1.getLongitud_registro();
    int fila = 0, offset_registro = header_file1.getInicio_registro();
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
            //rrn_tabla.append(rrn);
            ui->tabla1->insertRow(fila);
            for (int i = 0; i < header_file1.campos.size(); ++i) {
                int inc = header_file1.campos.at(i).getLongitud();
                QString substring = registro.mid(offset,inc);
                ui->tabla1->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
                if(header_file1.key == i){
                    if(i != 0)
                        offset_registro += inc;
                    mw->index.insert(substring.trimmed(),QString::number(offset_registro));
                    offset_registro += header_file1.getLongitud_registro();
                }
                offset += inc;
            }
            fila++;
        }else{
            offset += longitud_registro;
        }
    }
}

void dialog_nuevoRegistro::on_cargar_tabla1_clicked()
{

    if(ui->tabla1->rowCount() != 0)
        for(int i = 0; i < ui->tabla1->rowCount(); i++){
            ui->tabla1->removeRow(0);
        }

    cargarTabla1();
    updateIndexFile1();


}

bool dialog_nuevoRegistro::cargarTabla2(){

    QStringList lectura;
    QString archivo = QFileDialog::getOpenFileName(this, tr("Open File"));
    header_file2 = Header(archivo);
    QFile filelectura(header_file2.direccion);
    QFile archivo_index(header_file2.nombre_archivo + ".libx");
    archivo_index.setFileName(header_file2.nombre_archivo + ".libx");
    if (!archivo_index.open(QIODevice::WriteOnly | QIODevice::Text)){

    }
    if(!filelectura.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream in(&filelectura);
    int bandera=0;
    while(!in.atEnd()){
        if(header_file2.inicio_registro<=bandera){
            lectura+=in.readLine();
        }else{
            in.readLine();
        }
        bandera++;
    }
    ui->tabla2->setColumnCount(header_file2.campos.size());
    ui->tabla2->setRowCount(1);

    QStringList headers;


    for(int i = 0; i < header_file2.campos.size(); i++){
        headers.append(header_file2.campos.at(i).getNombre_campo());

    }

    ui->tabla2->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < header_file2.campos.size(); i++){
        ui->tabla2->setColumnWidth(i, 200);

    }

    //leer registros del archivo y agregarlos a la tabla
    in.seek(header_file2.inicio_registro);
    int longitud_registro = header_file2.getLongitud_registro();
    int fila = 0, offset_registro = header_file2.getInicio_registro();
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
            //rrn_tabla.append(rrn);
            ui->tabla2->insertRow(fila);
            for (int i = 0; i < header_file2.campos.size(); ++i) {
                int inc = header_file2.campos.at(i).getLongitud();
                QString substring = registro.mid(offset,inc);
                ui->tabla2->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
                if(header_file2.key == i){
                    if(i != 0)
                        offset_registro += inc;
                    mw->index.insert(substring.trimmed(),QString::number(offset_registro));
                    offset_registro += header_file2.getLongitud_registro();
                }
                offset += inc;
            }
            fila++;
        }else{
            offset += longitud_registro;
        }
    }
}

void dialog_nuevoRegistro::on_cargar_tabla2_clicked()
{
    if(ui->tabla2->rowCount() != 0)
        for(int i = 0; i < ui->tabla2->rowCount(); i++){
            ui->tabla2->removeRow(0);
        }

    cargarTabla2();
    updateIndexFile2();
}

bool dialog_nuevoRegistro::updateIndexFile1(){
    //Guardar en el Indice
        QFile archivo(header_file1.nombre_archivo + ".libx");
        qDebug() << "Nombre Archivo" << header_file1.nombre_archivo;
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out2(&archivo);
        QMapIterator<QString, QString> i(mw->index);
        while (i.hasNext()) {
            i.next();
            qDebug() << "kEY" << i.key();
            qDebug() << "Value " << i.value();
            out2 << i.key() << "," << i.value() << endl;
        }
        archivo.close();
}

bool dialog_nuevoRegistro::updateIndexFile2(){
    //Guardar en el Indice
        QFile archivo(header_file2.nombre_archivo + ".libx");
        qDebug() << "Nombre Archivo" << header_file2.nombre_archivo;
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QTextStream out2(&archivo);
        QMapIterator<QString, QString> i(mw->index);
        while (i.hasNext()) {
            i.next();
            qDebug() << "kEY" << i.key();
            qDebug() << "Value " << i.value();
            out2 << i.key() << "," << i.value() << endl;
        }
        archivo.close();
}

void dialog_nuevoRegistro::on_cruzar_tablas_clicked()
{
    if(header_file1.getCampo_llave() == header_file2.getCampo_llave()){
        QMessageBox::information(this, "Aviso", "¡Es posible cruzar!");
        if(ui->filename->text() == ""){
            QMessageBox::critical(this, "Error", "Archivo sin Nombre");
        }else{

            QFile file(ui->filename->text() + ".dat");
            QFile indice(ui->filename->text() + ".libx");
            if (!indice.open(QIODevice::WriteOnly | QIODevice::Text)){
            }
            indice.close();
            int size_registro = 0;
            Header header = Header(ui->filename->text(), mw->campos.size(), mw->campos);

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
                  out << "longitud de registro, " << size_registro << "\n";
                  out << "availlist,-1   "<<'\n';
                  file.flush();
                  file.close();
             ui->filename->setText("");
             QMessageBox::information(this, "Finalizado", "Archivo creado con exito");
             mw->campos.clear();//Remover todos los campos para que este vacia cuando se crea un archivo nuevo
             this->close();
            }
    }else{
        QMessageBox::critical(this, "Error", "Los archivos no tienen campos llave en común.");
    }

}
