#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <iostream>
#include <QImage>
#include <QPoint>

#include "exceptions.h"
#include "common.h"

class mapa
{
private:
    unsigned tamano_x_;
    unsigned tamano_y_;
    std::vector<std::vector<unsigned> > datos_;
private:
	void corregir_posicion(void); //Si sobra tiempo
	bool existe_imagen(QString);
	void importar_imagenes(void);
public:
	mapa(void);
	mapa(unsigned,unsigned);
	mapa(QPoint);//Se le pasa el tamaño del mapa
    void resize(unsigned,unsigned); //Cambiar el tamaño del mapa
    void generar_laberinto(); //Generar aleatoriamente con forma de laberinto
	void generar_laberinto(QPoint); //Generar aleatoriamente con la copa en un lugar
	void generar_laberinto(QPoint, QPoint); //Generar aleatoriamente el laberinto sabiendo la entrada y salida
	void generar_aleatorio(unsigned); //Colocar los setos aleatoriamente (sin forma de laberinto)
    void colocar_monstruos(unsigned); //Colocar una cantidad de monstruos en el mapa

	QImage get_tile(unsigned, unsigned);

    unsigned& get_x(void);
    unsigned& get_y(void);
};

#endif // MAPA_H
