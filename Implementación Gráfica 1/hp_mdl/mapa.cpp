#include "mapa.h"

mapa::mapa(void):
	tamano_x_(0),
	tamano_y_(0),
	inicio_(0,0),
	final_(0,0)
{
}

mapa::mapa(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y)
{
	datos_.resize(x);
	for(auto &i : datos_)
		i.resize(y, MAPA_ID_OTROS_VACIO);
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
	//FIXME
}

void mapa::generar_laberinto(void)
{
	//Bloquear todo
	for(auto &i : datos_)
		for(auto &j : i)
			j = MAPA_ID_SI_HAY_SETO;

	QPoint dummy(0,0);
	explora_vecinos_y_excava(dummy);

	for(auto &i : datos_){
		for(auto &j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

void mapa::explora_vecinos_y_excava(QPoint punto_actual, QPoint punto_anterior)
{
	//Revisar que no está caerca del borde
	if(punto_actual.x() == 0)
		return;
	if(punto_actual.x() == (int)(tamano_x_-1))
		return;
	if(punto_actual.y() == 0)
		return;
	if(punto_actual.y() == (int)(tamano_y_-1))
		return;

	if(existe_alrededor(punto_actual, MAPA_ID_NO_HAY_SETO, punto_anterior))
		return;

	unsigned siguiente_a_explorar;

	siguiente_a_explorar = qrand()%4;

	switch(esta_la_copa_alrededor(punto_actual)){ //Si estamos al lado de la copa, ocuparla inmediatamente
	case MAPA_ID_ARRIBA: siguiente_a_explorar = MAPA_ID_ARRIBA; break;
	case MAPA_ID_ABAJO: siguiente_a_explorar = MAPA_ID_ABAJO; break;
	case MAPA_ID_DERECHA: siguiente_a_explorar = MAPA_ID_DERECHA; break;
	case MAPA_ID_IZQUIERDA: siguiente_a_explorar = MAPA_ID_IZQUIERDA; break;
	default: break;
	}

	datos_[punto_actual.x()][punto_actual.y()] = MAPA_ID_NO_HAY_SETO;



	return;
}

bool mapa::existe_alrededor(QPoint celda, unsigned valor, QPoint omitir)
{
	if(datos_[celda.x()+1][celda.y()] == valor)
		if(celda.x()+1 != omitir.x() && celda.y() == omitir.y())//FIXME, LO DEJE AQUI
			return true;
	if(datos_[celda.x()-1][celda.y()] == valor)
		if(celda.x()-1 != omitir.x() && celda.y() == omitir.y())//FIXME, LO DEJE AQUI
			return true;
	if(datos_[celda.x()][celda.y()-1] == valor)
		if(celda.x() != omitir.x() && celda.y()-1 == omitir.y())//FIXME, LO DEJE AQUI
			return true;
	if(datos_[celda.x()][celda.y()+1] == valor)
		return true;
	return false;
}

unsigned mapa::esta_la_copa_alrededor(QPoint celda)
{
	if(datos_[celda.x()+1][celda.y()] == MAPA_ID_COPA)
		return MAPA_ID_DERECHA;
	if(datos_[celda.x()-1][celda.y()] == MAPA_ID_COPA)
		return MAPA_ID_IZQUIERDA;
	if(datos_[celda.x()][celda.y()-1] == MAPA_ID_COPA)
		return MAPA_ID_ABAJO;
	if(datos_[celda.x()][celda.y()+1] == MAPA_ID_COPA)
		return MAPA_ID_ARRIBA;
}

void mapa::generar_laberinto(QPoint posicion_copa)
{
	//FIXME
}

void mapa::generar_laberinto(QPoint posicion_copa, QPoint posicion_harry)
{
	//FIXME
}

void mapa::generar_aleatorio(unsigned porcentaje)
{
	//FIXME
}

void mapa::colocar_monstruos(unsigned cantidad_mon)
{
	//FIXME
}

unsigned& mapa::get_x(void)
{
	return tamano_x_;
}

unsigned& mapa::get_y(void)
{
	return tamano_y_;
}

QImage mapa::get_tile(QPoint coords)
{
	QString tile = "img/grass_wall.png";

	if (!existe_imagen(tile)){
		std::cerr << "No existe esa ruta" << std::endl;
	}

	QImage image(tile);
	return image;
}
