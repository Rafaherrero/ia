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

std::string imprdir(QPoint punto)
{
	std::stringstream stream;
	stream << "(" << punto.x() << ", " << punto.y() << ")";
	return stream.str();
}

std::string imprqp(dir_t dir)
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

}
