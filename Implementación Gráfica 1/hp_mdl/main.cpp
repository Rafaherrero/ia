#include "ventanaprincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
    w.show();
    //ACABO DE HACER UN SUPER CAMBIO, impementado

    return a.exec();
}
