/*!
 * \file mapa_t.cpp
 * \brief Contiene la definición de la clase "mapa"
 * \author Daniel Ramos Acosta <alu0100843095@ull.edu.es>
 * \date 9 de Octubre
 */

#include "mapa_t.h"

mapa_t::mapa_t(unsigned x, unsigned y):
	tam_x_(x),
	tam_y_(y),
	setos_(x,y, ID_MAPA_NO_HAY_SETO),
	entidades_(x,y, ID_MAPA_NO_HAY_SETO),
	harry_pos_(1,1),
	copa_pos_(x-2,y-2)
{
}

unsigned mapa_t::get_x(void)
{
	return tam_x_;
}

unsigned mapa_t::get_y(void)
{
	return tam_y_;
}

QPoint mapa_t::get_pos_harry(void)
{
	return harry_pos_;
}

QPoint mapa_t::get_pos_copa(void)
{
	return copa_pos_;
}

unsigned mapa_t::contar_setos(void)
{
	QPoint punto(0,0);
	unsigned cantidad = 0;
	for(unsigned i = 0; i < setos_.tam_x(); i++){
		for(unsigned j = 0; j < setos_.tam_y(); j++){
			punto.setX(i);
			punto.setY(j);
			if(entidades_.at(punto) == ID_GLOBAL_SETO_HAY)
				cantidad++;
		}
	}
	return cantidad;
}

unsigned mapa_t::contar_entidades(void)
{
	QPoint punto(0,0);
	unsigned cantidad = 0;
	for(unsigned i = 0; i < entidades_.tam_x(); i++){
		for(unsigned j = 0; j < entidades_.tam_y(); j++){
			punto.setX(i);
			punto.setY(j);
			if(entidades_.at(punto) != ID_GLOBAL_ENTIDAD_NULA)
				cantidad++;
		}
	}
	return cantidad;
}

unsigned mapa_t::contar_entidades(id_t entidad)
{
	QPoint punto(0,0);
	unsigned cantidad = 0;
	for(unsigned i = 0; i < entidades_.tam_x(); i++){
		for(unsigned j = 0; j < entidades_.tam_y(); j++){
			punto.setX(i);
			punto.setY(j);
			if(entidades_.at(punto) == entidad)
				cantidad++;
		}
	}
	return cantidad;
}

void mapa_t::resize(unsigned x,unsigned y)
{
	setos_.resize(x,y);
	entidades_.resize(x,y);
	setos_.clear();
	entidades_.clear();
	tam_x_ = x;
	tam_y_ = y;
}

void mapa_t::limpiar()
{
	setos_.clear();
	entidades_.clear();
}

void mapa_t::limpiar(QPoint celda)
{
	setos_.at(celda) = ID_GLOBAL_SETO_NO_HAY;
	entidades_.at(celda) = ID_GLOBAL_ENTIDAD_NULA;
}


void mapa_t::generar_laberinto(void)
{
	setos_.clear(ID_GENERACION_VACIO); //Limpiar el mapa_t
	explora_vecinos_y_excava(harry_pos_); //Generar el laberinto
	terminar_generar(); //Añadir bordes y espacios para harry y la copa
	corregir_posiciones(); //Cambiar de las ID de generación, a las ID del mapa_t globales
}

void mapa_t::explora_vecinos_y_excava(QPoint celda)
{
	//std::cout << "Dani bobo \n";
	setos_.at(celda) = ID_GENERACION_VISITADO;
	while(existe_casilla_ocupable(celda))
		explora_vecinos_y_excava(casilla_aleatoria_ocupable(celda));
	setos_.at(celda) = ID_GENERACION_MARCADO;
}

bool mapa_t::existe_casilla_ocupable(QPoint celda)
{
	for(unsigned i = 0; i < 4; i++){ //Para cada dirección
		if(setos_.alcanzable_bor(celda, i)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			QPoint revisar = common::QP(celda, i);
			id_t comp = setos_.at(revisar);
			if(comp == ID_GENERACION_VACIO)
				if(!tienes_adyacentes(revisar, i))
					return(true);
			//Si tiene adyacentes, mirar en otra dirección
		}
	}
	return false;
}

QPoint mapa_t::casilla_aleatoria_ocupable(QPoint celda)
{
	while(existe_casilla_ocupable(celda)){
		unsigned dir = common::random()%4;
		if(setos_.alcanzable_bor(celda, dir)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			QPoint revisar = common::QP(celda, dir);
			id_t comp = setos_.at(revisar);
			if(comp == ID_GENERACION_VACIO){
				if(!tienes_adyacentes(revisar, dir))
					return(revisar);
			}
		}
	}
	return QPoint(-1,-1);
}

bool mapa_t::tienes_adyacentes(QPoint celda, dir_t origen)
{
	unsigned desplazamiento = 0;
	switch (origen) {
	case ID_ORIENTACION_ARRIBA:
		desplazamiento = 4;
		break;
	case ID_ORIENTACION_DERECHA:
		desplazamiento = 6;
		break;
	case ID_ORIENTACION_IZQUIERDA:
		desplazamiento = 2;
		break;
	default:
		break;
	}

	for(unsigned i = 0; i < 5; i++){ //por cada dirección (incluyendo las esquinas)
		QPoint mirando = common::QP(celda, convertir_reloj(i+desplazamiento));
		if(setos_.alcanzable_bor(mirando)){ //Sólo si es alcanzable (que queda dentro de los márgenes de la matriz)
			if(setos_.at(mirando) == ID_GENERACION_VISITADO || setos_.at(mirando) == ID_GENERACION_MARCADO)
				return true; //Si pasamos de 1 adyacentes (por el que vinimos), tiene adyacentes
		}
	}
	return false;
}

dir_t mapa_t::convertir_reloj(dir_t i)
{
	i = i % 8;
	dir_t final;
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
	//Poner espacios a harry
	setos_.at(harry_pos_) = ID_GENERACION_MARCADO;
	for(unsigned i = 0; i < 8; i++){
		if(setos_.alcanzable(harry_pos_, i))
			setos_.at(harry_pos_, i) = ID_GENERACION_MARCADO;
	}

	//Poner espacios a la copa
	setos_.at(copa_pos_) = ID_GENERACION_MARCADO;
	for(unsigned i = 0; i < 8; i++){
		if(setos_.alcanzable(copa_pos_, i))
			setos_.at(copa_pos_, i) = ID_GENERACION_MARCADO;
	}
	setos_.at(copa_pos_) = ID_GENERACION_MARCADO;

	//Poner bordes
	for(unsigned i = 0; i < tam_y_; i++){
		for(unsigned j = 0; j < tam_x_; j++){
			if(i == 0 || j ==0 || i == tam_y_-1 || j == tam_x_-1){
				QPoint aux(j, i);
				setos_.at(aux) = ID_GENERACION_VACIO;
			}
		}
	}
}

void mapa_t::generar_aleatorio(unsigned porcentaje)
{
	setos_.clear(ID_GENERACION_MARCADO);


	unsigned max = ((tam_x_-1)*(tam_y_-1)*porcentaje)/100;
	unsigned cur = 0;
	unsigned iter = 0;
	QPoint punto_aleatorio;
	while(cur < max){
		punto_aleatorio.setX(common::random()%(tam_x_-1));
		punto_aleatorio.setY(common::random()%(tam_y_-1));
		if(setos_.alcanzable_bor(punto_aleatorio)){
			if(punto_aleatorio != harry_pos_ && punto_aleatorio != copa_pos_)
			setos_.at(punto_aleatorio) = ID_GENERACION_VACIO;
			cur++;
		}
		iter++;
		if(iter == 65535) //Sería un error
			throw exception::out_of_range("Bad densirty in aleatory method");
	}

	terminar_generar();
	corregir_posiciones();
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

void mapa_t::colocar_monstruos(unsigned cantidad)
{
	if(cantidad > (tam_x_*tam_y_)-contar_setos())
		throw exception::out_of_range("Excedido el numero de monstruos posibles");

	unsigned contador = 0;
	QPoint punto(0,0);
	while(contador < cantidad)
	{
		punto.setX(common::random()%entidades_.tam_x());
		punto.setY(common::random()%entidades_.tam_y());
		if(setos_.at(punto) == ID_GLOBAL_SETO_NO_HAY && entidades_.at(punto) == ID_GLOBAL_ENTIDAD_NULA){
			entidades_.at(punto) = ID_GLOBAL_ENTIDAD_MONSTRUO;
			contador++;
		}
	}
}

void mapa_t::mover_copa(QPoint celda)
{
	if(!entidades_.alcanzable(celda))
		throw exception::not_reachable(common::imprqp(celda).c_str());
	if(setos_.at(celda) == ID_GLOBAL_SETO_HAY || entidades_.at(celda) != ID_GLOBAL_ENTIDAD_NULA)
		throw exception::overlapping(common::imprqp(celda).c_str());

	//En otro caso...
	entidades_.at(copa_pos_) = ID_GLOBAL_ENTIDAD_NULA;
	copa_pos_ = celda;
	entidades_.at(copa_pos_) = ID_GLOBAL_ENTIDAD_COPA_MAGOS;
}

void mapa_t::mover_harry(QPoint celda)
{
	if(!entidades_.alcanzable(celda))
		throw exception::not_reachable(common::imprqp(celda).c_str());
	if(setos_.at(celda) == ID_GLOBAL_SETO_HAY || entidades_.at(celda) != ID_GLOBAL_ENTIDAD_NULA)
		throw exception::overlapping(common::imprqp(celda).c_str());

	//En otro caso...
	entidades_.at(harry_pos_) = ID_GLOBAL_ENTIDAD_NULA;
	harry_pos_ = celda;
	entidades_.at(harry_pos_) = ID_GLOBAL_ENTIDAD_HARRY_POTTER;
}

void mapa_t::mover_harry(dir_t sentido)
{
	QPoint celda = common::QP(harry_pos_, sentido);
	return mover_harry(celda);
}

id_t& mapa_t::get_seto(QPoint celda)
{
	if(!setos_.alcanzable(celda))
		throw exception::not_reachable(common::imprqp(celda).c_str());
	return setos_.at(celda);
}

id_t& mapa_t::get_seto(QPoint celda, dir_t dir)
{
	return setos_.at(common::QP(celda, dir));
}

id_t& mapa_t::get_ent(QPoint celda)
{
	if(!entidades_.alcanzable(celda))
		throw exception::not_reachable(common::imprqp(celda).c_str());
	return entidades_.at(celda);
}

id_t& mapa_t::get_ent(QPoint celda, dir_t dir)
{
	return entidades_.at(common::QP(celda, dir));
}
