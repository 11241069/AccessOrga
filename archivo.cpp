#include "archivo.h"

Archivo::Archivo()
{
}
void Archivo::camposset(Campo a){
    campos.append(a);
}
QList Archivo::camposget(){
    return campos;
}
void Archivo::camposclear(QList<Campo>* a){
    campos=a;
}

QFile Archivo::qfileget(){
    return file;
}
void Archivo::qfileset(QFile &a){
    file=a;
}
