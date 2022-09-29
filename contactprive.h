#ifndef CONTACTPRIVE_H
#define CONTACTPRIVE_H

#include "contact.h"
#include "adresse.h"
#include "date.h"
#include <sstream>
#include <iomanip>
#include <string>
class ContactPrive : public Contact{
    private:
        mutable Infos::Date date_naissance;
    public:
        ContactPrive(int,std::string,std::string,bool,Infos::Adresse,Infos::Date);
        Infos::Date& getDate_naissance() const;
        void setDate_naissance(const Infos::Date &value);
        std::string to_str() override;

        friend std::ostream& operator<<(std::ostream& os, const ContactPrive& s)
            {
                os<<s.getId()<<'\n';
                os<<s.getNom().c_str()<<'\n';
                os<<s.getPrenom()<<'\n';
                os<<s.getSexe_f()<<'\n';
                os<<s.getAdresse().getNumero()<<'\n';
                os<<s.getAdresse().getRue()<<'\n';
                os<<s.getAdresse().getCode_postal()<<'\n';
                os<<s.getAdresse().getVille()<<'\n';

                os<<s.getDate_naissance().getAnnee()<<'\n';
                os<<s.getDate_naissance().getMois()<<'\n';
                os<<s.getDate_naissance().getJour()<<'\n';
                return os;
            }

        // Extraction operator
        friend std::istream& operator>>(std::istream& os, ContactPrive& s)
        {
            // read in individual members of s
            int tempv;
            bool tempb;
            int max=1024;
            char temp_cs[max];
            os>>tempv;
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
            Infos::Date tempdate;
            os>>tempv;
            tempdate.setAnnee(tempv);
            os>>tempv;
            tempdate.setMois(tempv);
            os>>tempv;
            tempdate.setJour(tempv);
            s.setDate_naissance(tempdate);
            os>>std::ws;
            return os;
        }
};

#endif // CONTACTPRIVE_H
