#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <cstring>
#include "adresse.h"
#include "exceptioncontact.h"
#include "utils.h"

class Contact{
    private:
        static const int MAX_NOM=30;
        static const int MAX_PRENOM=30;
        unsigned long id;
        std::string nom;
        std::string prenom;
        bool sexe_f;
        mutable Infos::Adresse adresse;
    public:
        Contact(int id,std::string nom,std::string prenom,Infos::Adresse adresse,bool sexe_f);
        virtual ~Contact(){};
        unsigned long getId() const;
        std::string getId_s() const;
        void setId(unsigned long value);
        std::string getNom() const;
        void setNom(const std::string &value);
        std::string getPrenom() const;
        void setPrenom(const std::string &value);
        bool getSexe_f() const;
        void setSexe_f(bool value);
        virtual std::string to_str() =0;
         Infos::Adresse& getAdresse() const;
        void setAdresse(const Infos::Adresse &value);
        std::string getTitre() const;

};

#endif // CONTACT_H
