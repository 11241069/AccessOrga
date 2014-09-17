#include "dialog_abrirarchivos.h"
#include "ui_dialog_abrirarchivos.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "header.h"
#include <iostream>
#include "dialog_nuevoregistro.h"
#include <QDebug>
#include <QMessageBox>
#include <string>
#include "btree.h"
#include "btreenode.h"
using namespace std;

dialog_abrirArchivos::dialog_abrirArchivos(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::dialog_abrirArchivos)
{
    ui->setupUi(this);
    mw = parent;
    ArbolB=BTree(32);

}

dialog_abrirArchivos::~dialog_abrirArchivos()
{
    delete ui;
}

void dialog_abrirArchivos::on_pushButton_clicked()//Abrir Archivo Existente
{
    QStringList lectura;
    QString archivo = QFileDialog::getOpenFileName(this, tr("Open File"));
    header = Header(archivo);
    QFile filelectura(header.direccion);
    QFile archivo_index(header.nombre_archivo + ".libx");
    archivo_index.setFileName(header.nombre_archivo + ".libx");
    if (!archivo_index.open(QIODevice::WriteOnly | QIODevice::Text)){

    }
    filelectura.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&filelectura);
    int bandera=0;
    while(!in.atEnd()){
        if(header.inicio_registro<=bandera){
            lectura+=in.readLine();
            qDebug() <<"Lectura De Registr"<<lectura.at(0);
        }else{
            in.readLine();
        }
        bandera++;
    }
    ui->tabla->setColumnCount(header.campos.size());
    ui->tabla->setRowCount(1);

    QStringList headers;


    for(int i = 0; i < header.campos.size(); i++){
        headers.append(header.campos.at(i).getNombre_campo());

    }
    ui->camposbox->addItems(headers);
    ui->tabla->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < header.campos.size(); i++){
        ui->tabla->setColumnWidth(i, 200);

    }



    ui->tabla2->setColumnCount(2);
    ui->tabla2->setRowCount(header.campos.size());
    for(int i = 0; i < header.campos.size(); i++){
        ui->tabla2->setItem(i,0,new QTableWidgetItem(header.campos.at(i).getNombre_campo()));
    }
    ui->tabla->setRowCount(lectura.size());



    //leer registros del archivo y agregarlos a la tabla
    in.seek(header.inicio_registro);
    int longitud_registro = header.getLongitud_registro();
    int fila = 0, offset_registro = header.getInicio_registro();
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
            //rrn_tabla.append(rrn);
            ui->tabla->insertRow(fila);
            for (int i = 0; i < header.campos.size(); ++i) {
                int inc = header.campos.at(i).getLongitud();
                QString substring = registro.mid(offset,inc);
                ui->tabla->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
                if(header.key == i){
                    if(i != 0)
                        offset_registro += inc;
                    mw->index.insert(substring.trimmed(),QString::number(offset_registro));
                    offset_registro += header.getLongitud_registro();
                }
                offset += inc;
            }
            fila++;
        }else{
            offset += longitud_registro;
        }
    }

    updateIndex();
    filelectura.close();
}

void dialog_abrirArchivos::on_pushButton_2_clicked()//Agregar un nuevo registro
{
    try{
    QFile archivo_(header.direccion);
    qDebug() << header.direccion;
    archivo_.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out_(&archivo_);
    out_.seek(header.getAvaillist());
    int availlist = out_.readLine().toInt();
    qDebug() << "Availist == " << QString::number(availlist);
    archivo_.close();

    QStringList tokens;
    QString registro, campo_llave;
    for(int i=0;i< ui->tabla2->rowCount();i++){
        QTableWidgetItem* item = ui->tabla2->item(i,1);

        tokens.append(item->text());
        qDebug() << tokens.at(i);
    }
    qDebug()<<"El tamano de Campos"<<header.campos.size();
    for(int i=0;i<header.campos.size();i++){
        if("Entero"==(header.campos.at(i).getTipo())){
            qDebug()<<"Si Funciona";
            int i=tokens.at(i).toInt();
            qDebug()<<i;
        }
    }
    ui->tabla->insertRow(ui->tabla->rowCount());
    for(int i=0;i<tokens.size();i++){
        if(i==tokens.size()-1){
            if(header.campos.at(i).getLongitud()==tokens.at(i).size()){
                registro.append(tokens.at(i));
                ui->tabla->setItem(ui->tabla->rowCount()-1, i, new QTableWidgetItem(tokens.at(i)));
            }else{
                if(header.campos.at(i).getLongitud()>tokens.at(i).size()){
                    int diferencia=0;
                    diferencia=((header.campos.at(i).getLongitud())-tokens.at(i).size());
                    registro.append(tokens.at(i));
                    ui->tabla->setItem(ui->tabla->rowCount()-1, i, new QTableWidgetItem(tokens.at(i)));
                    for(int i=0;i<diferencia;i++){
                        registro.append(" ");
                    }
                }else{
                    QMessageBox::critical(this, "Error", "No Son las longitudes especificas");
                }
            }
        }else{
            if(header.campos.at(i).getLongitud()==tokens.at(i).size()){
                registro.append(tokens.at(i));
                ui->tabla->setItem(ui->tabla->rowCount()-1, i, new QTableWidgetItem(tokens.at(i)));
            }else{
                if(header.campos.at(i).getLongitud()>tokens.at(i).size()){
                    int diferencia=0;
                    diferencia=(header.campos.at(i).getLongitud())-(tokens.at(i).size());
                    registro.append(tokens.at(i));
                    ui->tabla->setItem(ui->tabla->rowCount()-1, i, new QTableWidgetItem(tokens.at(i)));
                    for(int i=0;i<diferencia;i++){
                        registro.append(" ");
                    }
                }else{
                    QMessageBox::critical(this, "Error", "No Son las longitudes especificas");
                }
            }
        }

    }

    campo_llave = ui->tabla2->item(header.key ,1)->text();
    ArbolB.insert(campo_llave.toInt());
    if(availlist == -1){
        qDebug()<<"Entro Aqui No estoy mal";
        QFile archivo(header.direccion);
        archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream out(&archivo);
        int offset = out.pos();
        out<<registro;
        archivo.close();
        //agregar al indice
        mw->index.insert(campo_llave,QString::number(offset));
        updateIndex();
    }else{
        rewrite(registro, availlist, campo_llave);
        updateIndex();
    }

    }catch(exception){
        QMessageBox::critical(this, "Error", "Esta Ingresando un String donde no se debe");
    }


}

void dialog_abrirArchivos::on_pushButton_3_clicked()
{
    QString hi;

    bool campoencontrado=false;
    int offset=0;
    if(ui->camposbox->currentText()==header.campo_llave){
        if(ArbolB.search(ui->textobuscar->text().toInt())!=NULL){
            qDebug()<<"se encontro";
            campoencontrado=true;
        }else{
            qDebug()<<"no se encontro";
            campoencontrado=false;
        }
        if(campoencontrado==true){
            QMapIterator<QString, QString> i(mw->index);
            while (i.hasNext()) {
                i.next();
                if(i.key().toInt()==(ui->textobuscar->text().toInt())){
                    offset=i.value().toInt();
                }
            }
        }
        QFile filelectura(header.direccion);
        filelectura.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&filelectura);
             in.seek(offset);
             hi=in.read(header.longitud_registro);
             qDebug()<<hi;



    /*ui->tablabuscar->clear();
    QString campo_buscar = ui->camposbox->currentText();
    QString registro_buscar = ui->textobuscar->text();
    int longitud_campo=0, inc = 0, fila = 0;
    QFile filelectura(header.direccion);
    filelectura.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&filelectura);

    for(int i = 0; i < header.campos.size(); i++){
        if(campo_buscar == header.campos.at(i).getNombre_campo()){
            longitud_campo = header.campos.at(i).getLongitud();
            break;
        }
        else
            inc += header.campos.at(i).getLongitud();
    }

    ui->tablabuscar->setColumnCount(header.campos.size());
    ui->tablabuscar->setRowCount(1);

    QStringList headers;


    for(int i = 0; i < header.campos.size(); i++){
        headers.append(header.campos.at(i).getNombre_campo());

    }

    ui->tablabuscar->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < header.campos.size(); i++){
        ui->tablabuscar->setColumnWidth(i, 200);
    }

    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.

    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.

    //Validando encontrar usando arbol y indices.
    //Validando encontrar usando arbol y indices.

    filelectura.seek(header.inicio_registro);
    while (!in.atEnd()) {
        QString registro = in.read(header.longitud_registro);
        qDebug() << "REGISTRO == " << registro;
        int offset = 0;
        if (registro.at(0) != '*') {
            //rrn_tabla.append(rrn);
            ui->tablabuscar->insertRow(fila);
            QString substring = registro.mid(inc, inc + longitud_campo);
            qDebug() << "CAMPO == " << substring;
            if(registro_buscar == substring){
                for (int i = 0; i < header.campos.size(); ++i) {
                    int incr = header.campos.at(i).getLongitud();
                    QString substrings = registro.mid(offset,incr);
                    ui->tablabuscar->setItem(fila,i,new QTableWidgetItem(substrings.trimmed()));
                    offset += inc;
                }
            }
            fila++;
        }else{
            offset += header.longitud_registro;
        }
    }



    filelectura.close();


    */
    /*
    }else{
    int bandera=0;
    while(!in.atEnd()){
        if(header.inicio_registro<=bandera){
            lectura+=in.readLine();
            qDebug() <<"Lectura De Registr"<<lectura.at(0);
    }else{
            in.readLine();
        }
        bandera++;
   }
    ui->tablabuscar->setColumnCount(header.campos.size());
    ui->tablabuscar->setRowCount(1);
    QStringList headers;


    for(int i = 0; i < header.campos.size(); i++){
        headers.append(header.campos.at(i).getNombre_campo());

    }
    ui->tablabuscar->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < header.campos.size(); i++){
        ui->tablabuscar->setColumnWidth(i, 200);

    }
    int itemsingresados=0;
    //ui->tablabuscar->setRowCount(lectura.size());
    for(int i=0;i<lectura.size();i++){
        QStringList tokens = lectura.at(i).split(',');
            if(tokens.at(ui->camposbox->currentIndex())==ui->textobuscar->text()){

                ui->tablabuscar->setRowCount(itemsingresados+1);
            for(int j=0;j<tokens.size();j++){
                QString campo=tokens.at(j);
                qDebug()<<campo;
                ui->tablabuscar->setItem(itemsingresados,j,new QTableWidgetItem(campo));

            }itemsingresados++;
           }
    }
*/

}
}

void dialog_abrirArchivos::on_pushButton_4_clicked()
{

    QTableWidget* table = ui->tabla;
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();
    int campo_llave = header.getKey();
    if(indexList.size() > 1){
        QModelIndex indice = indexList.at(0);
        QString llave = table->item(indice.row(),campo_llave)->text().trimmed();
        if (mw->index.size() > 0) {
            eliminarRegistro(llave);
            ArbolB.remove(llave.toInt());
            updateIndex();
        }
    }
    ui->tabla->removeRow(ui->tabla->currentRow());


}

void dialog_abrirArchivos::updateIndex(){
    //Guardar en el Indice
        ArbolB= BTree(32);
        QFile archivo(header.nombre_archivo + ".libx");
        qDebug() << "Nombre Archivo" << header.nombre_archivo;
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out2(&archivo);
        QMapIterator<QString, QString> i(mw->index);
        while (i.hasNext()) {
            i.next();
            qDebug() << "kEY" << i.key();
            ArbolB.insert(i.key().toInt());
            qDebug() << "Value " << i.value();
            out2 << i.key() << "," << i.value() << endl;
        }
        archivo.close();
}

bool dialog_abrirArchivos::eliminarRegistro(QString llave){

    QFile archivo(header.direccion);
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream in_out(&archivo);
    //leer cabeza del availlist
    in_out.seek(header.getAvaillist());
    QString availlist = in_out.readLine();
    int offset = mw->index.value(llave,"").toInt();
    if(!offset){
        qDebug()<<"no se pudo convertir el offset a int";
        return false;
    }
    int rrn = (offset - header.getInicio_registro()) / header.getLongitud_registro();
    qDebug()<<"cabeza de availlist: "<<availlist;
    qDebug()<<"registro a eliminar: "<<rrn;
    //reescribir cabeza del availlist
    in_out.seek(header.getAvaillist());
    QString str = QString::number(rrn);
    while (str.size() < 5) {
        str.append(' ');
    }
    in_out<<str;
    //marcar registro como borrado
    in_out.seek(offset);
    str = "*" + availlist;
    qDebug()<<"offset del registro a eliminar: "<<in_out.pos();
    in_out<<str;
    archivo.close();
    //eliminar registro del indice}
    mw->index.remove(llave);
    //llenarTabla();
    return true;
}

bool dialog_abrirArchivos::rewrite(QString registro, int &availlist, QString llave){
    //verificar si la llave ya existe en el indice
    if(mw->index.contains(llave)){
        qDebug()<<"la llave ya existe";
        return false;
    }
    //calcular el offset del registro a escribir
    int offset = header.getInicio_registro() + (availlist * header.getLongitud_registro());
    // abrir archivo
    QFile archivo(header.direccion);
    if (!archivo.open(QIODevice::ReadWrite| QIODevice::Text))
        return false;
    QTextStream in_out(&archivo);
    //obtener siguiente elemento del availlist
    in_out.seek(offset+1);
    QString rrn = in_out.read(5);
    //reescribir cabeza del availlist
    in_out.seek(header.getAvaillist());
    in_out<<rrn;
    //reescribir regsitro
    in_out.seek(offset);
    in_out<<registro;
    //agregar al indice
    mw->index.insert(llave,QString::number(offset));
    archivo.close();
    return true;
}


void dialog_abrirArchivos::on_pushButton_5_clicked()
{

    QString registro, campo_llave;
    int offset = header.inicio_registro + (ui->tabla->currentRow() * header.getLongitud_registro());
    QFile archivo(header.direccion);
    QStringList tokens;

    for(int j = 0; j < ui->tabla->columnCount(); j++){
        QTableWidgetItem* item = ui->tabla->item(ui->tabla->currentRow(),j);
        tokens.append(item->text());
        qDebug() << tokens.at(j);
    }


    for(int i = 0; i < tokens.size(); i++){
        if(tokens.at(i).size() == header.campos.at(i).getLongitud()){
            registro.append(tokens.at(i));

        }else if(tokens.at(i).size() < header.campos.at(i).getLongitud()){
            int diferencia=0;
            diferencia=((header.campos.at(i).getLongitud())-tokens.at(i).size());
            registro.append(tokens.at(i));
            for(int i=0;i<diferencia;i++){
                registro.append(" ");
            }
        }else{
            QMessageBox::critical(this, "Error", "No Son las longitudes especificas");
        }
    }

    archivo.open(QIODevice::ReadWrite| QIODevice::Text);
    campo_llave = ui->tabla->item(ui->tabla->currentRow(), header.key)->text();
    QTextStream in(&archivo);
    in.seek(offset);
    in << registro;
    mw->index.insert(campo_llave,QString::number(offset));
    updateIndex();
    archivo.close();
    QMessageBox::information(this, "Aviso", "Se ha modificado con exito.");
}




void dialog_abrirArchivos::on_pushButton_6_clicked()//Boton para compactar el archivo
{
    if(ui->change_filename->text() == ""){
        QMessageBox::critical(this, "Error", "Archivo sin Nombre");
    }else{

        QFile file(ui->change_filename->text() + ".dat");
        QFile indice(ui->change_filename->text() + ".libx");
        if (!indice.open(QIODevice::WriteOnly | QIODevice::Text)){
        }
        indice.close();
        int size_registro = 0;
        Header header_compactar = Header(ui->change_filename->text(), header.campos.size(), header.campos);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        QString registros;
        out << header.campos.size() << "\n";

        for(int i = 0; i < header.campos.size(); i++){
            out << header.campos.at(i).getNombre_campo() << ","
                << header.campos.at(i).getTipo() << ","
                << header.campos.at(i).getLongitud() << ","
                << header.campos.at(i).getEsllave() << "\n";
            size_registro += header.campos.at(i).getLongitud();
        }
        out << "longitud de registro, " << size_registro << "\n";
        out << "availlist,-1   "<<'\n';

        QFile newFile(header.direccion);
        newFile.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&newFile);
        in.seek(header.inicio_registro);
        int longitud_registro = header.getLongitud_registro(), inc = 0;
        int offset_registro = header.getInicio_registro();
        in.seek(header.inicio_registro);
        while (!in.atEnd()) {
            QString registro = in.read(longitud_registro);
            int offset = 0;
            if (registro.at(0) != '*') {
                for (int i = 0; i < header.campos.size(); ++i) {
                    int inc = header.campos.at(i).getLongitud();
                    QString substring = registro.mid(offset,inc);
                    out << substring;
                    offset += inc;
                }
            }else{
                offset += longitud_registro;
            }
        }
        file.flush();
        file.close();
        ui->change_filename->setText("");

    }
}
