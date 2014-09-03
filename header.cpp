#include "header.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

Header::Header()
{
}

Header::Header(QString nombre_archivo, int n_campos)
{
    this->nombre_archivo = nombre_archivo;
    numero_campos = n_campos;
}

Header::Header(QString direccion)
{
    longitud_registro = 0;
    QFile file(direccion);
        this->direccion=direccion;
         file.open(QIODevice::ReadWrite | QIODevice::Text);
         QTextStream in(&file);
         QString line = in.readLine();
         QStringList tokens;
         int total_lineas = line.toInt();
         for(int i = 0; i < total_lineas; i++){
             line = in.readLine();
             tokens = line.split(",");
             Campos campo = Campos();
             campo.setNombre_campo(tokens.at(0));
             campo.setTipo(tokens.at(1));
             campo.setLongitud(tokens.at(2).toInt());
             longitud_registro += tokens.at(2).toInt();

             campo.setEsllave(tokens.at(3).toInt());
             campos.append(campo);
             qDebug() << line;
         }
         longitud_registro +=total_lineas;

            line =in.readLine();
            if(line.at(0)=='&'){
                line.remove(0,1);
                availlist=line.toInt();
                qDebug() << availlist;
                inicio_registro=total_lineas+2;
        }
            in.flush();
            file.close();

    }

int Header::getInicio_registro() const
{
    return inicio_registro;
}

void Header::setInicio_registro(int value)
{
    inicio_registro = value;
}

int Header::getAvaillist() const
{
    return availlist;
}

void Header::setAvaillist(int value)
{
    availlist = value;
}

int Header::getLongitud_registro() const
{
    return longitud_registro;
}

void Header::setLongitud_registro(int value)
{
    longitud_registro = value;
}

int Header::getNumero_campos() const
{
    return numero_campos;
}

void Header::setNumero_campos(int value)
{
    numero_campos = value;
}

QString Header::getNombre_archivo() const
{
    return nombre_archivo;
}

void Header::setNombre_archivo(const QString &value)
{
    nombre_archivo = value;
}

