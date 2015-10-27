/*!
 * \file mapa_t.h
 * \brief Contiene la definición de la clase "mapa_t"
 * \author Daniel Ramos Acosta <alu0100843095@ull.edu.es>
 * \date 9 de Octubre
 */

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <iostream>
#include <QImage>
#include <QPoint>

#include "exceptions.h"
#include "common.h"
#include "tabla_t.h"

//IDs para generación del laberinto
#define ID_MAPA_SI_HAY_SETO 1
#define ID_MAPA_NO_HAY_SETO 0

//Revisar en forma de reloj
#define ID_SENTIDO_RELOJ_DERECHA 0
#define ID_SENTIDO_RELOJ_ABA_DER 1
#define ID_SENTIDO_RELOJ_ABAJO 2
#define ID_SENTIDO_RELOJ_ABA_IZQ 3
#define ID_SENTIDO_RELOJ_IZQUIERDA 4
#define ID_SENTIDO_RELOJ_ARR_IZQ 5
#define ID_SENTIDO_RELOJ_ARRIBA 6
#define ID_SENTIDO_RELOJ_ARR_DER 7

class mapa_t
{
private:
	unsigned tam_x_;
	unsigned tam_y_;
	tabla_t setos_;
	tabla_t entidades_;

	QPoint harry_pos_;
	QPoint copa_pos_;
private:
	//Métodos para crear el laberinto
	void explora_vecinos_y_excava(QPoint celda); //Método recursivo que crea el laberinto
	bool existe_casilla_ocupable(QPoint celda); //Devuelve si una celda tiene ocupables a su alrededor
	QPoint casilla_aleatoria_ocupable(QPoint celda); //Devuelve una casilla que se pueda ocupar. Si no encuentra ninguna devuelve (-1,-1)
	bool tienes_adyacentes(QPoint celda, dir_t origen); //Devuelve verdadero si tiene adyacentes, falso si no.
	dir_t convertir_reloj(dir_t i); //Para iterar de forma circular sobre las direcciones, emepzando por las 9.
	void terminar_generar(void); //Reemplaza los tipos de generación por el tipo global del laberinto

	void corregir_posiciones(void); //Usado para convertir de hay seto o no hay seto, a esquinas e intersecciones y id de tiles.

public:
	/// \name Constructores
	///@{

	/*!
	 * \brief Constructor al que se le pasa el tamaño
	 * \param x Tamaño en x del mapa
	 * \param y Tamaño en y del mapa
	 */
	mapa_t(unsigned x ,unsigned y);

	///@}

	/// \name Información
	///@{

	/*!
	 * \brief Devuelve el tamaño en x del mapa
	 * \return La x
	 */
	unsigned get_x(void);

	/*!
	 * \brief Devuelve el tamaño en y del mapa
	 * \return La y
	 */
	unsigned get_y(void);

	/*!
	 * \brief Devuelve el punto en el se encuentra harry
	 * \return Punto en cuestión
	 */
	QPoint get_pos_harry(void);

	/*!
	 * \brief Devuelve el punto en el se encuentra la copa
	 * \return Punto en cuestión
	 */
	QPoint get_pos_copa(void);

	/*!
	 * \brief Se usa para contar todos los setos
	 * \return devuelve el número de setos
	 */
	unsigned contar_setos(void);

	/*!
	 * \brief Se usa para contar todo el césped
	 * \return devuelve el número de césped
	 */
	unsigned contar_cesped(void);

	/*!
	 * \brief Se usa para contar todas las entidades
	 * \return devuelve el número de entidades
	 */
	unsigned contar_entidades(void);

	/*!
	 * \brief Se usa para contar una concreta especie de entidad
	 * \param entidad la entidad en cuestión
	 * \return devuelve el número de coincidencias
	 */
	unsigned contar_entidades(id_t entidad);

	///@}

	/// \name Modificación interna
	///@{

	/*!
	 * \brief Cambiar el tamaño del mapa
	 * \param x Tamaño en x del mapa
	 * \param y Tamaño en y del mapa
	 */
	void resize(unsigned x,unsigned y);

	/*!
	 * \brief Se usa para limpiar el mapa entero y ponerlo todo a vacío
	 */
	void limpiar(void);

	/*!
	 * \brief Se usa para limpiar una casilla (en todas las capas)
	 * \param Celda a limpiar
	 */
	void limpiar(QPoint celda);

	///@}

	/// \name Generaciones del laberinto
	///@{

	/*!
	 * \brief Generar el laberinto usando como inicio y final "inicio_", y "final_"
	 */
	void generar_laberinto(void);

	/*!
	 * \brief Colocar los setos aleatoriamente (sin forma de laberinto)
	 * \param porcentaje Porcentaje de ocupación del mapa de los setos
	 */
	void generar_aleatorio(unsigned porcentaje);

	///@}

	/// \name Modificación de entidades
	///@{

	/*!
	 * \brief Colocar una cantidad de monstruos en el mapa
	 * \param cantidad_mon Cantidad de monstruos
	 */
	void colocar_monstruos(unsigned cantidad);

	/*!
	 * \brief Mover la copa (la salida) en un punto determinado). Por defecto es la esquina inferior derecha.
	 * \param celda Coordenadas de la copa
	 */
	void mover_copa(QPoint celda);

	/*!
	 * \brief Mover a harry en un punto determinado. Por defecto es la esquina superior izquierda.
	 * \param celda Coordenadas de harry
	 */
	void mover_harry(QPoint celda);

	/*!
	 * \brief Mover a harry en una determinada dirección
	 * \param sentido Dirección en la que se mueve (según los defines de common.h)
	 */
	void mover_harry(dir_t sentido);

	///@}

	/// \name Modificación directas
	///@{

	/*!
	 * \brief Se usa para saber conseguir la ID del seto de esa casilla.
	 * \param celda La casilla en cuestión
	 * \return Verdadero si hay un seto, falso si no
	 */
	id_t& get_seto(QPoint celda);

	/*!
	 * \brief Se usa para saber conseguir la ID del seto de esa casilla.
	 * \param celda La casilla en cuestión
	 * \param dir Cirección en la que quieres mirar.
	 * \return Verdadero si hay un seto, falso si no
	 */
	id_t& get_seto(QPoint celda, dir_t dir);

	/*!
	 * \brief Se usa para devolver la ID de la entidad de una casilla.
	 * \param celda La casilla en cuestión
	 * \return Devuelve el ID de la entidad
	 */
	id_t& get_ent(QPoint celda);

	/*!
	 * \brief Se usa para devolver la ID de la entidad de una casilla.
	 * \param celda La casilla en cuestión7
	 * \param dir Cirección en la que quieres mirar.
	 * \return Devuelve el ID de la entidad
	 */
	id_t& get_ent(QPoint celda, dir_t dir);



	///@}
};

#endif // MAPA_H
