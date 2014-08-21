#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agregararchivo.h"
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

void MainWindow::on_actionNuevo_Archivo_triggered()
{
    AgregarArchivo *agregar= new AgregarArchivo;
    agregar->exec();
}
