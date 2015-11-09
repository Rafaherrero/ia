/*!
 * \file harryPotter.h
 * \brief Contiene la definición de la clase "harryPotter"
 * \author Airam Manuel Navas Simón <alu0100618426@ull.edu.es>
 * \date 9 de Octubre
 */

#ifndef harryPotter_H
#define harryPotter_H

#include <common.h>
#include <mapa_t.h>
#include <QStack>
#include <cmath>

class harryPotter
{
	/*!
	  * \brief Clase del muñeco de Harry Potter
	  *
	  * \author Rafael Herrero Álvarez <alu0100812275@ull.edu.es>
	  */

private:
	QPoint posicion_harry; //Posición actual de harry FIXME: Redundante, ya que se puede guardar en el mapa
	unsigned vidas; //Vidas actuales de harry TODO: No usado
	unsigned mana; //Nivel de maná de harry TODO: No usado
	mapa_t& laberinto; //Referencia al mapa en el que se encuentra harry
	tabla_t marcar; //Tabla que se usa para marcar en el DFS, y para guardar las estimas heurísticas
	QPoint get_next_dir(); //Obtener el siguiente movimiento del DFS
	QStack<QPoint> stack; //Pila usada para la implementación del DFS
	QPoint aux; //TODO
	bool primera_vez; //Primera vez que se ejecuta el algoritmo (el que sea)
	bool encontrada_copa; //false=copa no encontrada, true=copa encontrada
	unsigned costo_transicion_; //Coste de los nodos
	bool tipo_distancia_; //falso = manhattan, true = euclides

public:
	/// \name Constructores
	/// @{
	/*!
	 * \brief Constructor de Harry al que se le pasa el mapa (para que pueda moverse y obtener la información)
	 * \param lab El laberinto en el que se encuentra harry
	 */
	harryPotter(mapa_t& lab);
	///@}

	QPoint get_posicion_harry();
	void set_posicion_harry(QPoint pos);
	void set_posicion_harry_nuevo (QPoint nueva_posicion);

	bool estoy_en_la_copa();
	unsigned& costo_transicion(void);
	bool& tipo_distancia(void);

	bool puedo_continuar_DFS();
	QPoint movimiento_DFS();
	QPoint get_next_dir_DFS();


	unsigned funcion_heuristica_prox(QPoint);

	bool puedo_continuar_estrella();
	QPoint movimiento_estrella();

	bool puedo_continuar_LRTA();
	QPoint movimiento_LRTA();
	QPoint get_next_dir_LRTA();

	unsigned get_mana();
	unsigned get_vidas();
	void set_mana(unsigned mana_encontrado);
	void set_vidas(unsigned vida_gastada);

};

#endif // harryPotter_H
