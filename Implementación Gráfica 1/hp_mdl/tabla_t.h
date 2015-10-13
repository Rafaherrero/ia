#ifndef TABLA_T_H
#define TABLA_T_H

#include <vector>
#include <iostream>
#include <QPoint>

#include "common.h"

struct nodo_mapa{
	QPoint coord_;
	id_t valor_;
};

class tabla_t{
private:
	std::vector<std::vector<nodo_mapa> > tabla_;
	unsigned tamano_x_;
	unsigned tamano_y_;
	void actualizar_puntos(void);
	void desplazar_punto(QPoint& punto, id_t dir);
public:
	tabla_t(void);
	tabla_t(unsigned x, unsigned y);
	tabla_t(unsigned x, unsigned y, id_t val);
	void resize(unsigned x, unsigned y);
	nodo_mapa& at(QPoint coord);
	nodo_mapa& at_dir(QPoint coord, id_t dir);
	unsigned t_x(void);
	unsigned t_y(void);
	void clear(id_t val);
	bool alcanzable(QPoint celda);
	bool alcanzable(QPoint celda, id_t dir);
	void imprime(std::ostream& os);
};

#endif // TABLA_T_H
