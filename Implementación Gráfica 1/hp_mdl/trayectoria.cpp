#include "trayectoria.h"

trayectoria::trayectoria(mapa_t& lab, QPoint pos_harry):
	laberinto(lab)
{
	path room;
	room.camino.push(pos_harry);
	int aux;
	aux=(std::abs(pos_harry.x()-laberinto.get_pos_copa().x())+std::abs(pos_harry.y()-laberinto.get_pos_copa().y()));
	room.H=aux;
	room.coste=room.H;
	abierta.append(room);
}

trayectoria::~trayectoria()
{

}

/* 2B2
*/
void trayectoria::diversificar()
{
	for (int i = 0; i < 4; i++){
		if (i==ID_ORIENTACION_DERECHA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			path room;
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_DERECHA);
			int aux;
			aux=(std::abs(room.camino.top().x()-laberinto.get_pos_copa().x())+std::abs(room.camino.top().y()-laberinto.get_pos_copa().y()));
			room.H=aux;
			room.coste=room.H+10;

			abierta.append(room);
		}
		else if (i==ID_ORIENTACION_ABAJO && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			path room;
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_ABAJO);
			int aux;
			aux=(std::abs(room.camino.top().x()-laberinto.get_pos_copa().x())+std::abs(room.camino.top().y()-laberinto.get_pos_copa().y()));
			room.H=aux;
			room.coste=room.H+10;

			abierta.append(room);
		}
		else if (i==ID_ORIENTACION_IZQUIERDA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			path room;
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_IZQUIERDA);
			int aux;
			aux=(std::abs(room.camino.top().x()-laberinto.get_pos_copa().x())+std::abs(room.camino.top().y()-laberinto.get_pos_copa().y()));
			room.H=aux;
			room.coste=room.H+10;

			abierta.append(room);
		}
		else if (i==ID_ORIENTACION_ARRIBA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			path room;
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_ARRIBA);
			int aux;
			aux=(std::abs(room.camino.top().x()-laberinto.get_pos_copa().x())+std::abs(room.camino.top().y()-laberinto.get_pos_copa().y()));
			room.H=aux;
			room.coste=room.H+10;

			abierta.append(room);
		}
	}
}

/* 2B4 Ordenar lista abierta donde el primer
 * valor es el valor minimo
*/
void trayectoria::ordenar()
{
	for(int i=0; i < abierta.size(); i++){
		for(int j=i+1; j < abierta.size(); j++){
			if (abierta[i].coste > abierta[j].coste)
				abierta.swap(i, j);
		}
	}
}

/* 2B5
*/
void trayectoria::comprobar()
{
	for(int i=0; i < abierta.size(); i++){
		for(int j=i+1; j < abierta.size(); j++){
			if (abierta[i].camino.top()==abierta[j].camino.top()){
				if (abierta[i].coste < abierta[j].coste){
					for (int m=0; m < cerrada.size();m++){
						if (abierta[j].camino.top()==cerrada[m].camino.top()){
							if (abierta[j].coste < cerrada[m].coste)
								cerrada.append(abierta[j]);
						}
					}
					abierta.removeAt(j);
					for (int k=0; k < cerrada.size();k++){
						if (abierta[i].camino.top()==cerrada[k].camino.top()){
							if (abierta[i].coste > cerrada[k].coste){
								for (int n=0; n < cerrada.size();n++){
									if (abierta[j].camino.top()==cerrada[n].camino.top()){
										if (abierta[j].coste < cerrada[n].coste)
											cerrada.append(abierta[i]);
									}
								}
								abierta.removeAt(i);
							}
						}
					}
				}
				else{
					for (int o=0; o < cerrada.size();o++){
						if (abierta[i].camino.top()==cerrada[o].camino.top()){
							if (abierta[i].coste < cerrada[o].coste)
								cerrada.append(abierta[i]);
						}
					}
					abierta.removeAt(i);
					for (int l=0; l < cerrada.size();l++){
						if (abierta[j].camino.top()==cerrada[l].camino.top()){
							if (abierta[j].coste > cerrada[l].coste){
								for (int p=0; p < cerrada.size();p++){
									if (abierta[j].camino.top()==cerrada[p].camino.top()){
										if (abierta[j].coste < cerrada[p].coste)
											cerrada.append(abierta[j]);
									}
								}
								abierta.removeAt(j);
							}
						}
					}
				}
			}
		}
	}
}

path trayectoria::obtener_camino_minimo()
{
	bool copa_encontrada=false;

	while (!abierta.empty()||!copa_encontrada){
		if(abierta.first().camino.top()==laberinto.get_pos_copa()){
			copa_encontrada=true;
		}
		else{
			cerrada.append(abierta.first());
			abierta.removeFirst();

			for (int i=0; i < cerrada.size(); i++){
				if (cerrada.last().camino.top()==cerrada[i].camino.top()){
					if(cerrada.last().coste < cerrada[i].coste)
						cerrada.removeAt(i);
				}
			}
			diversificar();
			ordenar();
			comprobar();
		}
	}
	if (copa_encontrada==true){
		return abierta.first();
	}
	else{
		std::cout << "No tiene solución." << std::endl;
		QList <path> no_solucion;
		return no_solucion.first();
	}
}

