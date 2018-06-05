#include <iostream>
#include <string>
using namespace std;

class Souris
{
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  private:
  double poids;
  string couleur;
  unsigned int age; 
  unsigned int esperance_vie;
  bool clonee;
  public:
  Souris(double weight, string color, unsigned int age = 0, unsigned int life_expectancy = 36):
    poids(weight), 
    couleur(color),
    age(age),
    esperance_vie(life_expectancy)
  {
    clonee = false;
    cout << "Une nouvelle souris !\n";
  };
  Souris(Souris& autre):
    poids(autre.poids),
    couleur(autre.couleur),
    age(autre.age),
    esperance_vie(autre.esperance_vie*4/5)
  {
    clonee = true;
    cout << "Clonage d'une souris !\n";
  };
  ~Souris()
  {
    cout << "Fin d'une souris...\n";
  };
  void afficher() const{
    cout << "Une souris " << couleur;
    if(clonee)
      cout << ", clonee,";
    cout << " de " << age << " mois et pesant " << poids << " grammes\n";
  };
  void vieillir(){
    age += 1;
    if(clonee and (2*age >= esperance_vie))
      couleur = "verte";
  };
  void evolue(){
    age = esperance_vie;
    if(clonee and (2*age >= esperance_vie))
      couleur = "verte";
  }
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

}; // fin de la classe Souris

int main()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  // ... un tableau peut-être...
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}
