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
	/*!
	 * \brief Atributo que contiene la anchura del mapa (x)
	 */
	unsigned tamano_x_; //anchura del mapa

	/*!
	 * \brief Atributo que contiene la altura del mapa (y)
	 */
	unsigned tamano_y_; //altura del mapa

	/*!
	 * \brief Matrix que contiene los datos.
	 * Los datos se guardan en forma de unsigned, codificados según los define
	 * que están arriba. Por ejemplo, el 350 sería la copa.
	 */
	std::vector<std::vector<unsigned> > datos_;

	/*!
	 * \brief Lugar donde Harry Potter empezaría a caminar.
	 */
	QPoint inicio_;

	/*!
	 * \brief Lugar donde se encuentra a copa
	 */
	QPoint final_;

	//Cargar las imágenes en la clase
	struct otros{
		QImage completo_;
		QImage cuatro_;
		QImage unico_;
		QImage vacio_;
	} otros_;
	//FIXME: Añadir resto de imagenes
private:
	/*!
	 * \brief Convetir los muros simples a muros complejos conectados
	 * Sirve para corregir los muros, y convertirlos de simples muros cuadrados
	 * a muros que se interconectan entre ellos usando esquinas, intersecciones,
	 * etc. Hacerlo si sobra tiempo.
	 */
	void corregir_posicion(void);

	/*!
	 * \brief Se usa para saber si existe una determinada imagen en una ruta.
	 * \param ruta Ruta en la que está localizada la imagen a comprobar.
	 * \return Verdadero si existe, falso en otro caso.
	 */
	bool existe_imagen(QString ruta);

	/*!
	 * \brief Se usa para importar una a una las imágenes e incluirlas en la clase como QImage
	 */
	void importar_imagenes(void);

	//DOCUMENTAME: va explorando el laberinto y excavando las paredes de forma recursiva.
	void explora_vecinos_y_excava(QPoint punto_actual, QPoint punto_anterior);

	//DOCUMENTAME: retornar verdadero si está alrededor el valor unsigned al menos una vez.
	bool existe_alrededor(QPoint celda, unsigned valor, QPoint omitir);

	//DOCUMENTAME: comprueba si la copa está en una casilla adyacente devuelve un -1 si es un error
	unsigned esta_la_copa_alrededor(QPoint celda);
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
	mapa(unsigned x ,unsigned y);

	/*!
	 * \brief Cambiar el tamaño del mapa
	 * \param x Tamaño en x del mapa
	 * \param y Tamaño en y del mapa
	 */
	void resize(unsigned,unsigned);

	/*!
	 * \brief Generar el laberinto usando como inicio y final "inicio_", y "final_"
	 */
	void generar_laberinto(void);

	/*!
	 * \brief Colocar los setos aleatoriamente (sin forma de laberinto)
	 * \param Porcentaje de ocupación del mapa de los setos
	 */
	void generar_aleatorio(unsigned);

	/*!
	 * \brief Colocar una cantidad de monstruos en el mapa
	 * \param num Cantidad de monstruos
	 */
	void colocar_monstruos(unsigned cantidad_mon);

	/*!
	 * \brief Colocar la copa (la salida) en un punto determinado). Por defecto es la esquina inferior derecha.
	 * \param Coordenadas de la copa
	 */
	void colocar_copa(QPoint celda);

	/*!
	 * \brief Colocar a harry en un punto determinado). Por defecto es la esquina superior izquierda.
	 * \param Coordenadas de harry
	 */
	void colocar_harry(QPoint celda);

	/*!
	 * \brief Obtener la imagen que va en una determinada casilla
	 * \param La casilla en cuestión
	 * \return La imagen
	 */
	QImage get_tile(QPoint celda);

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
