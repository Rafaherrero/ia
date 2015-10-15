#ifndef ALEATORIO_H
#define ALEATORIO_H

#include <ctime>
#include <unistd.h>
#include <cstdlib>

class aleatorio
{
private:
	static unsigned long mix(unsigned long a, unsigned long b, unsigned long c);
public:
	static unsigned long random(void);
	aleatorio();
};

#endif // ALEATORIO_H
