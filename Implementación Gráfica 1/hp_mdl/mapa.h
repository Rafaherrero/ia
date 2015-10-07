#ifndef MAPA_H
#define MAPA_H

#include <vector>

class mapa
{
private:
    unsigned tamano_x_;
    unsigned tamano_y_;
    std::vector<std::vector<unsigned> > datos_;
public:
    mapa();
    mapa(unsigned,unsigned);//Se le pasa el tamaño del mapa
    void resize(unsigned,unsigned); //Cambiar el tamaño del mapa
    void generar_laberinto(); //Generar aleatoriamente con forma de laberinto
    void generar_aleatorio(unsigned); //Colocar obstáculos aleatoriamente
    void colocar_monstruos(unsigned); //Colocar una cantidad de monstruos en el mapa

    unsigned& get_x(void);
    unsigned& get_y(void);
};

#endif // MAPA_H
