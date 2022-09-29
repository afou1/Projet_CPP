#ifndef INTERAFACECONSOLE_H
#define INTERAFACECONSOLE_H

#include <iostream>
#include <iomanip>
#include <list>
#include "annuaire.h"
#include "contactprive.h"
#include "contactpro.h"
#include "adresse.h"
#include "utils.h"

class InterafaceConsole{
    private:
        Annuaire annuaire;
        bool sortir;
    public:
        InterafaceConsole();
        void afficherMenu();
        void lireChoixMenu();
        void optionAfficher();
        void optionRecherche();
        void optionAjouter();
        void optionModifier();
        void optionSupprimer();
        void optionsEnregistrer();
        void optionCharger();
        void optionSortir();

        void afficherMenuRecherche();
        void lireChoixRecherche();

        void ajouterPro();
        void ajouterPrive();

        void modifierPro(ContactPro*);
        void modifierPrive(ContactPrive*);

        void afficherModifsPro();
        void afficherModifsPrive();

        void lireNom(Contact* p);
        void lirePrenom(Contact* p);
        void lireSexe(Contact* p);
        void lireAdresse(Contact* p);
        void lireNomEntreprise(ContactPro* p);
        void lireStatutJuridique(ContactPro* p);
        void lireMail(ContactPro* p);
        void lireDate(ContactPrive* p);

        int lireInt(std::string message,bool positive=false);

        void executer();
};

#endif // INTERAFACECONSOLE_H
