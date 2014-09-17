#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_nuevoarchivo.h"
#include "dialog_abrirarchivos.h"
#include "dialog_nuevoregistro.h"
#include "QFileDialog"
#include <QString>
#include "header.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog_nuevoarchivo crear_Archivo(this);
    crear_Archivo.setModal(true);
    crear_Archivo.exec();
}

void MainWindow::on_pushButton_2_clicked()
{

    dialog_abrirArchivos abrir_Archivo(this);
    abrir_Archivo.setModal(true);
    abrir_Archivo.exec();

}

void MainWindow::on_pushButton_3_clicked()//Boton para ir al dialog de cruzar
{
    dialog_nuevoRegistro nuevo_Registro(this);
    nuevo_Registro.setModal(true);
    nuevo_Registro.exec();
}
