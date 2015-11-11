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
#include <trayectoria.h>
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

	unsigned funcion_heuristica_prox(QPoint);// Función de estimación heurística por proximidad al objetivo
	QPoint get_next_dir_DFS(); //Metodo para obtener el siguiente paso del DFS
	QPoint get_next_dir_LRTA(); //Método para obtener el siguiente paso del LRTA*
	bool estoy_en_la_copa(); //Metodo para saber si estamos situados sobre la copa
public:
	/// \name Constructores
	/// @{
	/*!
	 * \brief Constructor de Harry al que se le pasa el mapa (para que pueda moverse y obtener la información)
	 * \param lab El laberinto en el que se encuentra harry
	 */
	harryPotter(mapa_t& lab);
	///@}

	/// \name Accesores a Harry
	/// @{
	/*!
	 * \brief Método para obetener la posición de Harry
	 * \return El Punto en el que se encuentra Harry
	 */
	QPoint get_posicion_harry();

	/*!
	 * \brief Método para cambiar la posición de Harry
	 * \param pos Posición a la que se desea cambiar
	 */
	void set_posicion_harry(QPoint pos);

	/*!
	 * \brief Además de cambiar la posición, este método resetea todo el laberinto y hace una limpieza
	 * \param nueva_posicion Nueva posición de Harry.
	 */
	void set_posicion_harry_nuevo (QPoint nueva_posicion);
	///@}

	/// \name Modifición de parámetros de los Algoritmos
	///@{

	/*!
	 * \brief Se usa para modificar el coste de la transición entre los nodos
	 * \return Una referencia al coste
	 */
	unsigned& costo_transicion(void);

	/*!
	 * \brief Con esto se cambia el tipo de distancia, entre manhattan o eculides
	 * \return Una referencia al valor booleano, false=manhattan, true=euclides
	 */
	bool& tipo_distancia(void);
	///@}

	/// \name Algoritmos disponibles
	/// @{
	/*!
	 * \brief Analiza todas las condiciones de parada del DFS
	 * \return Si es falso Harry muere o encuentra la copa, en otro caso continua la ejecución
	 */
	bool puedo_continuar_DFS();

	/*!
	 * \brief Ejecuta una iteración del algoritmo DFS
	 * \return Devuelve la posicion actual de Harry
	 */
	QPoint movimiento_DFS();

	/*!
	 * \brief Analiza todas las condiciones de parada del A*
	 * \return Si es falso Harry muere o encuentra la copa, en otro caso continua la ejecución
	 */
	bool puedo_continuar_estrella();

	/*!
	 * \brief Ejecuta una iteración del algoritmo A*
	 * \return Devuelve la posicion actual de Harry
	 */
	QStack<QPoint> movimiento_estrella();

	/*!
	 * \brief Analiza todas las condiciones de parada del LRTA*
	 * \return Si es falso Harry muere o encuentra la copa, en otro caso continua la ejecución
	 */
	bool puedo_continuar_LRTA();

	/*!
	 * \brief Ejecuta una iteración del algoritmo LRTA*
	 * \return Devuelve la posicion actual de Harry
	 */
	QPoint movimiento_LRTA();

	/*!
	 * \brief Analiza todas las condiciones de parada del RTA*
	 * \return Si es falso Harry muere o encuentra la copa, en otro caso continua la ejecución
	 */
	bool puedo_continuar_RTA();

	/*!
	 * \brief Ejecuta una iteración del algoritmo RTA*
	 * \return Devuelve la posicion actual de Harry
	 */
	QPoint movimiento_RTA();



	///@}

	/// \name Métodos en deshuso
	///@{
	unsigned get_mana();
	unsigned get_vidas();
	void set_mana(unsigned mana_encontrado);
	void set_vidas(unsigned vida_gastada);
	///@}
};

#endif // harryPotter_H
