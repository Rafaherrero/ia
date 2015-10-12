#include "mapa.h"

/*

class tabla_t{
private:
	std::vector<std::vector<nodo_mapa> > tabla_;
	unsigned tamano_x_;
	unsigned tamano_y_;
public:
	tabla_t(void);
	tabla_t(unsigned x, unsigned y);
	void resize(unsigned x, unsigned y);
	nodo_mapa& at(QPoint coord);
	nodo_mapa& at_dir(QPoint coord, id_t dir);
};

*/

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
	return (celda.x() > 0 && celda.y() > 0) && (celda.x() < tamano_x_ && celda.y() < tamano_y_);
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

mapa::mapa(void):
	tamano_x_(0),
	tamano_y_(0),
	inicio_(0,0),
	final_(0,0)
{
}

mapa::mapa(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y),
	setos_(x,y, ID_MAPA_OTROS_VACIO),
	entidades_(x,y, ID_MAPA_OTROS_VACIO)
{
}

bool mapa::existe_imagen(QString ruta)
{
	QFileInfo checkFile(ruta);
	//Hay que saber si el fichero existe y no es un directorio
	if(checkFile.exists() && checkFile.isFile()){
		return true;
	}
	else{
		return false;
	}
}

void mapa::importar_imagenes(void)
{
	//TODO
}

void mapa::generar_laberinto(void)
{
	//Inicializar datos
	setos_.clear(ID_GENERACION_VACIO);

	explora_vecinos_y_excava(inicio_);

	//TODO: Quitar el chivato este
	setos_.imprime(std::cout);
}

void mapa::explora_vecinos_y_excava(QPoint celda)
{
	setos_.at(celda).valor_ = ID_GENERACION_VISITADO;
	unsigned explorar = 0;
	while(tiene_vecinos_sin_visitar(celda)){
		explorar = qrand()%4;
		if(setos_.at_dir(celda, explorar).valor_ == ID_GENERACION_VACIO)
			explora_vecinos_y_excava(setos_.at_dir(celda, explorar).coord_);
	}

	return;
}

bool mapa::tiene_vecinos_sin_visitar(QPoint celda)
{
	//Hay que verificar que, en los cuatro sentidos, es alcanzable y además no ha sido visitada.
	if(setos_.alcanzable(celda, ID_ORIENTACION_ARRIBA) && setos_.at_dir(celda, ID_ORIENTACION_ARRIBA).valor_ == ID_GENERACION_VACIO)
		return true;
	if(setos_.alcanzable(celda, ID_ORIENTACION_ABAJO) && setos_.at_dir(celda, ID_ORIENTACION_ABAJO).valor_ == ID_GENERACION_VACIO)
		return true;
	if(setos_.alcanzable(celda, ID_ORIENTACION_DERECHA) && setos_.at_dir(celda, ID_ORIENTACION_DERECHA).valor_ == ID_GENERACION_VACIO)
		return true;
	if(setos_.alcanzable(celda, ID_ORIENTACION_IZQUIERDA) && setos_.at_dir(celda, ID_ORIENTACION_IZQUIERDA).valor_ == ID_GENERACION_VACIO)
		return true;
	return false;
}

void mapa::generar_aleatorio(unsigned porcentaje)
{
	//TODO
}

void mapa::colocar_monstruos(unsigned cantidad_mon)
{
	//TODO
}

unsigned& mapa::get_x(void)
{
	return tamano_x_;
}

unsigned& mapa::get_y(void)
{
	return tamano_y_;
}

QImage mapa::get_tile_seto(QPoint celda)
{
	/*
	QString tile = "img/grass_wall.png";

	if (!existe_imagen(tile)){
		std::cerr << "No existe esa ruta" << std::endl;
	}

	QImage image(tile);
	return image;

	FIXME: Esto es para cargar una imagen.*/
	switch (setos_.at(celda).valor_) {
		case ID_MAPA_OTROS_COMPLETO: return imagenes_.otros_.completo_; break;
		default: break;
	}
	return imagenes_.otros_.completo_;
}
