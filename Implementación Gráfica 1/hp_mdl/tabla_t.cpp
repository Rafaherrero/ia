#include "tabla_t.h"

tabla_t::tabla_t(void):
	tamano_x_(0),
	tamano_y_(0)
{}


tabla_t::tabla_t(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y)
{
	tabla_.resize(x);
	for(auto &i : tabla_)
		i.resize(y);
	actualizar_puntos();
}

tabla_t::tabla_t(unsigned x, unsigned y, id_t val):
	tamano_x_(x),
	tamano_y_(y)
{
	tabla_.resize(x);
	for(auto &i : tabla_)
		i.resize(y);
	for(auto &i : tabla_)
		for(auto &j : i)
			j.valor_ = val;
	actualizar_puntos();
}

void tabla_t::actualizar_puntos(void)
{
	for(unsigned i = 0; i < tamano_x_; i++){
		for(unsigned j = 0; j < tamano_y_; j++){
			tabla_[i][j].coord_.setX(i);
			tabla_[i][j].coord_.setY(j);
		}
	}
}

void tabla_t::resize(unsigned x, unsigned y)
{
	tabla_.resize(x);
	for(auto &i : tabla_)
		i.resize(y);
	actualizar_puntos();
}

void tabla_t::desplazar_punto(QPoint& punto, id_t dir)
{
	switch(dir){
	case ID_ORIENTACION_ARRIBA: punto.ry()++; break;
	case ID_ORIENTACION_ABAJO: punto.ry()--; break;
	case ID_ORIENTACION_DERECHA: punto.rx()++; break;
	case ID_ORIENTACION_IZQUIERDA: punto.rx()--; break;
	case ID_ORIENTACION_ABA_IZQ: punto.ry()--; punto.rx()--; break;
	case ID_ORIENTACION_ARR_IZQ: punto.ry()++; punto.rx()--; break;
	case ID_ORIENTACION_ARR_DER: punto.ry()++; punto.rx()++; break;
	case ID_ORIENTACION_ABA_DER: punto.ry()--; punto.rx()++; break;
	}
}

nodo_mapa& tabla_t::at(QPoint coord)
{
	return tabla_[coord.x()][coord.y()];
}

nodo_mapa& tabla_t::at_dir(QPoint coord, id_t dir)
{
	desplazar_punto(coord, dir);
	return tabla_[coord.x()][coord.y()];
}

unsigned tabla_t::t_x(void)
{
	return tamano_x_;
}

unsigned tabla_t::t_y(void)
{
	return tamano_y_;
}

void tabla_t::clear(id_t val)
{
	for(auto &i : tabla_)
		for(auto &j : i)
			j.valor_ = val;
}

bool tabla_t::alcanzable(QPoint celda)
{
	bool expr = (celda.x() >= 0 && celda.y() >= 0) && (celda.x() < (int)tamano_x_ && celda.y() < (int)tamano_y_); //Dejarlo asi para el debugger
	return expr;
}

bool tabla_t::alcanzable(QPoint celda, id_t dir)
{
	desplazar_punto(celda, dir);

	return alcanzable(celda);
}

void tabla_t::imprime(std::ostream& os)
{
	for(auto &i : tabla_){
		for(auto &j : i)
			os << j.valor_ << " ";
		os << std::endl;
	}
}
