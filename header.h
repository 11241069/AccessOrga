#ifndef HEADER_H
#define HEADER_H
#include <QList>
#include "campos.h"
#include <QFile>

class Header
{
public:
    Header();
    Header(QString nombre_archivo, int n_campos, QList <Campos> campos);
    Header(QString);
    QString direccion;
    QString nombre_archivo;
    QString campo_llave;
    int key;
    int numero_campos;
    QList <Campos> campos;
    int longitud_registro;
    int availlist;
    int inicio_registro;
    QString getNombre_archivo() const;
    void setNombre_archivo(const QString &value);
    int getNumero_campos() const;
    void setNumero_campos(int value);
    int getLongitud_registro() const;
    void setLongitud_registro(int value);
    int getAvaillist() const;
    void setAvaillist(int value);
    int getInicio_registro() const;
    void setInicio_registro(int value);
    int getKey() const;
    void setKey(int value);
    QString getCampo_llave() const;
    void setCampo_llave(const QString &value);
};

#endif // HEADER_H
