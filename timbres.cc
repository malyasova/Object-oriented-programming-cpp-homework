#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
public:
  string nom;
  unsigned int annee;
  string pays;
  double valeur_faciale;
  Timbre(string name, unsigned int year, string country = "Suisse", double value = 1.0): nom(name), annee(year), pays(country), valeur_faciale(value){};
  double vente(){
  if(age() <= 5)
      return(valeur_faciale);
  else
      return(valeur_faciale*2.5*age());
  };
  const unsigned int age(){
      return(ANNEE_COURANTE - annee);
  };
  ostream& afficher(ostream& sortie) const{
      sortie << " de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
      return(sortie);
  };
};
class Rare: public Timbre{
private:
  static constexpr unsigned int PRIX_BASE_TRES_RARE = 600;
  static constexpr unsigned int PRIX_BASE_RARE = 400;
  static constexpr unsigned int PRIX_BASE_PEU_RARE = 50;
  double number; //number of stamps like this one
public:
  Rare(string name, unsigned int year, string country = "Suisse", double value = 1.0, double num = 100.0): Timbre(name, year, country, value), number(num){};
  const double nb_exemplaires(){
      return(number);
  };
  const unsigned int prix_base(){
      if(number < 100)
          return(PRIX_BASE_TRES_RARE);
      else if(number < 1000)
          return(PRIX_BASE_RARE);
      else
          return(PRIX_BASE_PEU_RARE);
  };  
  double vente(){
      return(prix_base()*(age()/10.0));
  };
  ostream& afficher(ostream& sortie) const{
      sortie << " rare (" << number << " ex.)";
      Timbre::afficher(sortie);
      return(sortie);
  }; 
};
class Commemoratif: public Timbre{
public:
  Commemoratif(string name, unsigned int year, string country = "Suisse", double value = 1.0):Timbre(name, year, country, value){};
  double vente(){
      return(2*Timbre::vente());
  };
  ostream& afficher(ostream& sortie) const{
      sortie << " commémoratif ";
      Timbre::afficher(sortie);
      return(sortie);
  }; 
};
ostream& operator<<(ostream& sortie, const Timbre& timber){
    sortie << "Timbre ";
    timber.afficher(sortie);
    return(sortie);
};
ostream& operator<<(ostream& sortie, const Rare& timber){
    sortie << "Timbre ";
    timber.afficher(sortie);
    return(sortie);
};
ostream& operator<<(ostream& sortie, const Commemoratif& timber){
    sortie << "Timbre ";
    timber.afficher(sortie);
    return(sortie);
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
