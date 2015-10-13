#ifndef COMMON
#define COMMON

#include <QString>
#include <QFileInfo>
#include <QPoint>

#define ID_GLOBAL_NULO 0
#define ID_GLOBAL_HARRY_POTTER 1
#define ID_GLOBAL_COPA_MAGOS 2
#define ID_GLOBAL_SETO 3
#define ID_GLOBAL_PARED 4
#define ID_GLOBAL_GRAGEA 5
#define ID_GLOBAL_MONSTRUO 6

//Cambien a estos defines de aquí abajo
#define ID_GLOBAL_SETO_HAY 1
#define ID_GLOBAL_SETO_NO_HAY 0

#define ID_GLOBAL_ENTIDAD_NULA 0
#define ID_GLOBAL_ENTIDAD_HARRY_POTTER 1
#define ID_GLOBAL_ENTIDAD_COPA_MAGOS 2
#define ID_GLOBAL_ENTIDAD_GRAGEA 3
#define ID_GLOBAL_ENTIDAD_MONSTRUO 4

//Orientaciones
#define ID_ORIENTACION_ARRIBA 0
#define ID_ORIENTACION_ABAJO 1
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

typedef unsigned id_t;

#define TAMANO_X 6
#define TAMANO_Y 6

#endif // COMMON

