#ifndef CAMPOS_H
#define CAMPOS_H
#include <QString>

class Campos
{
public:
    Campos();
    Campos(QString, QString, int, int);
    QString nombre_campo;
    QString tipo;
    int longitud;
    int esllave;
    QString getNombre_campo() const;
    void setNombre_campo(const QString &value);
    QString getTipo() const;
    void setTipo(const QString &value);
    int getLongitud() const;
    void setLongitud(int value);
    int getEsllave() const;
    void setEsllave(int value);
};

#endif // CAMPOS_H
