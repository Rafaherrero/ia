#include "trayectoria.h"

trayectoria::trayectoria(mapa_t& lab, QPoint pos_harry):
	laberinto(lab)
{
	path room;
	room.camino.push(pos_harry);
	room.coste=0;
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
	path ultima_trayectoria_eliminada = cerrada.last();
	QPoint nodo_final_trayectoria = ultima_trayectoria_eliminada.camino.top();

	for (int i = 0; i < 4; i++){ //Revisar en todas las direcciones
		QPoint revisar_nodo = common::QP(nodo_final_trayectoria, i);
		if(laberinto.get_seto(revisar_nodo) == ID_GLOBAL_SETO_NO_HAY){ //Si podemos expandirnos en esa direccion
			path nueva_trayectoria = ultima_trayectoria_eliminada; //Crear nueva trayectoria a partir de la trayectoria eliminada
			nueva_trayectoria.camino.push(revisar_nodo); //Añadiendo la direcciona en la que vamos
			nueva_trayectoria.coste++; //Incrementar coste de la trayectoria
			abierta.append(nueva_trayectoria); //Añadir la nueva trayectoria a la lista de abiertas
		}
	}
}

/* 2B4 Ordenar lista abierta donde el primer
 * valor es el valor minimo
*/
void trayectoria::ordenar() //Usar algoritmo de la burbuja para ordenar de menor a mayor según el COSTE ESTIMANDO
{
	bool change = true;
	for(std::size_t i = 1; (i < abierta.size()) && (change); i++){
		change = false;
		for(std::size_t j = abierta.size()-1; j >= i; j--)
			if( abierta[j].coste+manhattan(abierta[j].camino.top()) < abierta[j-1].coste+manhattan(abierta[j-1].camino.top())){
				std::swap(abierta[j-1], abierta[j]);
				change = true;
			}
	}
}

/* 2B5
*/
void trayectoria::comprobar()
{
	bool i_eliminado = false;
	for(int i = 0; i < abierta.size(); i++){ //Para cada elemento de abierta
		i_eliminado = false;
		for(int j = 0; j < abierta.size() && !i_eliminado; j++){ //Comparar on el resto de elementos
			if(abierta[i].camino.top() == abierta[j].camino.top()){ //Si son trayectorias equivalentes
				if(i != j){ //Saltarnos si somos nosotros mismos
					if(abierta[i].coste < abierta[j].coste){ //Si el j es mayor
						abierta.removeAt(j); //Eliminamos j
						j--; //No incrementeamos j ya que disminuye el índice del actual
					}
					else{
						abierta.removeAt(i); //Si i es mayor,
						i_eliminado = true; //eliminamos i y dejamos de comprobar con el resto
						i--; //No incrementeamos i ya que disminuye el índice del actual
					}
				}
			}

		}
	}
	//En este punto, hemos eliminado las trayectorias de ABIERTA equivalentes, y hemos dejado la de coste mínimo
	i_eliminado = false;
	for(int i = 0; i < abierta.size(); i++){ //Para cada trayectoria de ABIERTA
		i_eliminado = false;
		for(int j = 0; j < cerrada.size() && !i_eliminado; j++){ //Revisar una de cerrada
			if(abierta[i].camino.top() == cerrada[j].camino.top()){ //Si hay una trayectoria equivalente en CERRADA
				if(abierta[i].coste < cerrada[j].coste){ //Si el coste de la trayectoria de CERRADA es mayor,
					cerrada.removeAt(j); //Eliminamos la trayectoria j de CERRADA
					j--; //No incrementamos ya que disminuye el índice actual
				}
				else{
					abierta.removeAt(i); //Si i es mayor,
					i_eliminado = true; //eliminamos i y dejamos de comprobar con el resto
					i--; //No incrementeamos i ya que disminuye el índice del actual
				}
			}
		}
	}
}

path trayectoria::obtener_camino_minimo()
{
	while (!abierta.empty()){ //mientras la lista abierta no esté vacía
		if(abierta.first().camino.top()==laberinto.get_pos_copa()){ //Si la trayectoria actual termina en el nodo objetivo
			return abierta.first(); //Terminar y devolver la trayectoria
		}
		else{ //Si la primera trayectoria no termina en el nodo objetivo

			cerrada.append(abierta.first());
			abierta.removeFirst();

			for (int i=0; i < cerrada.size(); i++){ //Revisar todos los elmenetos de cerrada
				if (cerrada.last().camino.top()==cerrada[i].camino.top()){ //Si encontramos una trayectoria equivalente
					if(cerrada.last().coste < cerrada[i].coste){ //Y el coste de esa trayectoria es mayor
						cerrada.removeAt(i); //Eliminamos la trayectoria
						i--; //Movemos el iterado hacia atrás para mirar el siguiente elemento
					}
				}
			}

			diversificar(); //Fomar nuevas trayectorias nuevas a partir de el último nodo eliminado (ultimo nodo en cerrada)
			//Añadir las nuevas ramificaciones a abierta (si es que hay)

			ordenar(); //Ordenar la lista ABIERTA en base al costo total estimado de cada una,
			//colocando la de mínimo coste al inicio de la lista.

			comprobar(); //Si existen trayectorias similares en ABIERTA eliminar y dejar la de mínimo coste (en abierta)
			//Si en cerrada existe una trayectoria similar a la de ABIERTA borrar la de abierta
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

int trayectoria::get_fx(path tray){
	return tray.coste + manhattan(tray.camino.top());
}
