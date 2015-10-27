#include "tabla_t.h"

tabla_t::tabla_t(void):
	tam_x_(0),
	tam_y_(0),
	def_(0)
{}


tabla_t::tabla_t(unsigned x, unsigned y):
	tam_x_(x),
	tam_y_(y),
	def_(0)
{
	resize(x, y);
}

tabla_t::tabla_t(unsigned x, unsigned y, id_t val):
	tam_x_(x),
	tam_y_(y),
	def_(val)
{
	resize(x, y);
	clear();
}

void tabla_t::resize(unsigned x, unsigned y)
{
	tabla_.resize(x);
	for(auto &i : tabla_)
		i.resize(y);
	tam_x_ = x;
	tam_y_ = y;
}

id_t& tabla_t::at(QPoint coord)
{
	return tabla_[coord.x()][coord.y()];
}

id_t& tabla_t::at(QPoint coord, id_t sentido)
{
	coord = common::QP(coord, sentido);
	return tabla_[coord.x()][coord.y()];
}

unsigned tabla_t::tam_x(void)
{
	return tam_x_;
}

unsigned tabla_t::tam_y(void)
{
	return tam_y_;
}

void tabla_t::clear(void)
{
	for(auto &i : tabla_)
		for(auto &j : i)
			j = def_;
}

void tabla_t::clear(id_t val)
{
	for(auto &i : tabla_)
		for(auto &j : i)
			j = val;
}

bool tabla_t::alcanzable(QPoint celda)
{
	return (celda.x() >= 0 && celda.y() >= 0) && ((unsigned)celda.x() < tam_x_ && (unsigned)celda.y() < tam_y_); //Dejarlo asi para el debugger;
}

bool tabla_t::alcanzable(QPoint celda, id_t sentido)
{
	return alcanzable(common::QP(celda, sentido));
}

bool tabla_t::alcanzable_bor(QPoint celda)
{
	return (celda.x() >= 1 && celda.y() >= 1) && ((unsigned)celda.x() < tam_x_-1 && (unsigned)celda.y() < tam_y_-1); //Dejarlo asi para el debugger
}

bool tabla_t::alcanzable_bor(QPoint celda, id_t sentido)
{
	return alcanzable_bor(common::QP(celda, sentido));
}

void tabla_t::imprime(std::ostream& os)
{
	for(unsigned i = 0; i < tam_y_; i++){
		for(unsigned j = 0; j < tam_x_; j++){
			os << tabla_[j][i] << " ";
		}
		os << std::endl;
	}
}
