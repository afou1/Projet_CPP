#ifndef ANNUAIRE_H
#define ANNUAIRE_H

#include <map>
#include <list>
#include <fstream>
#include "contact.h"
#include "contactprive.h"
#include "contactpro.h"
#include "adresse.h"
class Annuaire{
    private:
        std::map<unsigned long,Contact*> map_annuaire;
    public:
        Annuaire();
        ~Annuaire();
        Contact* fromId(unsigned long id) const;
        std::list<Contact*> fromNom(const std::string nom) const;
        std::list<Contact*> fromCodePostal(unsigned int code_postal) const;
        std::list<Contact*> fromDepartement(unsigned int code_departement) const;
        std::list<Contact*> fromVille(const std::string ville) const;
        std::list<Contact*> getAll() const;
        bool ajouter(Contact*);
        bool supprimer(unsigned long id);
        int getSize() const;
        int save_prive() const;
        int save_pro() const;
        int load_prive();
        int load_pro();
};

#endif // ANNUAIRE_H
