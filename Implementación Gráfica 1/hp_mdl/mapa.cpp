#include "mapa.h"

mapa::mapa():
    tamano_x_(0),
    tamano_y_(0)
{}

mapa::mapa(unsigned x, unsigned y):
    tamano_x_(x),
    tamano_y_(y)
{
    datos_.resize(x);
    for(auto &i : datos_)
        i.resize(y);
}

void mapa::generar_laberinto()
{

}

void mapa::generar_aleatorio(unsigned porcentaje)
{

}

void mapa::colocar_monstruos(unsigned cantidad_mon)
{

}

unsigned& mapa::get_x(void)
{
    return tamano_x_;
}

unsigned& mapa::get_y(void)
{
    return tamano_y_;
}
