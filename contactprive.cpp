#include "contactprive.h"


using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;

Date& ContactPrive::getDate_naissance() const
{
    return date_naissance;
}

void ContactPrive::setDate_naissance(const Date &value)
{
    date_naissance = value;
}

std::string ContactPrive::to_str()
{
    stringstream resultat;
    int w=50;
    string line_adresse;
    string ligne_age;
    stringstream s_adresse(getAdresse().to_str());
    resultat <<left<<setfill('_') << setw(w)<<"    Particulier: "+getId_s()<<right<<setfill('_') << setw(1)<<"_"<<endl;
    resultat <<left<<setfill(' ') << setw(w)<<"    | "+getTitre()+" "+getNom()+" "+getPrenom()<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    while(getline(s_adresse,line_adresse,'\n')){
          resultat <<left<<setfill(' ') << setw(w)<<"    | "+line_adresse<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    }
    resultat <<left<<setfill(' ') << setw(w)<<"    | "+getDate_naissance().to_str()<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    ligne_age="Age: "+to_string(getDate_naissance().age());
    if(getDate_naissance().is_anniversaire()){
        ligne_age+=" et Bon Anniversaire !";
    }
    resultat <<left<<setfill(' ') << setw(w)<<"    | "+ligne_age<<right<<setfill(' ') << setw(1)<<"|"<<endl;
    resultat <<left<<setfill('_') << setw(w)<<"    |_"<<right<<setfill('_') << setw(1)<<"|"<<endl;
    return resultat.str();
}

ContactPrive::ContactPrive(int id,std::string nom,std::string prenom,bool sexe_f,Adresse a,Date d):Contact(id,nom,prenom,a,sexe_f)
{
    setDate_naissance(d);
}
