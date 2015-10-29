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
	marcar.at(stack.top())=ID_GENERACION_VISITADO;
	laberinto.mover_harry(nueva_posicion);
}

void harryPotter::set_mana (unsigned mana_encontrado){
	mana = mana_encontrado;
}

void harryPotter::set_vidas (unsigned vida_gastada){
	vidas = vida_gastada;
}

bool harryPotter::puedo_continuar(){
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

QPoint harryPotter::movimiento(){

	QPoint aux = get_next_dir();
	if(aux != get_posicion_harry()){
		set_posicion_harry(aux);
		stack.push(get_posicion_harry());
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
