#ifndef TABLA_T_H
#define TABLA_T_H

#include <vector>
#include <iostream>
#include <QPoint>

#include "common.h"

class tabla_t{
private:
	std::vector<std::vector<id_t> > tabla_;
	unsigned tam_x_;
	unsigned tam_y_;
	id_t def_;
public:
	tabla_t(void); //Constructor vacío
	tabla_t(unsigned x, unsigned y); //Se le pasa el tamaño de las x y las y
	tabla_t(unsigned x, unsigned y, id_t def); //Se le pasa el tamaño y el valor por defecto
	void resize(unsigned x, unsigned y); //Cambiar el tamaño
	QPoint dir(QPoint punto, id_t sentido); //Se utiliza para conseguir las coordenadas de un punto en una determinada dirección/sentido
	id_t& at(QPoint coord); //Se obtiene el valor de un punto concreto
	id_t& at(QPoint coord, id_t sentido); //Se obtiene el valor de un punto en una dirección
	bool alcanzable(QPoint celda); //Devuelve si un punto está dentro del rango de la tabla
	bool alcanzable(QPoint celda, id_t sentido); //devuelve si un punto en una dirección está dentro del rango de la tabla
	unsigned tam_x(void); //devuelve el tamaño de x
	unsigned tam_y(void); //devuelve el tamaño de y
	void clear(id_t val); //Convierte todas las celdas a un valor "val"
	void imprime(std::ostream& os); //imprime la tabla por la salida.
};

#endif // TABLA_T_H
