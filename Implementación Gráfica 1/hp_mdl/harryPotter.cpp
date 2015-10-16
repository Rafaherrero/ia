#include "harryPotter.h"

harryPotter::harryPotter(mapa_t& lab):
	posicion_harry(1,1),
	vidas(3),
	mana(3),
    laberinto(lab),
    marcar(lab.get_x(), lab.get_y(), ID_GENERACION_VACIO)
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


    while (get_vidas()>0&&get_vidas()<=3&&get_posicion_harry()!=laberinto.get_pos_copa()){
        QPoint punto(get_posicion_harry());
        marcar.at(punto)=ID_GENERACION_VISITADO;

        if(laberinto.get_seto(get_posicion_harry(), ID_ORIENTACION_ARRIBA) == ID_GLOBAL_SETO_HAY){

        }
    }


//while (get_vidas()>0&&get_vidas()<=3){
//set_posicion_harry (clase_airam.movimiento_harry());
//}
//	VentanaPrincipal harry;
//	if (get_vidas()>0&&get_vidas()<=3){
//		harry.set_texto_estado("¡¡¡¡Harry ha encontrado la copa!!!!");
//	}
}
