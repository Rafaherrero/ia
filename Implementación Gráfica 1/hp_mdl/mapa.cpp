#include "mapa.h"

mapa::mapa(void):
	tamano_x_(0),
	tamano_y_(0)
{
}

mapa::mapa(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y)
{
	datos_.resize(x);
	for(auto &i : datos_)
		i.resize(y);
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

}

void mapa::generar_laberinto(void)
{

}

void mapa::generar_laberinto(QPoint posicion_copa)
{

}

void mapa::generar_laberinto(QPoint posicion_copa, QPoint posicion_harry)
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

QImage mapa::get_tile(unsigned x, unsigned y)
{
	QString tile = "img/grass_wall.png";

	if (!existe_imagen(tile)){
		std::cerr << "No existe esa ruta" << std::endl;
	}

	QImage image(tile);
	return image;
}
