#ifndef AGREGARARCHIVO_H
#define AGREGARARCHIVO_H

#include <QDialog>

namespace Ui {
class AgregarArchivo;
}

class AgregarArchivo : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarArchivo(QWidget *parent = 0);
    ~AgregarArchivo();

private:
    Ui::AgregarArchivo *ui;
};

#endif // AGREGARARCHIVO_H
