#include "harry_potter.h"

harry_potter::harry_potter():
	posicion_harry(1,1),
	mana(3),
	vidas(3)
{

}

QPoint harry_potter::get_posicion_harry(){
	return posicion_harry;
}

unsigned harry_potter::get_mana(){
	return mana;
}

unsigned harry_potter::get_vidas(){
	return vidas;
}

void harry_potter::set_posicion_harry (QPoint ranas_de_chocolate){
	posicion_harry = ranas_de_chocolate;
}

void harry_potter::set_mana (unsigned mana_encontrado){
	mana = mana_encontrado;
}

void harry_potter::set_vidas (unsigned vida_gastada){
	vidas = vida_gastada;
}

void harry_potter::movimiento(){
	//while (get_vidas()>0&&get_vidas()<=3){
	//set_posicion_harry (clase_airam.movimiento_harry());
//}
	VentanaPrincipal harry;
	if (get_vidas()>0&&get_vidas()<=3){
		harry.set_texto_estado("¡¡¡¡Harry ha encontrado la copa!!!!");
	}
}
