#ifndef TRAYECTORIA_H
#define TRAYECTORIA_H
#include <QStack>
#include <QList>
#include <common.h>
#include <mapa_t.h>

struct path{
	QStack<QPoint> camino;
	int H;
};

class trayectoria
{
	private:
		QList<path> abierta;
		QList<path> cerrada;
		mapa_t& laberinto;

		int manhattan(QPoint origen);
		void diversificar();
		void ordenar();
		void comprobar();

	public:
		trayectoria(mapa_t& lab, QPoint pos_harry);
		~trayectoria();

		path obtener_camino_minimo();

};

#endif // TRAYECTORIA_H
