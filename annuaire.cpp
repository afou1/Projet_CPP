#include "annuaire.h"

using namespace std;

Annuaire::Annuaire()
{

}

Annuaire::~Annuaire(){
    for(auto c:map_annuaire){
        if(c.second!=nullptr){
            delete c.second;
        }
    }
}

Contact* Annuaire::fromId(unsigned long id) const{
    try{
        return map_annuaire.at(id);
    }catch (...) {
        return nullptr;
    }
}

list<Contact *> Annuaire::fromNom(const std::string nom) const{
    list<Contact*> resultat;
    string v=nom;
    for(auto & c: v) c = toupper(c);
    for(auto c:map_annuaire){
        if(c.second->getNom()==v){
            resultat.push_back(c.second);
        }
    }
    return resultat;
}

list<Contact *> Annuaire::fromCodePostal(unsigned int code_postal) const{
    list<Contact*> resultat;
    for(auto c:map_annuaire){
        if(c.second->getAdresse().getCode_postal()==code_postal){
            resultat.push_back(c.second);
        }
    }
    return resultat;
}

list<Contact *> Annuaire::fromDepartement(unsigned int code_departement) const{
    list<Contact*> resultat;
    for(auto c:map_annuaire){
            if(c.second->getAdresse().getDepartement()==code_departement){
                resultat.push_back(c.second);
            }
    }
    return resultat;
}

list<Contact *> Annuaire::fromVille(const string ville) const{
    list<Contact*> resultat;
    string v=ville;
    for(auto & c: v) c = toupper(c);
    for(auto c:map_annuaire){
            if(c.second->getAdresse().getVille()==v){
                resultat.push_back(c.second);
            }
    }
    return resultat;
}

std::list<Contact *> Annuaire::getAll() const
{
    list<Contact*> resultat;
    for(auto c:map_annuaire){
        resultat.push_back(c.second);
    }
    return resultat;
}

bool Annuaire::ajouter(Contact *c){
    try{
        map_annuaire[c->getId()]=c;
        return true;
    } catch (...) {
        return false;
    }
}

bool Annuaire::supprimer(unsigned long id){
    try{
        if(map_annuaire.count(id)>0){
            Contact* ptr_c=map_annuaire[id];
            if(ptr_c!=nullptr) delete ptr_c;
            map_annuaire.erase(id);
            return true;
        }else{
            return false;
        }
    } catch (...) {
        return false;
    }
}

int Annuaire::getSize() const{
    return map_annuaire.size();
}

int Annuaire::save_prive() const
{
    list<ContactPrive*> list_current;
    for(auto c:map_annuaire){
        ContactPrive* ptr_temp=dynamic_cast<ContactPrive*>(c.second);
        if(ptr_temp!=nullptr){
            list_current.push_back(ptr_temp);
        }
    }
    if(list_current.size()>0){
        try {
            ofstream fichier_prive("privates.dat",ios::out);
            for(ContactPrive* ptr_obj:list_current){
                fichier_prive<<*ptr_obj;
            }
            fichier_prive.close();
        }  catch (...) {
            throw ExceptionsAnnuaire::ExceptionContact("Erreur ecriture du fichier privates.dat");
        }
    }
    return list_current.size();
}

int Annuaire::save_pro() const
{
    list<ContactPro*> list_current;
    for(auto c:map_annuaire){
        ContactPro* ptr_temp=dynamic_cast<ContactPro*>(c.second);
        if(ptr_temp!=nullptr){
            list_current.push_back(ptr_temp);
        }
    }
    if(list_current.size()>0){
        try {
            ofstream fichier_pro("pros.dat",ios::out);
            for(ContactPro* ptr_obj:list_current){
                fichier_pro<<*ptr_obj;
            }
            fichier_pro.close();
        }  catch (...) {
            throw ExceptionsAnnuaire::ExceptionContact("Erreur ecriture du fichier pros.dat");
        }
    }
    return list_current.size();
}

int Annuaire::load_prive(){
    int cmp=0;
    try {
        ifstream fichier_prive("privates.dat",ios::in);
        fichier_prive.seekg(0);
        while(!fichier_prive.eof()){
            ContactPrive* p_temp=new ContactPrive(0,"nom","prenom",false,Infos::Adresse(),Infos::Date());
            fichier_prive>>*p_temp;
            if(p_temp->getId()>0){
                supprimer(p_temp->getId());
                ajouter(p_temp);
                cmp++;
            }
        }
        fichier_prive.close();
    }  catch (...) {
        throw ExceptionsAnnuaire::ExceptionContact("Fichier privates.dat corrumpu ou inexistant");
    }
    return cmp;
}

int Annuaire::load_pro(){
    int cmp=0;
    try {
        ifstream fichier_pro("pros.dat",ios::in);
        fichier_pro.seekg(0);
        while(!fichier_pro.eof()){
            ContactPro* p_temp=new ContactPro(0,"nom","prenom",false,Infos::Adresse(),"entreprise",ContactPro::StatutJuridique::EURL,"info@gmail.fr");
            fichier_pro>>*p_temp;
            if(p_temp->getId()>0){
                supprimer(p_temp->getId());
                ajouter(p_temp);
                cmp++;
            }
        }
        fichier_pro.close();
    }  catch (...) {
        throw ExceptionsAnnuaire::ExceptionContact("Fichier pros.dat corrumpu ou inexistant");
    }
    return cmp;
}
