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
#define ID_ORIENTACION_ABA_IZQ 4
#define ID_ORIENTACION_ARR_IZQ 5
#define ID_ORIENTACION_ARR_DER 6
#define ID_ORIENTACION_ABA_DER 7

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

//IDs para el algoritmo de generación
#define ID_GENERACION_VISITADO 400
#define ID_GENERACION_MARCADO 103
#define ID_GENERACION_VACIO 100

struct nodo_mapa{
	QPoint coord_;
	id_t valor_;
};

class tabla_t{
private:
	std::vector<std::vector<nodo_mapa> > tabla_;
	unsigned tamano_x_;
	unsigned tamano_y_;
	void actualizar_puntos(void);
	void desplazar_punto(QPoint& punto, id_t dir);
public:
	tabla_t(void);
	tabla_t(unsigned x, unsigned y);
	tabla_t(unsigned x, unsigned y, id_t val);
	void resize(unsigned x, unsigned y);
	nodo_mapa& at(QPoint coord);
	nodo_mapa& at_dir(QPoint coord, id_t dir);
	unsigned t_x(void);
	unsigned t_y(void);
	void clear(id_t val);
	bool alcanzable(QPoint celda);
	bool alcanzable(QPoint celda, id_t dir);
	void imprime(std::ostream& os);
};

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
	//Metodos de acceso a la tabla

	void corregir_posicion(void);
	bool existe_imagen(QString ruta);
	void importar_imagenes(void);

	void explora_vecinos_y_excava(QPoint celda);

	bool tiene_vecinos_sin_visitar(QPoint celda);

	unsigned dame_uno_ocupable(QPoint celda);

	bool tienes_adyacentes(QPoint celda, QPoint ignorar);

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
