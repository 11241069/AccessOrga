#ifndef AGREGARARCHIVO_H
#define AGREGARARCHIVO_H
#include <QList>
#include "qstring.h"
#include "campo.h"
#include "archivo.h"
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
    QList<Campo> campos;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AgregarArchivo *ui;
};

#endif // AGREGARARCHIVO_H
