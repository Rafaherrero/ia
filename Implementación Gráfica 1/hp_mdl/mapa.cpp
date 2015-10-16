#include "mapa.h"

//========================================================
//                   Clase mapa
//========================================================

mapa::mapa(void):
	tamano_x_(0),
	tamano_y_(0),
	inicio_(1,1),
	final_(1,1)
{
}

mapa::mapa(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y),
	setos_(x,y, ID_MAPA_OTROS_VACIO),
	entidades_(x,y, ID_MAPA_OTROS_VACIO),
	inicio_(1,1),
	final_(1,1)
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
	std::cout << "Corrigiendo las posiciones" << std::endl;
	terminar_generar();
	corregir_posiciones();
	setos_.imprime(std::cout);
}

void mapa::explora_vecinos_y_excava(QPoint celda) //TODO: Comprobar que funciona
{
	setos_.at(celda) = ID_GENERACION_VISITADO;
	while(existe_casilla_ocupable(celda))
		explora_vecinos_y_excava(casilla_ocupable(celda));
	setos_.at(celda) = ID_GENERACION_MARCADO;
	return;
}

bool mapa::existe_casilla_ocupable(QPoint celda)
{
	QPoint error(-1, -1);
	if(casilla_ocupable(celda) == error)
		return false;
	return true;
}

QPoint mapa::casilla_ocupable(QPoint celda)
{
	unsigned desplazamiento = random();
	for(unsigned i = 0; i < 4; i++){ //Para cada dirección
		unsigned i_e = (i+desplazamiento)%4; //Obtener un número aleatorio y a partir de ahí, rotar
		if(setos_.alcanzable(celda, i_e)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			QPoint revisar = setos_.dir(celda, i_e);
			id_t comp = setos_.at(revisar);
			if(comp == ID_GENERACION_VACIO && (comp != ID_GENERACION_VISITADO) && (comp != ID_GENERACION_MARCADO)){
				std::cout << "Vamos a revisar (" << celda.x() << ", " << celda.y() << ")" << std::endl;
				if(!tienes_adyacentes(revisar, i_e))
					return(revisar);
			}
			//Si tiene adyacentes, mirar en otra dirección
		}
	}
	QPoint dummy(-1,-1); //Si no tiene adyacentes, devolver un nulo (-1,-1)
	return dummy;
}

bool mapa::tienes_adyacentes(QPoint celda, unsigned origen) //FIXME
{
	unsigned desplazamiento = 0;
	switch (origen) {
	case ID_ORIENTACION_ARRIBA:
		desplazamiento+=4;
		break;
	case ID_ORIENTACION_DERECHA:
		desplazamiento+=6;
		break;
	case ID_ORIENTACION_IZQUIERDA:
		desplazamiento+=2;
		break;
	default:
		break;
	}

	unsigned cantidad_adyacentes = 0;
	for(unsigned i = 0; i < 6; i++){ //por cada dirección (incluyendo las esquinas)
		std::cout << "Vas a mirar a: " << convertir_reloj(i) << std::endl;
		QPoint mirando = setos_.dir(celda, convertir_reloj(i+desplazamiento));
		if(setos_.alcanzable(mirando)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			if(setos_.at(mirando) == ID_GENERACION_VISITADO || setos_.at(mirando) == ID_GENERACION_MARCADO)
				cantidad_adyacentes++;
			if(cantidad_adyacentes > 1)
				return true; //Si pasamos de 1 adyacentes (por el que vinimos), tiene adyacentes
		}
	}
	return false;
}

id_t mapa::convertir_reloj(unsigned i)
{
	i = i % 8;
	id_t final;
	switch(i){
	case 0: final = ID_ORIENTACION_DERECHA; break;
	case 1: final = ID_ORIENTACION_ABA_DER; break;
	case 2: final = ID_ORIENTACION_ABAJO; break;
	case 3: final = ID_ORIENTACION_ABA_IZQ; break;
	case 4: final = ID_ORIENTACION_IZQUIERDA; break;
	case 5: final = ID_ORIENTACION_ARR_IZQ; break;
	case 6: final = ID_ORIENTACION_ARRIBA; break;
	case 7: final = ID_ORIENTACION_ARR_DER; break;
	}
	return final;
}

void mapa::terminar_generar(void)
{
	for(unsigned i = 0; i < tamano_y_; i++){
		for(unsigned j = 0; j < tamano_x_; j++){
			if(i == 0 || j ==0 || i == tamano_y_-1 || j == tamano_x_-1){
				QPoint aux(i, j);
				setos_.at(aux) = ID_GENERACION_VACIO;
			}
		}
	}
}

unsigned long mapa::mix(unsigned long a, unsigned long b, unsigned long c)
{
	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);
	return c;
}

unsigned long mapa::random(void)
{
	return mix(clock(), time(NULL), getpid());
}

void mapa::generar_aleatorio(unsigned porcentaje)
{
	setos_.clear(ID_GENERACION_MARCADO);

	unsigned max = (tamano_x_*tamano_y_*porcentaje)/100;
	unsigned cur = tamano_x_+tamano_x_+tamano_y_+tamano_y_-4; //Contamos los bordes, restamos 4 porque repetimos celdas al sumar
	QPoint punto_aleatorio;
	while(cur < max){
		punto_aleatorio.setX(rand()%(tamano_x_-1));
		punto_aleatorio.setY(rand()%(tamano_y_-1));
		setos_.at(punto_aleatorio) = ID_GENERACION_VACIO;
		cur++;
	}

	terminar_generar();
	corregir_posiciones();
}

void mapa::colocar_monstruos(unsigned cantidad_mon)
{
	//TODO
}

void mapa::corregir_posiciones(void)
{
	QPoint celda(0,0);
	for(unsigned i = 0; i < setos_.tam_y(); i++){
		for(unsigned j = 0; j < setos_.tam_x(); j++){
			celda.ry() = i;
			celda.rx() = j;
			switch (setos_.at(celda)) {
			case ID_GENERACION_MARCADO:
				setos_.at(celda) = ID_MAPA_NO_HAY_SETO;
				break;
			case ID_GENERACION_VACIO:
				setos_.at(celda) = ID_MAPA_SI_HAY_SETO;
				break;
			default:
				break;
			}
		}
	}
	/* Esto debería funcionar y no funciona
	for(unsigned i = 0; celda.y() < setos_.t_y(); celda.ry()++){
		for(unsigned j = 0; celda.x() < setos_.t_x(); celda.rx()++){
			//celda.ry() = i;
			//celda.rx() = j;
			std::cout << "Voy al punto: " << celda.x() << ", " << celda.y() << std::endl;
		}
	}*/
}

unsigned& mapa::get_x(void)
{
	return tamano_x_;
}

unsigned& mapa::get_y(void)
{
	return tamano_y_;
}

bool mapa::get_seto(QPoint celda)
{
	if(setos_.at(celda) == ID_MAPA_SI_HAY_SETO)
		return true;
	return false;
}

id_t mapa::get_entidad(QPoint celda)
{
	return entidades_.at(celda);
}

id_t mapa::get(QPoint celda)
{
	if(get_seto(celda) == ID_MAPA_SI_HAY_SETO)
		return ID_GLOBAL_SETO_HAY;
	//En otro caso
	return get_entidad(celda);
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
	switch (setos_.at(celda)) {
	case ID_MAPA_OTROS_COMPLETO: return imagenes_.otros_.completo_; break;
	default: break;
	}
	return imagenes_.otros_.completo_;
}
