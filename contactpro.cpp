#include "contactpro.h"


using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;

const regex ContactPro::regex_mail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

ContactPro::ContactPro(int id,std::string nom,std::string prenom,bool sexe_f,Adresse adresse,
                       std::string nom_entreprise,StatutJuridique status,std::string adresse_mail):Contact(id,nom,prenom,adresse,sexe_f)
{
    setNom_entreprise(nom_entreprise);
    setStatus(status);
    setMail(adresse_mail);
}

std::string ContactPro::getNom_entreprise() const
{
    return nom_entreprise;
}

void ContactPro::setNom_entreprise(const std::string &value)
{
    regex r("[ _[:alnum:]]*");
    if(!regex_match(value,r)){
        throw ExceptionContact("Charctere invalide pour attribut nom de l'entreprise.");
    }else{
        string temp=value;
        for(auto &c:temp) c=toupper(c);
        nom_entreprise = trim(temp);
    }
}

ContactPro::StatutJuridique ContactPro::getStatus() const
{
    return status;
}

void ContactPro::setStatus(const StatutJuridique &value)
{
    status = value;
}


std::string ContactPro::getMail() const
{
    return mail;
}

void ContactPro::setMail(const std::string &value)
{
    if(regex_match(value.c_str(),regex_mail)){
        string temp=value;
        mail = trim(temp);
    }else{
        throw ExceptionContact("Adresse mail invalide");
    }
}

std::string ContactPro::to_str()
{
    stringstream resultat;
    int w=50;
    string line_adresse;
    stringstream s_adresse(getAdresse().to_str());
    resultat <<left<<setfill('_') << setw(w)<<"    Professionnel: "+getId_s()<<right<<setfill('_') << setw(1)<<"_"<<endl;
    resultat <<left<<setfill(' ') << setw(w)<<"    | Societe "+getNom_entreprise()<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    resultat <<left<<setfill(' ') << setw(w)<<"    | Contact: "+getTitre()+" "+getNom()+" "+getPrenom()<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    while(getline(s_adresse,line_adresse,'\n')){
          resultat <<left<<setfill(' ') << setw(w)<<"    | "+line_adresse<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    }
    resultat <<left<<setfill(' ') << setw(w)<<"    | "+getMail()<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    resultat <<left<<setfill('_') << setw(w)<<"    |_"<<right<<setfill('_') << setw(1)<<"|"<<endl;
    return resultat.str();
}


