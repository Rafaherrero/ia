#include "harryPotter.h"

harryPotter::harryPotter(mapa_t& lab):
	posicion_harry(1,1),
	vidas(3),
	mana(3),
	laberinto(lab),
	marcar(lab.get_x(), lab.get_y(), ID_GENERACION_VACIO),
	encontrada_copa(false)
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
	primera_vez = true;
	encontrada_copa = false;
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

	QPoint p_final;
	unsigned v_ahora = 32000;
	for(unsigned i = 0; i < lista.size(); i++){
		unsigned valor_bandera = marcar.at(lista[i]);
		if(valor_bandera < v_ahora){
			p_final = lista[i];
			v_ahora = valor_bandera;
		}
	}
	return p_final;
}

bool harryPotter::puedo_continuar_escalada(){
	return !encontrada_copa; //TODO: Implementar condición de parada del algirtmo de escalada
}

QPoint harryPotter::movimiento_escalada()
{
	if(primera_vez){
		for(unsigned i = 0; i < marcar.tam_x(); i++){
			for(unsigned j = 0; j < marcar.tam_y(); j++){
				marcar.at(common::QP(i,j)) = funcion_heuristica_prox(common::QP(i,j)); //Colocar todas las banderas a h*(x)
			}
		}
        primera_vez = false;
	}
	aux = get_next_dir_escalada();
    marcar.at(posicion_harry)+=10; // Se suma la bandera+1
	set_posicion_harry(aux);

	if(laberinto.get_pos_copa() == posicion_harry)
		encontrada_copa = true;

	return posicion_harry;
}

unsigned harryPotter::funcion_heuristica_prox(QPoint p1)
{
	QPoint p2 = laberinto.get_pos_copa();
    double resultado = sqrt((p2.x() - p1.x())*(p2.x() - p1.x()) + (p2.y() - p1.y())*(p2.y() - p1.y())); //Distancia euclides
    /*unsigned mx = abs(p1.x()-p2.x()); Distancia manhattan
    unsigned my = abs(p1.y()-p2.y());
    return mx+my;*/
    return unsigned(resultado);
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

bool harryPotter::puedo_continuar_estrella(){
	return puedo_continuar_DFS(); //TODO: Implementar condición de parada del algirtmo A*
}

QPoint harryPotter::movimiento_estrella(){
	std::cout << "Soy el movimiento en estrella!" << std::endl; //TODO: Quitar esto cuando ya no haga falta
	return movimiento_DFS(); //TODO: Implementar algoritmo A*.
}
