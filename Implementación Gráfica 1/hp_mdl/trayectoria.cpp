#include "trayectoria.h"

trayectoria::trayectoria(mapa_t& lab, QPoint pos_harry):
	laberinto(lab)
{
	path room;
	room.camino.push(pos_harry);
	room.H=manhattan(pos_harry);
	abierta.append(room);
}

trayectoria::~trayectoria()
{

}

/* 2B2
*/

int trayectoria::manhattan(QPoint origen){
	return (std::abs(origen.x()-laberinto.get_pos_copa().x())+std::abs(origen.y()-laberinto.get_pos_copa().y()));
}

void trayectoria::diversificar()
{
	path room;
	for (int i = 0; i < 4; i++){
		room.H=-1;
		if (i==ID_ORIENTACION_DERECHA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_DERECHA);
			room.H=manhattan(room.camino.top());
		}
		else if (i==ID_ORIENTACION_ABAJO && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_ABAJO);
			room.H=manhattan(room.camino.top());
		}
		else if (i==ID_ORIENTACION_IZQUIERDA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_IZQUIERDA);
			room.H=manhattan(room.camino.top());
		}
		else if (i==ID_ORIENTACION_ARRIBA && laberinto.get_seto(cerrada.last().camino.top(), i) == ID_GLOBAL_SETO_NO_HAY){
			room.camino=cerrada.last().camino;
			room.camino.push(cerrada.last().camino.top()+MOVER_ARRIBA);
			room.H=manhattan(room.camino.top());
		}
		if (room.H != -1)
			abierta.append(room);
	}
}

/* 2B4 Ordenar lista abierta donde el primer
 * valor es el valor minimo
*/
void trayectoria::ordenar()
{
	for(int i=0; i < abierta.size(); i++){
		for(int j=i+1; j < abierta.size(); j++){
			if (abierta[i].H > abierta[j].H)
				abierta.swap(i, j);
		}
	}
}

/* 2B5
*/
void trayectoria::comprobar()
{
	QList <int> eliminar;
	for(int i=0; i < abierta.size(); i++){
		for(int j=0; j < cerrada.size(); j++){
			if (abierta[i].camino.top()==cerrada[j].camino.top() && abierta[i].H >= cerrada[j].H){
				eliminar.append(i);
			}
		}
	}
	for (int i=0; i < eliminar.size(); i++){
		abierta.removeAt(eliminar.at(i));
	}
	eliminar.clear();
	for(int i=0; i < abierta.size(); i++){
		for(int j=i+1; j < abierta.size(); j++){
			if (abierta[i].camino.top()==abierta[j].camino.top()){
				eliminar.append(j);
			}
		}
	}
	for (int i=0; i < eliminar.size(); i++){
		cerrada.append(abierta[eliminar.at(i)]);
		abierta.removeAt(eliminar.at(i));
	}
	eliminar.clear();
}

path trayectoria::obtener_camino_minimo()
{
	QList <int> eliminar;
	while (!abierta.empty()){
		if(abierta.first().camino.top()==laberinto.get_pos_copa()){
			return abierta.first();
		}
		else{
			cerrada.append(abierta.first());
			abierta.removeFirst();

			for (int i=0; i < cerrada.size(); i++){
				if (cerrada.last().camino.top()==cerrada[i].camino.top()){
					if(cerrada.last().H < cerrada[i].H)
						eliminar.append(i);
				}
			}
			for (int i=0; i < eliminar.size(); i++){
				cerrada.removeAt(eliminar.at(i));
			}
			eliminar.clear();

			diversificar();
			ordenar();
			comprobar();
		}
	}

	std::cout << "No tiene solución." << std::endl;

	path room;
	QPoint error(-1,-1);
	room.camino.push(error);
	QList <path> no_solucion;
	no_solucion.append(room);
	return no_solucion.first();
}

