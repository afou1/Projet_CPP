#ifndef ADRESSE_H
#define ADRESSE_H

#include <iostream>
#include "exceptionadresse.h"
#include <sstream>
#include <iomanip>
#include <regex>
#include "utils.h"

#define MAX_STR 256
namespace Infos {
    class Adresse{
        private:
            unsigned int numero;
            std::string rue;
            std::string complement;
            unsigned int code_postal;
            std::string ville;
        public:
            Adresse(const Adresse& a);
            Adresse(int vnum=12,std::string vrue="rue",int vcode=1,std::string vville="ville"):
                numero(vnum),rue(vrue),code_postal(vcode),ville(vville){}
            unsigned int getNumero() const;
            void setNumero(unsigned int value);
            std::string getRue() const;
            void setRue(const std::string &value);
            std::string getComplement() const;
            void setComplement(const std::string &value);
            unsigned int getCode_postal() const;
            void setCode_postal(unsigned int value);
            std::string getVille() const;
            void setVille(const std::string &value);
            unsigned int getDepartement() const;
            Adresse& operator=(const Adresse& a);
            std::string to_str() const;

    };
}


#endif // ADRESSE_H
