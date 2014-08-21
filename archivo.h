#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <QFile>
#include <QList>
#include "campo.h"
class Archivo
{
private:
    QFile* file;
    QList<Campo> campos;
public:
    Archivo();
    void camposset(Campo a);
    QList<Campo> camposget();
    void camposclear(QList<Campo>* a);
    QFile qfileget();
    void qfileset(QFile a);
};

#endif // ARCHIVO_H
