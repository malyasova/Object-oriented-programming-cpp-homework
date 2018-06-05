#include <iostream>
using namespace std;

int main()
{
  cout << "Donnez l'heure de dÃ©but de la location (un entier) : ";
  int debut;
  cin >> debut;

  cout << "Donnez l'heure de fin de la location (un entier) : ";
  int fin;
  cin >> fin;

  /*****************************************************
   * ComplÃ©ter le code Ã  partir d'ici
   *****************************************************/
  if ((debut < 0) or (debut > 24) or (fin < 0) or (fin > 24)){
    cout << "Les heures doivent Ãªtre comprises entre 0 et 24 !" << endl;
  };
  if (debut == fin){
    cout << "Bizarre, vous n'avez pas louÃ© votre vÃ©lo bien longtemps !" << endl;
  };
  if (debut > fin){
    cout << "Bizarre, le dÃ©but de la location est aprÃ¨s la fin ..." << endl;
  };
  if (debut < fin){
    cout << "Vous avez louÃ© votre vÃ©lo pendant" << endl;
    if (debut < 7 or fin > 17){
      cout << max(7 - debut, 0) + max(fin - 17, 0) << " heure(s) au tarif horaire de 1" 
           << " franc(s)" << endl;
    };
    if (debut < 17 and fin >7){
      cout << min(fin, 17) - max(debut, 7) << " heure(s) au tarif horaire de 2" 
           << " franc(s)" << endl;
    };  
    cout << "Le montant total Ã  payer est de " << max(7 - debut, 0) + max(fin - 17, 0) + 2*(min(fin, 17) - max(debut, 7))
         << " franc(s)." << endl;
  };
  /*******************************************
   * Ne rien modifier aprÃ¨s cette ligne.
   *******************************************/

  return 0;
}
