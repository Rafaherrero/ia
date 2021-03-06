#include "exceptions.h"

namespace exception{
    /*
    nombre_de_error::nombre_de_error(void):
        what_("Mensaje por defecto del error")
    {}

	nombre_de_error::nombre_de_error(const char* what_arg):
        what_(what_arg)
    {}
    */
    out_of_range::out_of_range(void):
        what_("Out of range error")
    {}

	out_of_range::out_of_range(const char* what_arg):
        what_(what_arg)
    {}

    mem_error::mem_error(void):
        what_("Memory error")
    {}

	mem_error::mem_error(const char* what_arg):
        what_(what_arg)
    {}

	not_reachable::not_reachable(void):
		what_("Not reachable error")
	{}

	not_reachable::not_reachable(const char* what_arg):
		what_(what_arg)
	{}

	overlapping::overlapping(void):
		what_("Overlapping error")
	{}

	overlapping::overlapping(const char* what_arg):
		what_(what_arg)
	{}
}
