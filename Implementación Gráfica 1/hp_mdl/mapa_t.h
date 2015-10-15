/*!
 * \file mapa.h
 * \brief Contiene la definición de la clase "mapa"
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

//IDs para imágenes
#define ID_MAPA_OTROS_COMPLETO 100
#define ID_MAPA_OTROS_CUATRO 101
#define ID_MAPA_OTROS_UNICO 102
#define ID_MAPA_OTROS_VACIO 103
#define ID_MAPA_UNA_ABAJO 104
#define ID_MAPA_UNA_ARRIBA 105
#define ID_MAPA_UNA_DERECHA 106
#define ID_MAPA_UNA_IZQUIERDA 107
#define ID_MAPA_DOS_ABA_DER 108
#define ID_MAPA_DOS_ABA_IZQ 109
#define ID_MAPA_DOS_ARR_DER 110
#define ID_MAPA_DOS_ARR_IZQ 111
#define ID_MAPA_DOS_HORIZONTAL 112
#define ID_MAPA_DOS_VERTICAL 113
#define ID_MAPA_TRES_ABAJO 114
#define ID_MAPA_TRES_ARRIBA 115
#define ID_MAPA_TRES_DERECHA 116
#define ID_MAPA_TRES_IZQUIERDA 117

//Revisar en forma de reloj
#define ID_SENTIDO_RELOJ_ABAJO 0
#define ID_SENTIDO_RELOJ_ABA_IZQ 1
#define ID_SENTIDO_RELOJ_IZQUIERDA 2
#define ID_SENTIDO_RELOJ_ARR_IZQ 3
#define ID_SENTIDO_RELOJ_ARRIBA 4
#define ID_SENTIDO_RELOJ_ARR_DER 5
#define ID_SENTIDO_RELOJ_DERECHA 6
#define ID_SENTIDO_RELOJ_ABA_DER 7

//Entidades
#define ID_ENTIDADES_COPA 350 //Final del mapa
#define ID_ENTIDADES_INICIO 351
#define ID_ENTIDADES_MONSTRUO 352
#define ID_ENTIDADES_GRAGEA 353


class mapa_t
{
private:
	unsigned tamano_x_;
	unsigned tamano_y_;
	tabla_t setos_;
	tabla_t entidades_;

	QPoint inicio_;
	QPoint final_;
private:
	void corregir_posiciones(void); //Usado para convertir de hay seto o no hay seto, a esquinas e intersecciones y id de tiles.
	bool existe_imagen(QString ruta); //Comprobar si existe una determinada imagen en la ruta especificada
	void importar_imagenes(void); //Importar todos los sprites a la clase.

	//Métodos para crear el laberinto
	void explora_vecinos_y_excava(QPoint celda); //Método recursivo que crea el laberinto
	bool existe_casilla_ocupable(QPoint celda); //Devuelve si una celda tiene ocupables a su alrededor
	QPoint casilla_ocupable(QPoint celda); //Devuelve una casilla que se pueda ocupar. Si no encuentra ninguna devuelve (-1,-1)
	bool tienes_adyacentes(QPoint celda, dir_t origen); //Devuelve verdadero si tiene adyacentes, falso si no.
	id_t convertir_reloj(dir_t i);
	void terminar_generar(void);

public:
	/// \name Constructores
	///@{

	/*!
	 * \brief Constructor vacío
	 */
	mapa_t(void);

	/*!
	 * \brief Constructor al que se le pasa el tamaño
	 * \param x Tamaño en x del mapa_t
	 * \param y Tamaño en y del mapa_t
	 */
	mapa_t(unsigned x ,unsigned y);

	///@}

	/// \name Información
	///@{

	/*!
	 * \brief Devuelve el tamaño en x del mapa_t
	 * \return La x
	 */
	unsigned get_x(void);

	/*!
	 * \brief Devuelve el tamaño en y del mapa_t
	 * \return La y
	 */
	unsigned get_y(void);

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
	 * \brief Cambiar el tamaño del mapa_t
	 * \param x Tamaño en x del mapa_t
	 * \param y Tamaño en y del mapa_t
	 */
	void resize(unsigned x,unsigned y);

	/*!
	 * \brief Se usa para limpiar el mapa_t entero y ponerlo todo a vacío
	 */
	void limpiar(void);

	/*!
	 * \brief Se usa para limpiar una casilla si hay un monstruo o una grajea
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
	 * \param porcentaje Porcentaje de ocupación del mapa_t de los setos
	 */
	void generar_aleatorio(unsigned porcentaje);

	///@}

	/// \name Modificación de entidades
	///@{

	/*!
	 * \brief Colocar una cantidad de monstruos en el mapa_t
	 * \param cantidad_mon Cantidad de monstruos
	 */
	void colocar_monstruos(unsigned cantidad);

	/*!
	 * \brief Colocar la copa (la salida) en un punto determinado). Por defecto es la esquina inferior derecha.
	 * \param celda Coordenadas de la copa
	 */
	void mover_copa(QPoint celda);

	/*!
	 * \brief Colocar a harry en un punto determinado. Por defecto es la esquina superior izquierda.
	 * \param celda Coordenadas de harry
	 */
	void mover_harry(QPoint celda);

	/*!
	 * \brief Colocar a harry en un punto determinado. Por defecto es la esquina superior izquierda.
	 * \param celda Coordenadas de harry
	 */
	void mover_harry(QPoint celda, dir_t sentido);

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
	 * \brief Se usa para devolver la ID de la entidad de una casilla.
	 * \param celda La casilla en cuestión
	 * \return Devuelve el ID de la entidad
	 */
	id_t& get_ent(QPoint celda);

	///@}
};

#endif // mapa_t_H
