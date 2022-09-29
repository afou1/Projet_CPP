#include "contact.h"

using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;
unsigned long Contact::getId() const{
    return id;
}

std::string Contact::getId_s() const
{
    stringstream resultat;
    resultat << setfill('0') << setw(5) << getId();
    return resultat.str();
}

void Contact::setId(unsigned long value){
    id = value;
}

std::string Contact::getNom() const{
    return nom;
}

void Contact::setNom(const std::string &value){
    regex r("[ [:alpha:]]*");
    if(!regex_match(value,r)){
        throw ExceptionContact("Charctere invalide pour attribut nom.");
    }
    else if(value.size()>0 && value.size()<=Contact::MAX_NOM)
    {
        nom = value;
        for(auto & c: nom) c = toupper(c);
        nom=trim(nom);
    }else{
        throw ExceptionContact("Taille du nom invalide.");
    }
}

std::string Contact::getPrenom() const{
    return prenom;
}

void Contact::setPrenom(const std::string &value){
    regex r("[ [:alpha:]]*");
    if(!regex_match(value,r)){
        throw ExceptionContact("Charctere invalide pour attribut prenom.");
    }
    else if(value.size()>0 && value.size()<=Contact::MAX_NOM){
        prenom = value;
        for(auto & c: prenom) c = tolower(c);
        prenom[0]=toupper(prenom[0]);
        prenom=trim(prenom);
    }else{
        throw ExceptionContact("Taille du prenom invalide.");
    }

}

bool Contact::getSexe_f() const{
    return sexe_f;
}

void Contact::setSexe_f(bool value){
    sexe_f = value;
}

Adresse& Contact::getAdresse() const{
    return adresse;
}

void Contact::setAdresse(const Adresse &value){
    adresse = value;
}

std::string Contact::getTitre() const
{
    if(sexe_f){
        return "Mme.";
    }else{
        return "M.";
    }
}



Contact::Contact(int id,std::string nom,std::string prenom, Adresse adresse,bool sexe_f){
    setId(id);
    setNom(nom);
    setPrenom(prenom);
    setAdresse(adresse);
    setSexe_f(sexe_f);
}
