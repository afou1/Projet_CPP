#include "date.h"

using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;

unsigned short Date::getAnnee() const
{
    return annee;
}

void Date::setAnnee(unsigned short value)
{
    time_t temp= time(nullptr);
    tm *const pTInfo = std::localtime(&temp);
    int annee_actuelle=1900 + pTInfo->tm_year;
    if(value>=1900 && value<=annee_actuelle){
        annee = value;
    }else{
        throw ExceptionContact("Valeur annee invalide");
    }
}

unsigned short Date::getMois() const
{
    return mois;
}

void Date::setMois(unsigned short value)
{
    if(value>=1 && value<=12){
        mois = value;
    }else{
        throw ExceptionContact("Valeur mois invalide");
    }
}

unsigned short Date::getJour() const
{
    return jour;
}

void Date::setJour(unsigned short value)
{
    if(annee>=1900 && mois>=1){
        time_t temp= time(nullptr);
        tm * date = std::localtime(&temp);
        date->tm_year=getAnnee()-1900;
        date->tm_mon=getMois()-1;
        date->tm_mday=value;
        time_t res = mktime(date);
        if((date->tm_year==(getAnnee()-1900))&&
                (date->tm_mon==(getMois()-1))&&
                (date->tm_mday==value)){
            jour = value;
        }else{
           throw ExceptionContact("Valeur jour invalide");
        }
    }else{
        throw ExceptionContact("Valeur annee ou mois vide");
    }

}

Date &Date::operator=(const Date &d)
{
    this->setAnnee(d.getAnnee());
    this->setMois(d.getMois());
    this->setJour(d.getJour());
    return *this;
}

string Date::to_str() const
{
     stringstream resultat;
     resultat<<setfill('0') << setw(2) << getJour() <<"/";
     resultat<<setfill('0') << setw(2) << getMois() <<"/";
     resultat << getAnnee();
     return resultat.str();
}

bool Date::is_anniversaire() const
{
    time_t temp= time(nullptr);
    tm *const pTInfo = std::localtime(&temp);
    int mois_actuel=pTInfo->tm_mon+1;
    int jour_actuel=pTInfo->tm_mday;
    if(
       mois_actuel==getMois() &&
       jour_actuel==getJour()){
        return true;
    }else{
        return false;
    }
}

int Date::age() const
{
    time_t temp= time(nullptr);
    tm *const pTInfo = std::localtime(&temp);
    int annee_actuelle=1900 + pTInfo->tm_year;
    return annee_actuelle-getAnnee();
}

Date::Date(const Date &d){
    this->setAnnee(d.getAnnee());
    this->setMois(d.getMois());
    this->setJour(d.getJour());
}
