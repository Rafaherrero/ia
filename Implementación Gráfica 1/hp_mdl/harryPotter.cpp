#include "harryPotter.h"

harryPotter::harryPotter(mapa_t& lab):
	posicion_harry(1,1),
	vidas(3),
	mana(3),
	laberinto(lab),
	marcar(lab.get_x(), lab.get_y(), ID_GENERACION_VACIO)
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

void harryPotter::set_posicion_harry (QPoint ranas_de_chocolate){
	posicion_harry = ranas_de_chocolate;
	laberinto.mover_harry(ranas_de_chocolate);
}

void harryPotter::set_posicion_harry_nuevo (QPoint nueva_posicion){
	posicion_harry = nueva_posicion;
	stack.clear();
	stack.push(get_posicion_harry());
	marcar.resize(laberinto.get_x(),laberinto.get_y());
	marcar.clear();
	laberinto.mover_harry(nueva_posicion);
	marcar.at(stack.top())=ID_GENERACION_VISITADO;

}

void harryPotter::set_mana (unsigned mana_encontrado){
	mana = mana_encontrado;
}

void harryPotter::set_vidas (unsigned vida_gastada){
	vidas = vida_gastada;
}

bool harryPotter::puedo_continuar_DFS(){
	if (get_posicion_harry()==laberinto.get_pos_copa()||stack.empty())
		return false;
	else
		return true;
}

QPoint harryPotter::get_next_dir(){
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

QPoint harryPotter::get_next_dir_escalada()
{
	QPoint p_arriba = common::QP(get_posicion_harry(), ID_ORIENTACION_ARRIBA);
	QPoint p_abajo = common::QP(get_posicion_harry(), ID_ORIENTACION_ABAJO);
	QPoint p_derecha = common::QP(get_posicion_harry(), ID_ORIENTACION_DERECHA);
	QPoint p_izquierda = common::QP(get_posicion_harry(), ID_ORIENTACION_IZQUIERDA);

	unsigned h_arriba = funcion_heuristica_prox(p_arriba);
	unsigned h_abajo = funcion_heuristica_prox(p_abajo);
	unsigned h_derecha = funcion_heuristica_prox(p_derecha);
	unsigned h_izquierda = funcion_heuristica_prox(p_izquierda);

	std::pair<QPoint,unsigned> arriba(p_arriba, h_arriba);
	std::pair<QPoint,unsigned> abajo(p_abajo, h_abajo);
	std::pair<QPoint,unsigned> derecha(p_derecha, h_derecha);
	std::pair<QPoint,unsigned> izquierda(p_izquierda, h_izquierda);

	std::vector<std::pair<QPoint,unsigned>> lista;

	if(laberinto.get_seto(p_arriba) == ID_GLOBAL_SETO_NO_HAY && marcar.at(p_arriba) == ID_GENERACION_VACIO){
		lista.push_back(arriba);
	}
	if(laberinto.get_seto(p_abajo) == ID_GLOBAL_SETO_NO_HAY && marcar.at(p_abajo) == ID_GENERACION_VACIO){
		lista.push_back(abajo);
	}
	if (laberinto.get_seto(p_derecha) == ID_GLOBAL_SETO_NO_HAY && marcar.at(p_derecha) == ID_GENERACION_VACIO){
		lista.push_back(derecha);
	}
	if (laberinto.get_seto(p_izquierda) == ID_GLOBAL_SETO_NO_HAY && marcar.at(p_izquierda) == ID_GENERACION_VACIO){
		lista.push_back(izquierda);
	}

	QPoint punto_final = get_posicion_harry();
	unsigned h_ahora = 32000;
	for(int i = 0; i < lista.size(); i++){
		if(h_ahora > lista[i].second){
			h_ahora = lista[i].second;
			punto_final = lista[i].first;
		}
	}
	return punto_final;
}

QPoint harryPotter::movimiento_DFS(){

	aux = get_next_dir();
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

bool harryPotter::puedo_continuar_escalada(){
	return puedo_continuar_DFS(); //TODO: Implementar condición de parada del algirtmo de escalada
}

QPoint harryPotter::movimiento_escalada()
{
	//std::cout << "Soy el movimiento en escalada!" << std::endl; //TODO: Quitar esto cuando ya no haga falta
	std::cout << "La distancia entre harry y la copa es " << funcion_heuristica_prox(posicion_harry) << std::endl;
	aux = get_next_dir_escalada();
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

unsigned harryPotter::funcion_heuristica_prox(QPoint p1)
{
	QPoint p2 = laberinto.get_pos_copa();
	double resultado = sqrt((p2.x() - p1.x())*(p2.x() - p1.x()) + (p2.y() - p1.y())*(p2.y() - p1.y()));
	return (unsigned)resultado;
}

bool harryPotter::puedo_continuar_estrella(){
	return puedo_continuar_DFS(); //TODO: Implementar condición de parada del algirtmo A*
}

QPoint harryPotter::movimiento_estrella(){
	std::cout << "Soy el movimiento en estrella!" << std::endl; //TODO: Quitar esto cuando ya no haga falta
	return movimiento_DFS(); //TODO: Implementar algoritmo A*.
}
