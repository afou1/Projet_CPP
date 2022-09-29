#include "adresse.h"

using namespace std;
using namespace Infos;
using namespace ExceptionsAnnuaire;
unsigned int Adresse::getNumero() const
{
    return numero;
}

void Adresse::setNumero(unsigned int value)
{
    numero = value;
}

std::string Adresse::getRue() const
{
    return rue;
}

void Adresse::setRue(const std::string &value)
{
    string temp=value;
    for(auto &c:temp) c=tolower(c);
    temp[0]=toupper(temp[0]);
    rue = trim(temp);
}

std::string Adresse::getComplement() const
{
    return complement;
}

void Adresse::setComplement(const std::string &value)
{
    if(value.size()>0){
        string temp=value;
        for(auto &c:temp) c=tolower(c);
        temp[0]=toupper(temp[0]);
        complement = trim(temp);
    }else{
        complement="";
    }

}

unsigned int Adresse::getCode_postal() const
{
    return code_postal;
}

void Adresse::setCode_postal(unsigned int value)
{
    if(value<=99999)
        code_postal = value;
    else
        throw ExceptionAdresse("Valeur code postal invalide.");
}

std::string Adresse::getVille() const
{
    return ville;
}

void Adresse::setVille(const std::string &value)
{
    regex r("[ [:alpha:]]*");
    if(!regex_match(value,r)){
        throw ExceptionAdresse("Charctere invalide pour attribut ville.");
    }else{
        string tempv=value;
        for(auto & c: tempv) c = toupper(c);
        ville = trim(tempv);
    }
}

unsigned int Adresse::getDepartement() const
{
    return getCode_postal()/1000;
}

Adresse &Adresse::operator=(const Adresse &a)
{
    this->setCode_postal(a.getCode_postal());
    this->setComplement(a.getComplement());
    this->setNumero(a.getNumero());
    this->setRue(a.getRue());
    this->setVille(a.getVille());
    return *this;
}

std::string Adresse::to_str() const
{
    stringstream resultat;
    resultat<<getNumero()<<","<<getRue()<<endl;
    if(getComplement().size()>0)
        resultat<<getComplement()<<endl;
    resultat<<getCode_postal()<<" "<<getVille()<<endl;
    return resultat.str();
}




Adresse::Adresse(const Adresse &a)
{
    this->setCode_postal(a.getCode_postal());
    this->setComplement(a.getComplement());
    this->setNumero(a.getNumero());
    this->setRue(a.getRue());
    this->setVille(a.getVille());
}
