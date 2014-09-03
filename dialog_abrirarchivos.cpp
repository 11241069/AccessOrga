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
using namespace std;

dialog_abrirArchivos::dialog_abrirArchivos(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::dialog_abrirArchivos)
{
    ui->setupUi(this);
    mw = parent;

}

dialog_abrirArchivos::~dialog_abrirArchivos()
{
    delete ui;
}

void dialog_abrirArchivos::on_pushButton_clicked()
{
    QStringList lectura;
    QString archivo = QFileDialog::getOpenFileName(this, tr("Open File"));
    header = Header(archivo);
    QFile filelectura(header.direccion);
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
    for(int i=0;i<lectura.size();i++){
        QStringList tokens = lectura.at(i).split(',');
            for(int j=0;j<tokens.size();j++){
                QString campo=tokens.at(j);
                qDebug()<<campo;
                ui->tabla->setItem(i,j,new QTableWidgetItem(campo));
            }
    }

    filelectura.close();
}

void dialog_abrirArchivos::on_pushButton_2_clicked()
{
    QStringList tokens;
    for(int i=0;i< ui->tabla2->rowCount();i++){
        QTableWidgetItem* item = ui->tabla2->item(i,1);
        tokens.append(item->text());
        qDebug() << tokens.at(i);
    }
    QFile archivoregistros(header.direccion);
    if (!archivoregistros.open(QIODevice::WriteOnly | QIODevice::Append| QIODevice::Text))
        return;
    QTextStream out(&archivoregistros);

    for(int i=0;i<tokens.size();i++){
        if(i==tokens.size()-1){
          if(header.campos.at(i).getLongitud()==tokens.at(i).size()){
              out<<tokens.at(i)<<"\n";
          }else{
          if(header.campos.at(i).getLongitud()>tokens.at(i).size()){
              int diferencia=0;
              diferencia=((header.campos.at(i).getLongitud())-tokens.at(i).size());
              out<<tokens.at(i);
              for(int i=0;i<diferencia;i++){
              out<<'-';
              }
              out<<"\n";
          }else{
              QMessageBox::critical(this, "Error", "No Son las longitudes especificas");
          }
          }
        }else{
            if(header.campos.at(i).getLongitud()==tokens.at(i).size()){
                out<<tokens.at(i)<<',';
            }else{
            if(header.campos.at(i).getLongitud()>tokens.at(i).size()){
                int diferencia=0;
                diferencia=(header.campos.at(i).getLongitud())-(tokens.at(i).size());
                out<<tokens.at(i);
                for(int i=0;i<diferencia;i++){
                out<<'-';
                }
                out<<',';
            }else{
                QMessageBox::critical(this, "Error", "No Son las longitudes especificas");
            }
            }
        }
    }

    archivoregistros.flush();
    archivoregistros.close();
}

void dialog_abrirArchivos::on_pushButton_3_clicked()
{
    ui->tablabuscar->clear();
    QStringList lectura;
    QFile filelectura(header.direccion);
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
    filelectura.close();
}

void dialog_abrirArchivos::on_pushButton_4_clicked()
{
    QString buscar=ui->tablabuscar->currentItem()->text();
    QFile fileborrar(header.direccion);
    if(!fileborrar.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"NO lo Podemos Abrir";
    }else{
        qDebug()<<"Se Abrio";
    }
    QTextStream in(&fileborrar);
    int lines=0;
    int borrar=0;
    int mover=0;
    int calculando=0;
    while(!in.atEnd()){
        if(header.inicio_registro<=lines){
        QStringList tokens;
        tokens=in.readLine().split(',');
            if(buscar==tokens.at(0)){
                   borrar=calculando;
            }
            calculando++;
        }else{
            in.readLine();

            mover++;
        }
    lines++;
    }
    in.flush();
    in.reset();
    fileborrar.seek(0);
    fileborrar.close();
    QFile a(header.direccion);
    a.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream aps(&a);
    int probando=0;
    for(int i=0;i<mover;i++){
        QString hola=aps.readLine();
        probando=aps.pos();
        qDebug()<<probando;
        qDebug()<<mover;
    }
    if(borrar==0){
        probando+=borrar*header.longitud_registro;
    a.seek(probando);
    }else{
        probando+=borrar*header.longitud_registro+2;
    a.seek(probando);
    }
    QString avail="*"+header.availlist;

    a.write("*");

}
