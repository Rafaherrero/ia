#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <exception>

namespace exception{

    class out_of_range:public std::exception
    {
    private:
        const char* what_;

    public:
        out_of_range(void);
        out_of_range(const char*);

        const char* what() const throw(){return what_;}
    };

    class mem_error:public std::exception
    {
    private:
        const char* what_;

    public:
        mem_error(void);
        mem_error(const char*);

        const char* what() const throw(){return what_;}
    };

	class not_reachable:public std::exception
	{
	private:
		const char* what_;

	public:
		not_reachable(void);
		not_reachable(const char*);

		const char* what() const throw(){return what_;}
	};

	class overlapping:public std::exception
	{
	private:
		const char* what_;

	public:
		overlapping(void);
		overlapping(const char*);

		const char* what() const throw(){return what_;}
	};
}

#endif // EXCEPTIONS_H
