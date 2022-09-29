#ifndef EXCEPTIONADRESSE_H
#define EXCEPTIONADRESSE_H

#include <exception>
#include <string>

namespace ExceptionsAnnuaire {
    class ExceptionAdresse : public std::exception{
        private:
            std::string cause;
        public:
            ExceptionAdresse(std::string c) throw(): cause(c){};
            ~ExceptionAdresse() throw(){};
            const char* what() const throw(){return cause.c_str();}
    };
}


#endif // EXCEPTIONADRESSE_H
