#include "harryPotter.h"

harryPotter::harryPotter(mapa_t& lab):
	posicion_harry(1,1),
	vidas(3),
	mana(3),
	laberinto(lab)
{

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
}

void harryPotter::set_mana (unsigned mana_encontrado){
	mana = mana_encontrado;
}

void harryPotter::set_vidas (unsigned vida_gastada){
	vidas = vida_gastada;
}

void harryPotter::movimiento(){
	//while (get_vidas()>0&&get_vidas()<=3){
	//set_posicion_harry (clase_airam.movimiento_harry());
//}
//	VentanaPrincipal harry;
//	if (get_vidas()>0&&get_vidas()<=3){
//		harry.set_texto_estado("¡¡¡¡Harry ha encontrado la copa!!!!");
//	}
}
