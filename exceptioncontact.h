#ifndef EXCEPTIONCONTACT_H
#define EXCEPTIONCONTACT_H

#include <exception>
#include <string>


namespace ExceptionsAnnuaire {
    class ExceptionContact : public std::exception{
        private:
            std::string cause;
        public:
            ExceptionContact(std::string c) throw(): cause(c){};
            ~ExceptionContact() throw(){};
            const char* what() const throw(){return cause.c_str();}
    };
}



#endif // EXCEPTIONCONTACT_H
