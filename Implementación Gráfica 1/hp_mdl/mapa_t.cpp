/*!
 * \file mapa_t.cpp
 * \brief Contiene la definición de la clase "mapa"
 * \author Daniel Ramos Acosta <alu0100843095@ull.edu.es>
 * \date 9 de Octubre
 */

#include "mapa_t.h"

mapa_t::mapa_t(void):
	tamano_x_(0),
	tamano_y_(0),
	inicio_(1,1),
	final_(1,1)
{
}

mapa_t::mapa_t(unsigned x, unsigned y):
	tamano_x_(x),
	tamano_y_(y),
	setos_(x,y, ID_MAPA_NO_HAY_SETO),
	entidades_(x,y, ID_MAPA_NO_HAY_SETO),
	inicio_(1,1),
	final_(1,1)
{
}

bool mapa_t::existe_imagen(QString ruta)
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

void mapa_t::importar_imagenes(void)
{
	//TODO
}

void mapa_t::generar_laberinto(void)
{
	setos_.clear(ID_GENERACION_VACIO); //Limpiar el mapa_t
	explora_vecinos_y_excava(inicio_); //Generar el laberinto
	terminar_generar(); //Añadir bordes y espacios para harry y la copa
	corregir_posiciones(); //Cambiar de las ID de generación, a las ID del mapa_t globales
}

void mapa_t::explora_vecinos_y_excava(QPoint celda)
{
	setos_.at(celda) = ID_GENERACION_VISITADO;
	while(existe_casilla_ocupable(celda))
		explora_vecinos_y_excava(casilla_ocupable(celda));
	setos_.at(celda) = ID_GENERACION_MARCADO;
	return;
}

bool mapa_t::existe_casilla_ocupable(QPoint celda)
{
	QPoint error(-1, -1);
	if(casilla_ocupable(celda) == error)
		return false;
	return true;
}

QPoint mapa_t::casilla_ocupable(QPoint celda)
{
	unsigned desplazamiento = random();
	for(unsigned i = 0; i < 4; i++){ //Para cada dirección
		unsigned i_e = (i+desplazamiento)%4; //Obtener un número aleatorio y a partir de ahí, rotar
		if(setos_.alcanzable(celda, i_e)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			QPoint revisar = setos_.dir(celda, i_e);
			id_t comp = setos_.at(revisar);
			if(comp == ID_GENERACION_VACIO && (comp != ID_GENERACION_VISITADO) && (comp != ID_GENERACION_MARCADO))
				if(!tienes_adyacentes(revisar, i_e))
					return(revisar);
			//Si tiene adyacentes, mirar en otra dirección
		}
	}
	QPoint dummy(-1,-1); //Si no tiene adyacentes, devolver un nulo (-1,-1)
	return dummy;
}

bool mapa_t::tienes_adyacentes(QPoint celda, dir_t origen) //FIXME
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

id_t mapa_t::convertir_reloj(dir_t i)
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

void mapa_t::terminar_generar(void)
{
	//TODO: Añadir espacios para harry y la copa.
	for(unsigned i = 0; i < tamano_y_; i++){
		for(unsigned j = 0; j < tamano_x_; j++){
			if(i == 0 || j ==0 || i == tamano_y_-1 || j == tamano_x_-1){
				QPoint aux(j, i);
				setos_.at(aux) = ID_GENERACION_VACIO;
			}
		}
	}
}

void mapa_t::generar_aleatorio(unsigned porcentaje)
{
	setos_.clear(ID_GENERACION_MARCADO);

	unsigned max = (tamano_x_*tamano_y_*porcentaje)/100;
	unsigned cur = tamano_x_+tamano_x_+tamano_y_+tamano_y_-4; //Contamos los bordes, restamos 4 porque repetimos celdas al sumar
	QPoint punto_aleatorio;
	while(cur < max){
		punto_aleatorio.setX(aleatorio::random()%(tamano_x_-1));
		punto_aleatorio.setY(aleatorio::random()%(tamano_y_-1));
		setos_.at(punto_aleatorio) = ID_GENERACION_VACIO;
		cur++;
	}

	terminar_generar();
	corregir_posiciones();
}

void mapa_t::colocar_monstruos(unsigned cantidad)
{
	//TODO
}

void mapa_t::corregir_posiciones(void)
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
}

unsigned mapa_t::get_x(void)
{
	return tamano_x_;
}

unsigned mapa_t::get_y(void)
{
	return tamano_y_;
}

id_t& mapa_t::get_seto(QPoint celda)
{
	//TODO: tirar excepción si no es alcanzable
	return setos_.at(celda);
}

id_t& mapa_t::get_ent(QPoint celda)
{
	//TODO: tirar excepción si no es alcanzable
	return entidades_.at(celda);
}
