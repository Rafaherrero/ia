#ifndef COMMON
#define COMMON

#include <unistd.h>
#include <QString>
#include <QFileInfo>
#include <QPoint>

//TODO: Borrar después de depurar
#include <sstream>
#include <string>

//IDs de entidades y setos

typedef unsigned id_t;

#define ID_GLOBAL_SETO_HAY 1
#define ID_GLOBAL_SETO_NO_HAY 0

#define ID_GLOBAL_ENTIDAD_NULA 0
#define ID_GLOBAL_ENTIDAD_HARRY_POTTER 1
#define ID_GLOBAL_ENTIDAD_COPA_MAGOS 2
#define ID_GLOBAL_ENTIDAD_GRAGEA 3
#define ID_GLOBAL_ENTIDAD_MONSTRUO 4

//Distintas direcciones en las que podemos ir

typedef unsigned dir_t;

#define ID_ORIENTACION_ABAJO 0
#define ID_ORIENTACION_ARRIBA 1
#define ID_ORIENTACION_DERECHA 2
#define ID_ORIENTACION_IZQUIERDA 3
#define ID_ORIENTACION_ABA_IZQ 4
#define ID_ORIENTACION_ARR_IZQ 5
#define ID_ORIENTACION_ARR_DER 6
#define ID_ORIENTACION_ABA_DER 7

//IDs para el algoritmo de generación
#define ID_GENERACION_VISITADO 400
#define ID_GENERACION_MARCADO 103
#define ID_GENERACION_VACIO 100

//TODO: Esto de aquí se debería pedir por pantalla

#define TAMANO_X 60
#define TAMANO_Y 40

#define TAMANO_ICONO 18

namespace common{
	unsigned mix(unsigned long a, unsigned long b, unsigned long c);
	unsigned random(void);
	//TODO: Borrar después de depurar
	std::string imprqp(QPoint punto);
	std::string imprdir(dir_t dir);
	QPoint QP(unsigned x, unsigned y);
	QPoint QP(QPoint punto, dir_t dir);
}

#endif // COMMON
