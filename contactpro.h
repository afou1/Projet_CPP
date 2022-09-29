#ifndef CONTACTPRO_H
#define CONTACTPRO_H


#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include "adresse.h"
#include "contact.h"
#include "utils.h"

#define MAX_STR_PRO 128

class ContactPro : public Contact{

    public:
        enum StatutJuridique{SARL,SA,SAS,EURL};
        ContactPro(int,std::string,std::string,bool,Infos::Adresse,std::string,StatutJuridique,std::string);
        std::string getNom_entreprise() const;
        void setNom_entreprise(const std::string &value);

        StatutJuridique getStatus() const;
        void setStatus(const StatutJuridique &value);

        std::string getMail() const;
        void setMail(const std::string &value);

        std::string to_str() override;

        friend std::ostream& operator<<(std::ostream& os, ContactPro& s)
            {
                os<<s.getId()<<'\n';
                os<<s.getNom()<<'\n';
                os<<s.getPrenom()<<'\n';
                os<<s.getSexe_f()<<'\n';
                os<<s.getAdresse().getNumero()<<'\n';
                os<<s.getAdresse().getRue()<<'\n';
                os<<s.getAdresse().getCode_postal()<<'\n';
                os<<s.getAdresse().getVille()<<'\n';

                os<<s.getStatus()<<'\n';
                os<<s.getNom_entreprise()<<'\n';
                return os;
            }

        // Extraction operator
        friend std::istream& operator>>(std::istream& os, ContactPro& s)
        {
            // read in individual members of s
            int tempv;
            bool tempb;
            os>>tempv;
            int max=1024;
            char temp_cs[max];
            s.setId(tempv);
            os>>std::ws;
            os.getline(temp_cs,max,'\n');

            s.setNom(std::string(temp_cs));
            os>>std::ws;
            os.getline(temp_cs,max,'\n');
            s.setPrenom(std::string(temp_cs));
            os>>tempb;
            s.setSexe_f(tempb);
            Infos::Adresse tempa;

            os>>tempv;
            tempa.setNumero(tempv);
            os>>std::ws;
            os.getline(temp_cs,max,'\n');
            tempa.setRue(std::string(temp_cs));
            os>>tempv;
            tempa.setCode_postal(tempv);
            os>>std::ws;
            os.getline(temp_cs,max,'\n');
            tempa.setVille(std::string(temp_cs));
            s.setAdresse(tempa);

            os>>tempv;
            StatutJuridique tempst=static_cast<StatutJuridique>(tempv);
            s.setStatus(tempst);
            os>>std::ws;
            os.getline(temp_cs,max,'\n');
            s.setNom_entreprise(std::string(temp_cs));
            os>>std::ws;
            return os;
        }

private:
        static const std::regex regex_mail;
        std::string nom_entreprise;
        StatutJuridique status;
        std::string mail;
};

#endif // CONTACTPRO_H
