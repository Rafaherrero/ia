/*!
 * \file harry_potter.h
 * \brief Contiene la definición de la clase "harry_potter"
 * \author Rafael Herrero Álvarez <alu0100812275@ull.edu.es>
 * \date 9 de Octubre
 */

#ifndef HARRY_POTTER_H
#define HARRY_POTTER_H

#include <common.h>
#include <mapa.h>

class harry_potter
{
	/*!
	  * \brief Clase del muñeco de Harry Potter
	  *
	  * \author Rafael Herrero Álvarez <alu0100812275@ull.edu.es>
	  */

private:
	QPoint posicion_harry;
	unsigned vidas;
	unsigned mana;
	mapa& laberinto;
	harry_potter();  //Lo ponemos aqui porque Dani lo quiso así

public:

	harry_potter(mapa& lab);
	QPoint get_posicion_harry();
	void set_posicion_harry(QPoint ranas_de_chocolate);
	void set_mana(unsigned mana_encontrado);
	void set_vidas(unsigned vida_gastada);
	void movimiento();
	unsigned get_mana();
	unsigned get_vidas();
};

#endif // HARRY_POTTER_H
