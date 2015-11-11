#include "harryPotter.h"

harryPotter::harryPotter(mapa_t& lab):
	posicion_harry(1,1),
	vidas(3),
	mana(3),
	laberinto(lab),
	marcar(lab.get_x(), lab.get_y(), ID_GENERACION_VACIO),
	encontrada_copa(false),
	costo_transicion_(5),
	tipo_distancia_(false), //Manhattan
	muerto(false)
{
	stack.push(get_posicion_harry());
	marcar.at(stack.top())=ID_GENERACION_VISITADO;
}

QPoint harryPotter::get_posicion_harry(){
	return posicion_harry;
}

unsigned harryPotter::get_mana(){
	return mana;
}

unsigned harryPotter::get_vidas(){
	return vidas;
}

void harryPotter::set_posicion_harry (QPoint pos){
	posicion_harry = pos;
	laberinto.mover_harry(pos);
}

void harryPotter::set_posicion_harry_nuevo (QPoint nueva_posicion){
	posicion_harry = nueva_posicion;
	stack.clear();
	stack.push(get_posicion_harry());
	marcar.resize(laberinto.get_x(),laberinto.get_y());
	marcar.clear();
	laberinto.mover_harry(nueva_posicion);
	marcar.at(stack.top())=ID_GENERACION_VISITADO;
	primera_vez = true;
	encontrada_copa = false;
	muerto = false;
}

void harryPotter::set_mana (unsigned mana_encontrado){
	mana = mana_encontrado;
}

void harryPotter::set_vidas (unsigned vida_gastada){
	vidas = vida_gastada;
}

//********************** FUNCIONES PARA EL ALGORITMO DFS ***************************

bool harryPotter::puedo_continuar_DFS(){
	if (get_posicion_harry()==laberinto.get_pos_copa()||stack.empty())
		return false;
	else
		return true;
}

QPoint harryPotter::movimiento_DFS(){

	aux = get_next_dir_DFS();
	if(aux != get_posicion_harry()){
		set_posicion_harry(aux);
		stack.push(get_posicion_harry());
		if (!stack.empty())
			marcar.at(stack.top())=ID_GENERACION_VISITADO;
	}
	else{
		marcar.at(get_posicion_harry())=ID_GENERACION_MARCADO;
		stack.pop();
		if (!stack.empty())
			set_posicion_harry(stack.top());
	}
	return get_posicion_harry();
}

QPoint harryPotter::get_next_dir_DFS(){
	for (int i = 0; i < 4; i++){
		if (i==ID_ORIENTACION_DERECHA && laberinto.get_seto(get_posicion_harry(), i) == ID_GLOBAL_SETO_NO_HAY && marcar.at(get_posicion_harry(), i) == ID_GENERACION_VACIO){
			return get_posicion_harry()+MOVER_DERECHA;
		}
		else if(i==ID_ORIENTACION_ABAJO && laberinto.get_seto(get_posicion_harry(), i) == ID_GLOBAL_SETO_NO_HAY && marcar.at(get_posicion_harry(), i) == ID_GENERACION_VACIO){
			return get_posicion_harry()+MOVER_ABAJO;
		}
		else if(i==ID_ORIENTACION_IZQUIERDA && laberinto.get_seto(get_posicion_harry(), i) == ID_GLOBAL_SETO_NO_HAY && marcar.at(get_posicion_harry(), i) == ID_GENERACION_VACIO){
			return get_posicion_harry()+MOVER_IZQUIERDA;
		}
		else if(i==ID_ORIENTACION_ARRIBA && laberinto.get_seto(get_posicion_harry(), i) == ID_GLOBAL_SETO_NO_HAY && marcar.at(get_posicion_harry(), i) == ID_GENERACION_VACIO){
			return get_posicion_harry()+MOVER_ARRIBA;
		}
	}
	return get_posicion_harry();
}

//********************** FUNCIONES PARA EL ALGORITMO LRTA* ***************************

bool harryPotter::puedo_continuar_LRTA(){
	return !encontrada_copa && !muerto;
}

QPoint harryPotter::movimiento_LRTA()
{
	if(primera_vez){ //Inicializacion
		for(unsigned i = 0; i < marcar.tam_x(); i++){
			for(unsigned j = 0; j < marcar.tam_y(); j++){
				marcar.at(common::QP(i,j)) = funcion_heuristica_prox(common::QP(i,j)); //Colocar todas las banderas a h*(x)
			}
		}
		primera_vez = false;
	}
	aux = get_fx(MIN); // Obtener el x' con h*(x) mínimo
	marcar.at(posicion_harry) = costo_transicion_ + marcar.at(aux); // Al x se le suma f(x') y el coste de transicion
	set_posicion_harry(aux); //Nos desplazamos a x'

	if(laberinto.get_pos_copa() == posicion_harry) //Si hemos encontrado la copa, salimos
		encontrada_copa = true;

	if((marcar.at(posicion_harry)-funcion_heuristica_prox(posicion_harry)) > costo_transicion_*25) //Si pasamos demasiadas veces por un mismo lugar, morimos
		muerto = true;

	return posicion_harry;
}

//********************** FUNCIONES PARA EL ALGORITMO RTA ***************************

bool harryPotter::puedo_continuar_RTA(){
	return !encontrada_copa && !muerto;
}


QPoint harryPotter::movimiento_RTA()
{
	if(primera_vez){ //Inicializacion
		for(unsigned i = 0; i < marcar.tam_x(); i++){
			for(unsigned j = 0; j < marcar.tam_y(); j++){
				marcar.at(common::QP(i,j)) = funcion_heuristica_prox(common::QP(i,j)); //Colocar todas las banderas a h*(x)
			}
		}
		primera_vez = false;
	}
	marcar.at(posicion_harry) = costo_transicion_ + marcar.at(get_fx(SECONDMIN)); // Al x se le suma f(x') del segundo mínimo y el coste de transicion
	set_posicion_harry(get_fx(MIN)); //Nos desplazamos a x' con f(x') mínimo

	if(laberinto.get_pos_copa() == posicion_harry) //Si hemos encontrado la copa, salimos
		encontrada_copa = true;

	if((marcar.at(posicion_harry)-funcion_heuristica_prox(posicion_harry)) > costo_transicion_*25) //Si pasamos demasiadas veces por un mismo lugar, morimos
		muerto = true;

	return posicion_harry;
}

//********************** FUNCIONES PARA EL ALGORITMO A ESTRELLA ***************************

bool harryPotter::puedo_continuar_estrella()
{
	return puedo_continuar_DFS();
}

QStack<QPoint> harryPotter::movimiento_estrella()
{
	trayectoria* a_estrella;
	a_estrella = new trayectoria(laberinto, get_posicion_harry());
	return a_estrella->obtener_camino_minimo().camino;

}

//********************** MÉTODOS COMUNES PARA ALGORITMOS HEURÍSTICOS *********************

unsigned harryPotter::funcion_heuristica_prox(QPoint p1)
{
	QPoint p2 = laberinto.get_pos_copa();
	if(tipo_distancia_){
		double resultado = sqrt((p2.x() - p1.x())*(p2.x() - p1.x()) + (p2.y() - p1.y())*(p2.y() - p1.y())); //Distancia euclides
		return unsigned(resultado);
	}
	unsigned mx = abs(p1.x()-p2.x()); //Distancia manhattan
	unsigned my = abs(p1.y()-p2.y());
	return mx+my;
}

QPoint harryPotter::get_fx(unsigned min)
{
	QPoint p_arriba = common::QP(get_posicion_harry(), ID_ORIENTACION_ARRIBA);
	QPoint p_abajo = common::QP(get_posicion_harry(), ID_ORIENTACION_ABAJO);
	QPoint p_derecha = common::QP(get_posicion_harry(), ID_ORIENTACION_DERECHA);
	QPoint p_izquierda = common::QP(get_posicion_harry(), ID_ORIENTACION_IZQUIERDA);

	std::vector<QPoint> lista;

	if(laberinto.get_seto(p_arriba) == ID_GLOBAL_SETO_NO_HAY){
		lista.push_back(p_arriba);
	}
	if(laberinto.get_seto(p_abajo) == ID_GLOBAL_SETO_NO_HAY){
		lista.push_back(p_abajo);
	}
	if (laberinto.get_seto(p_derecha) == ID_GLOBAL_SETO_NO_HAY){
		lista.push_back(p_derecha);
	}
	if (laberinto.get_seto(p_izquierda) == ID_GLOBAL_SETO_NO_HAY){
		lista.push_back(p_izquierda);
	}

	if(lista.size() == 0){//Si no tenemos donde movernos, nos quedamos en el sitio y nos morimos
		muerto=true;
		return posicion_harry;
	}

	bubble(lista); //ordenar la lista de menor a mayor usando el algoritmo de la burbuja (por usar uno)
	if(min > 0 && lista.size() > 1) //Devolver el primer o segundo mínimo
		return lista[1];
	return lista[0];
}

void harryPotter::bubble(std::vector<QPoint> &vec)
{
	bool change = true;
	for(std::size_t i = 1; (i < vec.size()) && (change); i++){
		change = false;
		for(std::size_t j = vec.size()-1; j >= i; j--)
			if( marcar.at(vec[j]) < marcar.at(vec[j-1])){
				std::swap(vec[j-1], vec[j]);
				change = true;
			}
	}
}

unsigned& harryPotter::costo_transicion(void)
{
	return costo_transicion_;
}


bool& harryPotter::tipo_distancia(void)
{
	return tipo_distancia_;
}
