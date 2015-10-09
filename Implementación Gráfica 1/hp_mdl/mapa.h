#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <iostream>
#include <QImage>
#include <QPoint>

#include "exceptions.h"
#include "common.h"

//IDs para generación del laberinto
#define MAPA_ID_SI_HAY_SETO 1
#define MAPA_ID_NO_HAY_SETO 0

#define MAPA_ID_ARRIBA 0
#define MAPA_ID_ABAJO 1
#define MAPA_ID_DERECHA 2
#define MAPA_ID_IZQUIERDA 3

//IDs para imágenes
#define MAPA_ID_OTROS_COMPLETO 250
#define MAPA_ID_OTROS_CUATRO 251
#define MAPA_ID_OTROS_UNICO 252
#define MAPA_ID_OTROS_VACIO 253
#define MAPA_ID_UNA_ABAJO 254
#define MAPA_ID_UNA_ARRIBA 255
#define MAPA_ID_UNA_DERECHA 256
#define MAPA_ID_UNA_IZQUIERDA 257
#define MAPA_ID_DOS_ABA_DER 258
#define MAPA_ID_DOS_ABA_IZQ 259
#define MAPA_ID_DOS_ARR_DER 260
#define MAPA_ID_DOS_ARR_IZQ 260
#define MAPA_ID_DOS_HORIZONTAL 262
#define MAPA_ID_DOS_VERTICAL 263
#define MAPA_ID_TRES_ABAJO 264
#define MAPA_ID_TRES_ARRIBA 265
#define MAPA_ID_TRES_DERECHA 266
#define MAPA_ID_TRES_IZQUIERDA 267

#define MAPA_ID_COPA 350 //Final del mapa
#define MAPA_ID_INICIO 351

class mapa
{
private:
	unsigned tamano_x_; //anchura del mapa
	unsigned tamano_y_; //altura del mapa
	std::vector<std::vector<unsigned> > datos_; /*Datos que contiene el laberinto.
	//En principio 0 es desocupado y 1 es ocupado, pero luego
	250 es centro, 251 es completo, etc.
	*/

	QPoint inicio_;
	QPoint final_;
	//Imagenes
	QImage centro_; //FIXME
private:
	void corregir_posicion(void); //Hacerlo si sobra tiempo. Se usa para determinar la dirección de los tiles.
	bool existe_imagen(QString); //Saber si existe una imagen en una ruta determinada
	void importar_imagenes(void); //revisar una por una las imagenes e importarlas a la clase.
	void explora_vecinos_y_excava(QPoint, QPoint); //va explorando el laberinto y excavando las paredes de forma recursiva.
	bool existe_alrededor(QPoint, unsigned, QPoint); //retornar verdadero si está alrededor el valor unsigned al menos una vez.
	unsigned esta_la_copa_alrededor(QPoint); //devuelve un -1 si es un error
public:
	/*!
	 * \brief Constructor vacío
	 */
	mapa(void);

	/*!
	 * \brief Constructor al que se le pasa el tamaño
	 * \param x Tamaño en x del mapa
	 * \param y Tamaño en y del mapa
	 */
	mapa(unsigned,unsigned);

	/*!
	 * \brief Cambiar el tamaño del mapa
	 * \param x Tamaño en x del mapa
	 * \param y Tamaño en y del mapa
	 */
	void resize(unsigned,unsigned);

	/*!
	 * \brief Generar el laberinto usando como inicio y final "inicio_", y "final_"
	 */
	void generar_laberinto();

	/*!
	 * \brief Colocar los setos aleatoriamente (sin forma de laberinto)
	 * \param Porcentaje de ocupación del mapa de los setos
	 */
	void generar_aleatorio(unsigned);

	/*!
	 * \brief Colocar una cantidad de monstruos en el mapa
	 * \param num Cantidad de monstruos
	 */
	void colocar_monstruos(unsigned);

	/*!
	 * \brief Colocar la copa (la salida) en un punto determinado). Por defecto es la esquina inferior derecha.
	 * \param Coordenadas de la copa
	 */
	void colocar_copa(QPoint);

	/*!
	 * \brief Colocar a harry en un punto determinado). Por defecto es la esquina superior izquierda.
	 * \param Coordenadas de harry
	 */
	void colocar_harry(QPoint);

	/*!
	 * \brief Obtener la imagen que va en una determinada casilla
	 * \param La casilla en cuestión
	 * \return La imagen
	 */
	QImage get_tile(QPoint);

	/*!
	 * \brief Devuelve el tamaño en x del mapa
	 * \return La x
	 */
    unsigned& get_x(void);

	/*!
	 * \brief Devuelve el tamaño en y del mapa
	 * \return La y
	 */
    unsigned& get_y(void);
};

#endif // MAPA_H
