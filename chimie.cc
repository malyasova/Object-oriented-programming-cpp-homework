#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Flacon(string name, double vol, double acidity){
    nom = name;
    volume = vol;
    pH = acidity;
  };
//const below refers to this (we cannot change instance members)
  ostream& etiquette(ostream& sortie) const{
      sortie << nom << " : " << volume << " ml, pH " << pH;
      return(sortie);
  };
  Flacon& operator+=(Flacon const& flacon){
      nom = nom + " + " + flacon.nom;
      pH += (log10(volume + flacon.volume) - log10(volume + flacon.volume * pow(10.0, pH - flacon.pH)));
      volume += flacon.volume;
      return *this;  
  };
};
ostream& operator<<(ostream& sortie, Flacon const& flacon){
    return flacon.etiquette(sortie);

};
const Flacon operator+(Flacon flacon1, Flacon const& flacon2){
    flacon1 += flacon2;
    return flacon1;
};
#define BONUS
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
