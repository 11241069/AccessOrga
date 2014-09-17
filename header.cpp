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

Header::Header(QString nombre_archivo, int n_campos, QList <Campos> campos)
{
    this->nombre_archivo = nombre_archivo;
    numero_campos = n_campos;
    this->campos = campos;
}

Header::Header(QString direccion)
{
    int pleca;
    QString filename;
    for(int i = 0; i < direccion.size(); i++){
        if(direccion.at(i) == '/'){
            pleca = i;
        }
    }
    for(int i = pleca + 1; i < direccion.size() - 4; i++){
        filename.append(direccion.at(i));
    }

    nombre_archivo = filename;
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

         for(int i = 0; i < campos.size(); i++){
             if(campos.at(i).getEsllave() == 1){
                 key = i;
                 campo_llave = campos.at(i).getNombre_campo();
             }
         }


         while (!in.atEnd()) {
             QString str = in.readLine();
             if (str.contains("longitud de registro")) {
                 availlist = in.pos() + 10;
             } else if (str.contains("availlist")) {
                 inicio_registro = in.pos();
                 break;
             }
         }

            in.flush();
            file.close();



}
QString Header::getCampo_llave() const
{
    return campo_llave;
}

void Header::setCampo_llave(const QString &value)
{
    campo_llave = value;
}

int Header::getKey() const
{
    return key;
}

void Header::setKey(int value)
{
    key = value;
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

