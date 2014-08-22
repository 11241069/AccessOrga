#include "Campos.h"

Campos::Campos()
{
}

Campos::Campos(QString nombre_campo, QString tipo, int longitud, int esllave)
{
    this->nombre_campo = nombre_campo;
    this->tipo = tipo;
    this->longitud = longitud;
    this->esllave = esllave;
}

int Campos::getEsllave() const
{
    return esllave;
}

void Campos::setEsllave(int value)
{
    esllave = value;
}

int Campos::getLongitud() const
{
    return longitud;
}

void Campos::setLongitud(int value)
{
    longitud = value;
}

QString Campos::getTipo() const
{
    return tipo;
}

void Campos::setTipo(const QString &value)
{
    tipo = value;
}

QString Campos::getNombre_campo() const
{
    return nombre_campo;
}

void Campos::setNombre_campo(const QString &value)
{
    nombre_campo = value;
}
