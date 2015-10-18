#include "common.h"

namespace common
{

unsigned mix(unsigned long a, unsigned long b, unsigned long c)
{
	   a=a-b;  a=a-c;  a=a^(c >> 13);
	   b=b-c;  b=b-a;  b=b^(a << 8);
	   c=c-a;  c=c-b;  c=c^(b >> 13);
	   a=a-b;  a=a-c;  a=a^(c >> 12);
	   b=b-c;  b=b-a;  b=b^(a << 16);
	   c=c-a;  c=c-b;  c=c^(b >> 5);
	   a=a-b;  a=a-c;  a=a^(c >> 3);
	   b=b-c;  b=b-a;  b=b^(a << 10);
	   c=c-a;  c=c-b;  c=c^(b >> 15);
	   return c;
}

unsigned random(void)
{
	std::srand(mix(clock(), time(NULL), getpid()));
	return std::rand();
}

std::string imprqp(QPoint punto)
{
	std::stringstream stream;
	stream << "(" << punto.x() << ", " << punto.y() << ")";
	return stream.str();
}

std::string imprdir(dir_t dir)
{
	switch(dir){
		case ID_ORIENTACION_ABAJO: return std::string("abajo"); break;
		case ID_ORIENTACION_ARRIBA: return std::string("arriba"); break;
		case ID_ORIENTACION_DERECHA: return std::string("derecha"); break;
		case ID_ORIENTACION_IZQUIERDA: return std::string("izquierda"); break;
		case ID_ORIENTACION_ABA_IZQ: return std::string("abajo a la izquierda"); break;
		case ID_ORIENTACION_ARR_IZQ: return std::string("arriba a la derecha"); break;
		case ID_ORIENTACION_ARR_DER: return std::string("arriba a la derecha"); break;
		case ID_ORIENTACION_ABA_DER: return std::string("abajo a la derecha"); break;
	}
	return std::string("??????");
}

QPoint QP(unsigned x, unsigned y)
{
	return QPoint(x,y);
}

QPoint QP(QPoint punto, dir_t dir)
{
	switch(dir){
	case ID_ORIENTACION_ARRIBA: punto.ry()--; break;
	case ID_ORIENTACION_ABAJO: punto.ry()++; break;
	case ID_ORIENTACION_DERECHA: punto.rx()++; break;
	case ID_ORIENTACION_IZQUIERDA: punto.rx()--; break;
	case ID_ORIENTACION_ABA_IZQ: punto.ry()++; punto.rx()--; break;
	case ID_ORIENTACION_ARR_IZQ: punto.ry()--; punto.rx()--; break;
	case ID_ORIENTACION_ARR_DER: punto.ry()--; punto.rx()++; break;
	case ID_ORIENTACION_ABA_DER: punto.ry()++; punto.rx()++; break;
	}
	return punto;
}

}
