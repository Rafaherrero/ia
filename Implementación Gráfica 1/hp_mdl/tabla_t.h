/*!
 * \file tabla_t.h
 * \brief Contiene la definición de la clase "tabla_t"
 * \author Daniel Ramos Acosta <alu0100843095@ull.edu.es>
 * \date 3 de Noviembre
 */

#ifndef TABLA_T_H
#define TABLA_T_H

#include <vector>
#include <iostream>
#include <QPoint>

#include "common.h"

class tabla_t{
private:
	std::vector<std::vector<id_t> > tabla_; //Vector de vectores para almacenar los datos
	unsigned tam_x_; //Tamaño en x
	unsigned tam_y_; //Tamaño en y
	id_t def_; //Valor por defecto
public:
	/// \name Constructores
	///@{
	/*!
	 * \brief Constructor vacío
	 */
	tabla_t(void);

	/*!
	 * \brief Constructor al que se le pasa el tamaño
	 * \param x Distancia en x de la tabla
	 * \param y Distancia en y de la tabla
	 */
	tabla_t(unsigned x, unsigned y);

	/*!
	 * \brief Constructor con el tamaño y un valor por defecto
	 * \param x Tamaño en x de la tabla
	 * \param y Tamaño en y de la tabla
	 * \param def Valor por defecto de las casillas
	 */
	tabla_t(unsigned x, unsigned y, id_t def);

	///@}

	/// \name Información
	///@{

	/*!
	 * \brief Devuelve el tamaño de x
	 */
	unsigned tam_x(void);

	/*!
	 * \brief Devuelve el tamaño de y
	 */
	unsigned tam_y(void);

	/*!
	 * \brief Devuelve si un punto está dentro del rango de la tabla
	 * \param celda La celda para saber si está en el rango
	 * \return Verdadero si está en el rango, falso en otro caso
	 */
	bool alcanzable(QPoint celda);

	/*!
	 * \brief Devuelve si un punto en una dirección está dentro del rango de la tabla
	 * \param celda La celda para saber si está en el rango
	 * \param sentido El sentido en el que queremos mirar
	 * \return Verdadero si está en el rango, falso en otro caso
	 */
	bool alcanzable(QPoint celda, id_t sentido);

	/*!
	 * \brief Devuelve si un punto está dentro del rango de la tabla contando con los bordes
	 * \param celda La celda para saber si está en el rango
	 * \return Verdadero si está en el rango, falso en otro caso
	 */
	bool alcanzable_bor(QPoint celda);

	/*!
	 * \brief Devuelve si un punto en una dirección está dentro del rango de la tabla contando con los bordes
	 * \param celda La celda para saber si está en el rango
	 * \param sentido El sentido en el que queremos mirar
	 * \return Verdadero si está en el rango, falso en otro caso
	 */
	bool alcanzable_bor(QPoint celda, id_t sentido);

	/*!
	 * \brief Imprime la salida en el buffer de salida
	 * \param os Stream de salida (out stream)
	 */
	void imprime(std::ostream& os);

	///@}

	/// \name Modificadores
	///@{

	/*!
	 * \brief Se usa para modificar el tamaño de la tabla
	 * \param x Tamaño en x de la tabla
	 * \param y Tamaño en y de la tabla
	 */
	void resize(unsigned x, unsigned y);

	/*!
	 * \brief clear Convierte todas las celdas al valor por defecto
	 */
	void clear(void);

	/*!
	 * \brief Convierte todas las celdas a un valor determinado
	 * \param val El valor al que se quiere poner
	 */
	void clear(id_t val);

	///@}

	/// \name Acceso a los elementos
	///@{

	/*!
	 * \brief Se obtiene el valor de un punto concreto
	 * \param coord Coorenadas de la celda
	 * \return Una referencia al elemento (para poder modificarlo)
	 */
	id_t& at(QPoint coord);

	/*!
	 * \brief Se obtiene el valor de un punto concreto en una dirección
	 * \param coord Coorenadas de la celda
	 * \param sentido El sentido de la celda
	 * \return Una referencia al elemento (para poder modificarlo)
	 */
	id_t& at(QPoint coord, id_t sentido);

	///@}
};

#endif // TABLA_T_H
