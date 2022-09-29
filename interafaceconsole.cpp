#include "interafaceconsole.h"

using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;

const string red("\033[0;31m");
const string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const string underline("\033[4m");
const string reset("\033[0m");

InterafaceConsole::InterafaceConsole(){
    sortir=false;
}
void InterafaceConsole::afficherMenu() {
    cout<<endl<<"=========================================="<<endl;
    cout<<"    Menu principal"<<endl;
    cout<<"=========================================="<<endl;
    cout.setf(ios::right, ios::adjustfield);
    int w=30;
    cout <<left<<setfill(' ') << setw(w)<<"    __________________________"<<right<<setfill('_') << setw(w)<<"_"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 1- Afficher annuaire"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 2- Recherche"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 3- Ajouteur contact"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 4- Modifier contact"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 5- Supprimer contact"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 6- Enregistrer annuaire"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 7- Charger annuaire"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 8- Sortir"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    |_________________________"<<right<<setfill('_') << setw(w)<<"_|"<<endl;
}

void InterafaceConsole::optionAfficher() {
    list<Contact*> all_contacts= annuaire.getAll();
    if(all_contacts.size()>0){
        for (auto c:all_contacts){
            cout<<c->to_str()<<endl;
        }
    }else{
        cout<<endl<<yellow<<"Annuaire vide"<<reset<<endl;
    }
}

void InterafaceConsole::optionRecherche() {
    afficherMenuRecherche();
    lireChoixRecherche();

}

void InterafaceConsole::optionAjouter(){
    int choix=-1;
    cout<<endl<<"1- Professionnel"<<endl;
    cout<<"2- Privé"<<endl<<endl;
    while(choix!=1 && choix!=2){
        choix=lireInt("Votre choix",true);
        switch (choix) {
            case 1:
                ajouterPro();
            break;
            case 2:
                ajouterPrive();
            break;
            default:
                cout<<red<<"Erreur: choix invalide"<<reset<<endl;
            break;
        }
    }

}

void InterafaceConsole::optionModifier() {
    Contact *p=nullptr;
    int id=-1;
    while(p==nullptr){
        id=lireInt("Numero du contact à modifier",true);
        p=annuaire.fromId(id);
        if(p==nullptr){
            cout<<red<<"Numero inexistant dans l'annuaire"<<reset<<endl;
        }
    }
    ContactPrive* ptr_prive=dynamic_cast<ContactPrive*>(p);
    if(ptr_prive!=nullptr){
        modifierPrive(ptr_prive);
    }else{
        ContactPro* ptr_pro=dynamic_cast<ContactPro*>(p);
        if(ptr_pro!=nullptr){
            //on devrait tjr rentrer dans cette condition
            //Je la met dans le cas ou on ajoute un troisieme type de contact dans le future
            modifierPro(ptr_pro);
        }
    }
}
void InterafaceConsole::optionSupprimer() {
    int id;
    id=lireInt("Numero du contact à supprimer",true);
    if(annuaire.supprimer(id)){
        cout<<green<<"suppression executée"<<reset<<endl;
    }else{
        cout<<red<<"Numero inexistant, aucune suppression executée"<<reset<<endl;
    }
}

void InterafaceConsole::optionsEnregistrer() {
    try {
        int nb_prives=annuaire.save_prive();
        if(nb_prives>0){
            cout<<green<<nb_prives<<" contacts privés sauvegardés dans privates.pro"<<reset<<endl;
        }else{
            cout<<yellow<<"Aucun contact privé sauvegardé dans privates.pro"<<reset<<endl;
        }
    }  catch (const ExceptionContact &e) {
        cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
    }
    try {
        int nb_pros=annuaire.save_pro();
        if(nb_pros>0){
            cout<<green<<nb_pros<<" contacts professionnels sauvegardés dans pros.pro"<<reset<<endl;
        }else{
            cout<<yellow<<"Aucun contact professionnel sauvegardé dans pros.pro"<<reset<<endl;
        }
    }  catch (const ExceptionContact &e) {
        cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
    }
}

void InterafaceConsole::optionCharger(){
    try {
        int nb_prives=annuaire.load_prive();
        if(nb_prives>0){
            cout<<green<<nb_prives<<" contacts privés chargés de privates.pro"<<reset<<endl;
        }else{
            cout<<yellow<<"Aucun contact privé chargé de privates.pro"<<reset<<endl;
        }
    }  catch (const ExceptionContact &e) {
        cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
    }
    try {
        int nb_pros=annuaire.load_pro();
        if(nb_pros>0){
            cout<<green<<nb_pros<<" contacts professionnels chargés de pros.pro"<<reset<<endl;
        }else{
            cout<<yellow<<"Aucun contact professionnel chargé de pros.pro"<<reset<<endl;
        }
    }  catch (const ExceptionContact &e) {
        cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
    }
}

void InterafaceConsole ::optionSortir() {
    this->sortir=true;
}

void InterafaceConsole::afficherMenuRecherche() {
    cout<<endl<<"=========================================="<<endl;
    cout<<"    Menu recherche"<<endl;
    cout<<"=========================================="<<endl;
    cout.setf(ios::right, ios::adjustfield);
    int w=30;
    cout <<left<<setfill(' ') << setw(w)<<"    __________________________"<<right<<setfill('_') << setw(w)<<"_"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 1- Par numero"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 2- Par nom"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 3- Par code postal"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 4- Par departement"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 5- Par ville"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    |_________________________"<<right<<setfill('_') << setw(w)<<"_|"<<endl;
}

void InterafaceConsole::lireChoixRecherche() {
    int choix=-1;
    while(choix<1 || choix>5){
        choix=lireInt("Votre choix",true);
        switch (choix) {
            case 1: {
                int id;
                id=lireInt("Identifiant recherché",true);
                Contact* c=annuaire.fromId(id);
                if(c!=nullptr){
                    cout<<c->to_str()<<endl;
                }else{
                    cout<<red<<"Aucun contact avec l'identifiant entré"<<reset<<endl;
                }
                break;
            }
            case 2: {
                cout<<endl<<"Nom recherché: ";
                string nom;
                cin.clear();
                fflush(stdin);
                getline(cin>>ws,nom);
                nom=trim(nom);
                list<Contact*> list_c=annuaire.fromNom(nom);
                if(list_c.size()>0){
                    for (auto c:list_c){
                        cout<<c->to_str()<<endl;
                    }
                }else{
                    cout<<red<<"Aucun contact avec le nom entré"<<reset<<endl;
                }
                break;
            }
            case 3: {
                unsigned int code_p;
                code_p=lireInt("Code postal recherché",true);
                list<Contact*> list_d=annuaire.fromCodePostal(code_p);
                if(list_d.size()>0){
                    for (auto c:list_d){
                        cout<<c->to_str()<<endl;
                    }
                }else{
                    cout<<red<<"Aucun contact avec le code postal entré"<<reset<<endl;
                }
                break;
            }
            case 4: {
                unsigned int code_dp;
                code_dp=lireInt("Departement recherché",true);
                list<Contact*> list_e=annuaire.fromDepartement(code_dp);
                if(list_e.size()>0){
                    for (auto c:list_e){
                        cout<<c->to_str()<<endl;
                    }
                }else{
                    cout<<red<<"Aucun contact avec le departement entré"<<reset<<endl;
                }
            break;
            }
            case 5: {
                cout<<endl<<"Ville recherché: ";
                string ville;
                cin.clear();
                fflush(stdin);
                getline(cin>>ws,ville);
                ville=trim(ville);
                for(auto &c:ville) c=toupper(c);
                list<Contact*> list_f=annuaire.fromVille(ville);
                if(list_f.size()>0){
                    for (auto c:list_f){
                        cout<<c->to_str()<<endl;
                    }
                }else{
                    cout<<red<<"Aucun contact avec la ville entrée"<<reset<<endl;
                }
            break;
            }
            default:
                cout<<red<<"Erreur: Choix invalide"<<reset<<endl;
            break;
        }
    }
}

void InterafaceConsole::ajouterPro(){
    int id=annuaire.getSize()+1;
    ContactPro* contact_pro=new ContactPro(id,"nom","prenom",true,Adresse(),
                                           "entreprise",ContactPro::StatutJuridique::EURL,"info@ent.fr");
    lireNom(contact_pro);
    lirePrenom(contact_pro);
    lireSexe(contact_pro);
    lireAdresse(contact_pro);
    lireNomEntreprise(contact_pro);
    lireStatutJuridique(contact_pro);
    lireMail(contact_pro);
    annuaire.ajouter(contact_pro);
    cout<<green<<"Contact pro num: "<<contact_pro->getId_s()<<" ajouté"<<reset<<endl;
}

void InterafaceConsole::ajouterPrive(){
    int id=annuaire.getSize()+1;
    ContactPrive* contact_prive=new ContactPrive(id,"nom","prenom",true,Adresse(),Date());
    lireNom(contact_prive);
    lirePrenom(contact_prive);
    lireSexe(contact_prive);
    lireAdresse(contact_prive);
    lireDate(contact_prive);
    annuaire.ajouter(contact_prive);
    cout<<green<<"Contact privé num: "<<contact_prive->getId_s()<<" ajouté"<<reset<<endl;
}

void InterafaceConsole::modifierPro(ContactPro* p){
    afficherModifsPro();
    int choix=-1;
    while(choix<1 || choix>7){
        choix=lireInt("Attribut à modifier",true);
        if(choix<1 || choix>7)
            cout<<red<<"Erreur: choix invalid"<<reset<<endl;
    }
    switch (choix) {
        case 1:
            lireNom(p);
        break;
        case 2:
            lirePrenom(p);
        break;
        case 3:
            lireSexe(p);
        break;
        case 4:
            lireAdresse(p);
        break;
        case 5:
            lireNomEntreprise(p);
        break;
        case 6:
            lireStatutJuridique(p);
        break;
        default:
            lireMail(p);
        break;
    }
}

void InterafaceConsole::modifierPrive(ContactPrive* p){
    afficherModifsPrive();
    int choix=-1;
    while(choix<1 || choix>5){
        choix=lireInt("Attribut à modifier",true);
        if(choix<1 || choix>5)
            cout<<red<<"Erreur: choix invalid"<<reset<<endl;
    }
    switch (choix) {
        case 1:
            lireNom(p);
        break;
        case 2:
            lirePrenom(p);
        break;
        case 3:
            lireSexe(p);
        break;
        case 4:
            lireAdresse(p);
        break;
        default:
            lireDate(p);
        break;
    }
}

void InterafaceConsole::afficherModifsPro(){
    cout<<endl<<"=========================================="<<endl;
    cout<<"    Menu modification contact pro"<<endl;
    cout<<"=========================================="<<endl;
    cout.setf(ios::right, ios::adjustfield);
    int w=30;
    cout <<left<<setfill(' ') << setw(w)<<"    __________________________"<<right<<setfill('_') << setw(w)<<"_"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 1- Nom"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 2- Prenom"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 3- Sexe"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 4- Adresse"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 5- Nom entreprise"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 6- Statut juridique"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 7- Adresse mail"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    |_________________________"<<right<<setfill('_') << setw(w)<<"_|"<<endl;
}

void InterafaceConsole::afficherModifsPrive(){
    cout<<endl<<"=========================================="<<endl;
    cout<<"    Menu modification contact prive"<<endl;
    cout<<"=========================================="<<endl;
    cout.setf(ios::right, ios::adjustfield);
    int w=30;
    cout <<left<<setfill(' ') << setw(w)<<"    __________________________"<<right<<setfill('_') << setw(w)<<"_"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 1- Nom"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 2- Prenom"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 3- Sexe"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 4- Adresse"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    | 5- Date de naissance"<<right<<setfill(' ') << setw(w)<<"|"<<endl;
    cout <<left<<setfill(' ') << setw(w)<<"    |_________________________"<<right<<setfill('_') << setw(w)<<"_|"<<endl;
}

void InterafaceConsole::lireNom(Contact *p)
{
    bool invalid=true;
    while(invalid){
        cout<<"Nom: ";
        string input_nom;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,input_nom);
        input_nom=trim(input_nom);
        try{
            p->setNom(input_nom);
            invalid=false;
        }catch(const ExceptionContact &e){
            cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
            continue;
        }
    }
}

void InterafaceConsole::lirePrenom(Contact *p) {
    bool invalid=true;
    while(invalid){
        cout<<"Prenom: ";
        string input_prenom;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,input_prenom);
        input_prenom=trim(input_prenom);
        try{
            p->setPrenom(input_prenom);
            invalid=false;
        }catch(const ExceptionContact &e){
            cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
            continue;
        }
    }
}

void InterafaceConsole::lireSexe(Contact *p) {
    cout<<"Sexe (F/M): ";
    string c;
    cin.clear();
    fflush(stdin);
    getline(cin>>ws,c);
    c=trim(c);
    c[0]=toupper(c[0]);
    while(c.size()!=1 || (c!="F" && c!="M")){
        cout<<red<<"Erreur: valeure invalide"<<reset<<endl;
        cout<<"Sexe (F/M): ";
        cin.clear();
        getline(cin>>ws,c);
        c=trim(c);
        c[0]=toupper(c[0]);
    }
    p->setSexe_f(c=="F");
}

void InterafaceConsole::lireAdresse(Contact *p) {
    //TODO refactor
    cout<<underline<<"Adresse:"<<reset<<endl<<endl;
    string tab="    ";
    bool invalid=true;
    while(invalid){
        int num;
        num=lireInt(tab+"Numero",true);
        try {
            p->getAdresse().setNumero(num);
            invalid=false;
        }  catch (const ExceptionAdresse &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        cout<<tab+"Rue: ";
        string rue;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,rue);
        rue=trim(rue);
        try {
            p->getAdresse().setRue(rue);
            invalid=false;
        }  catch (const ExceptionAdresse &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        cout<<tab+"Complement: ";
        string cmp;
        cin.clear();
        fflush(stdin);
        getline(cin,cmp);
        cmp=trim(cmp);
        try {
            p->getAdresse().setComplement(cmp);
            invalid=false;
        }  catch (const ExceptionAdresse &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        int code;
        code=lireInt(tab+"Code postal",true);
        try {
            p->getAdresse().setCode_postal(code);
            invalid=false;
        }  catch (const ExceptionAdresse &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        cout<<tab+"Ville: ";
        string ville;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,ville);
        ville=trim(ville);
        try {
            p->getAdresse().setVille(ville);
            invalid=false;
        }  catch (const ExceptionAdresse &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
}

void InterafaceConsole::lireNomEntreprise(ContactPro *p)
{
    bool invalid=true;
    while(invalid){
        cout<<"Nom Entreprise: ";
        string nom_e;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,nom_e);
        nom_e=trim(nom_e);
        try {
            p->setNom_entreprise(nom_e);
            invalid=false;
        }  catch (const ExceptionContact &e) {
            cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
        }
    }
}

void InterafaceConsole::lireStatutJuridique(ContactPro *p) {
    string statut;
    bool invalid=true;
    while(invalid){
        cout<<"Statut Juridique: ";
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,statut);
        statut=trim(statut);
        for(auto &c:statut) c=toupper(c);
        if(statut=="SARL"){
            p->setStatus(ContactPro::StatutJuridique::SARL);
            invalid=false;
        }else if(statut=="SA"){
            p->setStatus(ContactPro::StatutJuridique::SA);
            invalid=false;
        }else if(statut=="SAS"){
            p->setStatus(ContactPro::StatutJuridique::SAS);
            invalid=false;
        }else if(statut=="EURL"){
            p->setStatus(ContactPro::StatutJuridique::EURL);
            invalid=false;
        }else{
            cout<<red<<"Erreur: valeur invalide"<<reset<<endl;
        }
    }
}

void InterafaceConsole::lireMail(ContactPro *p) {
    bool invalid=true;
    while(invalid){
        cout<<"Email: ";
        string mail;
        cin.clear();
        fflush(stdin);
        getline(cin>>ws,mail);
        mail=trim(mail);
        try {
             p->setMail(mail);
             invalid=false;
        }  catch (const ExceptionContact &e) {
            cout<<red<<"Erreur: "<<e.what()<<reset<<endl;
        }
    }
}

void InterafaceConsole::lireDate(ContactPrive *p) {
    cout<<underline<<"Date de naissance:"<<reset<<endl<<endl;
    string tab="    ";
    bool invalid=true;
    while(invalid){
        int annee;
        annee=lireInt(tab+"Annee",true);
        try {
            p->getDate_naissance().setAnnee(annee);
            invalid=false;
        }  catch (const ExceptionContact &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        int mois;
        mois=lireInt(tab+"Mois",true);
        try {
            p->getDate_naissance().setMois(mois);
            invalid=false;
        }  catch (const ExceptionContact &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
    invalid=true;
    while(invalid){
        int jour;
        jour=lireInt(tab+"Jour",true);
        try {
            p->getDate_naissance().setJour(jour);
            invalid=false;
        }  catch (const ExceptionContact &e) {
            cout<<red<<tab+"Erreur: "<<e.what()<<reset<<endl;
        }
    }
}

int InterafaceConsole::lireInt(string message, bool positive){

    bool invalid=true;
    int result;
    while(invalid){
        cout<<message<<": ";
        string ligne;
        cin.clear();
        fflush(stdin);
        fflush(stdin);
        getline(cin>>ws,ligne);
        ligne=trim(ligne);
        try{
            result=stol(ligne);
            if(positive && result<0){
                cout<<red<<"Erreur: impossible d'avoir une valeur negative pour ce champ"<<reset<<endl;
                continue;
            }else{
                return result;
            }

        } catch (...) {
            cout<<red<<"Erreur: valeur incomprise"<<reset<<endl;
        }
    }
    return -1;
}

void InterafaceConsole::executer(){
    while(!sortir){
        afficherMenu();
        lireChoixMenu();
    }
}

void InterafaceConsole::lireChoixMenu(){
    int choix=-1;
    while(choix<1 || choix>8){
        cout<<endl<<endl;
        choix=lireInt("Votre choix",true);
        switch (choix) {
        case 1:
            optionAfficher();
            break;
        case 2:
            optionRecherche();
            break;
        case 3:
            optionAjouter();
            break;
        case 4:
            optionModifier();
            break;
        case 5:
            optionSupprimer();
            break;
        case 6:
            optionsEnregistrer();
            break;
        case 7:
            optionCharger();
            //cout<<"Pas eu le temps de finir cette partie"<<endl;
            break;
        case 8:
            optionSortir();
            break;
        default:
            cout<<red<<"Erreur: valeur choix invalide"<<reset<<endl;
        }
    }
}
