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

//IDs para generación del laberinto
#define ID_MAPA_SI_HAY_SETO 1
#define ID_MAPA_NO_HAY_SETO 0

//Direcciones
#define ID_ORIENTACION_ARRIBA 0
#define ID_ORIENTACION_ABAJO 1
#define ID_ORIENTACION_DERECHA 2
#define ID_ORIENTACION_IZQUIERDA 3

//IDs para imágenes
#define ID_MAPA_OTROS_COMPLETO 250
#define ID_MAPA_OTROS_CUATRO 251
#define ID_MAPA_OTROS_UNICO 252
#define ID_MAPA_OTROS_VACIO 253
#define ID_MAPA_UNA_ABAJO 254
#define ID_MAPA_UNA_ARRIBA 255
#define ID_MAPA_UNA_DERECHA 256
#define ID_MAPA_UNA_IZQUIERDA 257
#define ID_MAPA_DOS_ABA_DER 258
#define ID_MAPA_DOS_ABA_IZQ 259
#define ID_MAPA_DOS_ARR_DER 260
#define ID_MAPA_DOS_ARR_IZQ 260
#define ID_MAPA_DOS_HORIZONTAL 262
#define ID_MAPA_DOS_VERTICAL 263
#define ID_MAPA_TRES_ABAJO 264
#define ID_MAPA_TRES_ARRIBA 265
#define ID_MAPA_TRES_DERECHA 266
#define ID_MAPA_TRES_IZQUIERDA 267

//Entidades
#define ID_ENTIDADES_COPA 350 //Final del mapa
#define ID_ENTIDADES_INICIO 351
#define ID_ENTIDADES_MONSTRUO 352
#define ID_ENTIDADES_GRAGEA 353

/*!
 * \brief Clase mapa
 * Proporciona una interfaz para poder manejar diversas funciones del mapa, como
 * generar el laberinto, obtener tiles dependiendo de lo que haya, etc.
 * \author Daniel Ramos Acosta <alu0100843095@ull.edu.es>
 */
class mapa
{
private:
	/*!
	 * \brief Atributo que contiene la anchura del mapa (x)
	 */
	unsigned tamano_x_;

	/*!
	 * \brief Atributo que contiene la altura del mapa (y)
	 */
	unsigned tamano_y_;

	/*!
	 * \brief Matrix que contiene la posición (y orientación) de los setos.
	 */
	std::vector<std::vector<unsigned> > setos_;

	/*!
	 * \brief Matrix que contiene la posición de las entidades.
	 */
	std::vector<std::vector<unsigned> > entidades_;

	//std::vector<std::vector<unsigned> > background_; No hace falta porque es siempre el mismo tile.

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
	struct una{
		QImage abajo_;
		QImage arriba_;
		QImage derecha_;
		QImage izquierda_;
	} una_;
	struct dos{
		QImage aba_der_;
		QImage aba_izq_;
		QImage arr_der_;
		QImage arr_izq_;
		QImage horizontal_;
		QImage vertical_;
	} dos_;
	struct tres{
		QImage abajo_;
		QImage arriba_;
		QImage derecha_;
		QImage izquierda_;
	} tres_;
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

	//TODO: Documentar: va explorando el laberinto y excavando las paredes de forma recursiva.
	void explora_vecinos_y_excava(QPoint punto_actual, QPoint punto_anterior);

	//TODO: Documentar: retornar verdadero si está alrededor el valor unsigned al menos una vez.
	bool existe_alrededor(QPoint celda, unsigned valor, QPoint omitir);

	//TODO: Documentar: comprueba si la copa está en una casilla adyacente devuelve un -1 si es un error
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
	void resize(unsigned x,unsigned y);

	/*!
	 * \brief Generar el laberinto usando como inicio y final "inicio_", y "final_"
	 */
	void generar_laberinto(void);

	/*!
	 * \brief Colocar los setos aleatoriamente (sin forma de laberinto)
	 * \param porcentaje Porcentaje de ocupación del mapa de los setos
	 */
	void generar_aleatorio(unsigned porcentaje);

	/*!
	 * \brief Colocar una cantidad de monstruos en el mapa
	 * \param cantidad_mon Cantidad de monstruos
	 */
	void colocar_monstruos(unsigned cantidad_mon);

	/*!
	 * \brief Colocar la copa (la salida) en un punto determinado). Por defecto es la esquina inferior derecha.
	 * \param celda Coordenadas de la copa
	 */
	void colocar_copa(QPoint celda);

	/*!
	 * \brief Colocar a harry en un punto determinado. Por defecto es la esquina superior izquierda.
	 * \param celda Coordenadas de harry
	 */
	void colocar_harry(QPoint celda);

	/*!
	 * \brief Obtener la imagen que va en una determinada casilla de la capa background
	 * \param celda La casilla en cuestión
	 * \return La imagen
	 */
	QImage get_tile_bg(QPoint celda);

	/*!
	 * \brief Obtener la imagen que va en una determinada casilla de la capa de los setos
	 * \param celda La casilla en cuestión
	 * \return La imagen
	 */
	QImage get_tile_seto(QPoint celda);

	/*!
	 * \brief Obtener la imagen que va en una determinada casilla de la capa de entidades
	 * \param celda La casilla en cuestión
	 * \return La imagen
	 */
	QImage get_tile_entidad(QPoint celda);

	/*!
	 * \brief Se usa para limpiar una casilla si hay un monstruo o una grajea
	 * \param Celda a limpiar
	 */
	void limpiar_casilla(QPoint celda);

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
