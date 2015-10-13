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
#include <ctime>
#include <unistd.h>
#include <cstdlib>

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

//Entidades
#define ID_ENTIDADES_COPA 350 //Final del mapa
#define ID_ENTIDADES_INICIO 351
#define ID_ENTIDADES_MONSTRUO 352
#define ID_ENTIDADES_GRAGEA 353

struct imagenes_t{
	struct otros_t{
		QImage completo_;
		QImage cuatro_;
		QImage unico_;
		QImage vacio_;
	} otros_;
	struct una_t{
		QImage abajo_;
		QImage arriba_;
		QImage derecha_;
		QImage izquierda_;
	} una_;
	struct dos_t{
		QImage aba_der_;
		QImage aba_izq_;
		QImage arr_der_;
		QImage arr_izq_;
		QImage horizontal_;
		QImage vertical_;
	} dos_;
	struct tres_t{
		QImage abajo_;
		QImage arriba_;
		QImage derecha_;
		QImage izquierda_;
	} tres_;
};

class mapa
{
private:
	unsigned tamano_x_;
	unsigned tamano_y_;
	tabla_t setos_;
	tabla_t entidades_;
	//std::vector<std::vector<unsigned> > background_; No hace falta porque es siempre el mismo tile.

	QPoint inicio_;
	QPoint final_;

	//Cargar las imágenes en la clase
	imagenes_t imagenes_;
private:
	void corregir_posicion(void); //Usado para convertir de hay seto o no hay seto, a esquinas e intersecciones
	bool existe_imagen(QString ruta); //Comprobar si existe una determinada imagen en la ruta especificada
	void importar_imagenes(void); //Importar todos los sprites a la clase.

	//Métodos para crear el laberinto
	void explora_vecinos_y_excava(QPoint celda); //Método recursivo que crea el laberinto
	bool existe_casilla_ocupable(QPoint celda); //Devuelve si una celda tiene ocupables a su alrededor
	QPoint casilla_ocupable(QPoint celda); //Devuelve una casilla que se pueda ocupar. Si no encuentra ninguna devuelve (-1,-1)
	bool tienes_adyacentes(QPoint celda); //Devuelve verdadero si tiene adyacentes, falso si no.

	//Generar numeros aleatorios
	unsigned long mix(unsigned long a, unsigned long b, unsigned long c);
	unsigned long random(void);

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
	 * \brief Se usa para saber si en una celda existe un seto, o no.
	 * \param celda La casilla en cuestión
	 * \return Verdadero si hay un seto, falso si no
	 */
	bool get_seto(QPoint celda);//Demandado por rafa y airam

	/*!
	 * \brief Se usa para devolver la ID de la entidad de una casilla.
	 * \param celda La casilla en cuestión
	 * \return Devuelve el ID de la entidad
	 */
	id_t get_entidad(QPoint celda); //Demandado por rafa y airam

	/*!
	 * \brief Se usa para devolver la mezcla de lo que haya en una casilla
	 * \param celda La casilla en cuestión
	 * \return Devuelve el ID de lo que sea
	 */
	id_t get(QPoint celda);

	/*!
	 * \brief Se usa para contar una concreta especie de entidad
	 * \param entidad la entidad en cuestión
	 * \return devuelve el número de coincidencias
	 */
	unsigned contar_entidades(id_t entidad); //Demandado por rafa

	/*!
	 * \brief Se usa para limpiar una casilla si hay un monstruo o una grajea
	 * \param Celda a limpiar
	 * \return devuelve el número de esas entidades encontradas
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
