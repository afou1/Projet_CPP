#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "exceptioncontact.h"


namespace Infos {
    class Date{
        private:
            unsigned short annee;
            unsigned short mois;
            unsigned short jour;
        public:
            Date(int vanne=1995,int vmois=3,int vjour=5):annee(vanne),mois(vmois),jour(vjour){}
            Date(const Date &d);
            unsigned short getAnnee() const;
            void setAnnee(unsigned short value);
            unsigned short getMois() const;
            void setMois(unsigned short value);
            unsigned short getJour() const;
            void setJour(unsigned short value);
            Date& operator=(const Date& d);
            std::string to_str() const;

            bool is_anniversaire() const;
            int age() const;
    };
}



#endif // DATE_H
