#ifndef CAMPO_H
#define CAMPO_H
#include "qstring.h"

class Campo
{
public:
    Campo();
    QString nombrecampo;
    QString tipo;
    int longitud;
    bool esllave;

};

#endif // CAMPO_H
