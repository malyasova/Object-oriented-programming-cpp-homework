#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
#include <memory>
// Chaines de caractères à utiliser pour les affichages:
/*

été jeté

d'un

n'est

L'oeuvre

bibliothèque

détruit

*/
class Auteur{
private:
  string name;
  bool awarded;
public:
  Auteur(string name, bool awarded = false): name(name), awarded(awarded){};
//We make Auteur class uncopiable:
  Auteur(Auteur const&) = delete;
  string getNom() const{
    return name;
  };
  bool getPrix() const{
    return awarded;
  };  
};
class Oeuvre{
private:
  string title;
  Auteur const& author;
  string language;
public:
  Oeuvre(string title, const Auteur& author, string language):
    title(title),
    author(author),
    language(language){};
  Oeuvre(Oeuvre const& autre) = delete;
  const string getTitre() const{
    return title;
  };
  Auteur const& getAuteur() const{
    return author;
  };
  const string getLangue() const{
    return language;
  };
  void affiche() const{
    cout << title << ", " << author.getNom() << ", en " << language << endl;
  };
  /*bool operator==(Oeuvre const& autre){
    return(title == autre.getTitre() and \
           author == autre.getAuteur() and \
           language == autre.getLangue());
  };*/
  ~Oeuvre(){
    cout << "L'oeuvre \"" << title << ", " << author.getNom() << ", en " << language << "\" n'est plus disponible.\n";
  };
};
class Exemplaire{
private:
  Oeuvre const& book;
public:
  Exemplaire(Oeuvre const& book): book(book){
    cout << "Nouvel exemplaire de : ";
    book.affiche();
  };
//A reference cannot be reassigned, so it must be initialized at the member-initialization-list
  Exemplaire(Exemplaire const& autre): book(autre.book){
    cout << "Copie d'un exemplaire de : ";
    autre.getOeuvre().affiche();
  };
  ~Exemplaire(){
    cout << "Un exemplaire de \"" << book.getTitre() << ", " << book.getAuteur().getNom() << ", en " << book.getLangue() << "\" a été jeté !\n";
  };
  const Oeuvre& getOeuvre() const{
    return book;
  };
  void affiche() const{
    cout << "Exemplaire de : " << book.getTitre() << ", " << book.getAuteur().getNom() << ", en " << book.getLangue();
  };
};
class Bibliotheque{
private:
  vector<unique_ptr<Exemplaire> > collection;
  string name;
public:
  Bibliotheque(string name): name(name){
    cout << "La bibliothèque " << name << " est ouverte !\n";
  };
  string getNom() const{
    return name;
  };
  void stocker(const Oeuvre& book, unsigned int n = 1){
    for(int i = 0; i < n; ++i)
      collection.push_back(unique_ptr<Exemplaire>(new Exemplaire(book)));
  };
  void lister_exemplaires(string language){
    if(language == "")
      lister_exemplaires();
    else
      for(auto& ex_ptr : collection)
        if(ex_ptr->getOeuvre().getLangue() == language){
          ex_ptr->affiche();
          cout << endl;
        };  
  };
  void lister_exemplaires(){
    for(auto& ex_ptr : collection){
      ex_ptr->affiche();
      cout << endl;
    };
  };
  unsigned int compter_exemplaires(Oeuvre const& book){
    unsigned int n = 0;
    for(auto& ex_ptr : collection)
      if(ex_ptr->getOeuvre().getTitre() == book.getTitre())
        ++n;
    return n;
  };
  void afficher_auteurs(bool prix = false){
    if(prix){
      for(auto& ex_ptr : collection)
        if(ex_ptr->getOeuvre().getAuteur().getPrix())
          cout << ex_ptr->getOeuvre().getAuteur().getNom() << endl;
    }
    else
      for(auto& ex_ptr : collection)
        cout << ex_ptr->getOeuvre().getAuteur().getNom() << endl;
  };
  ~Bibliotheque(){
    cout << "La bibliothèque " << name << " ferme ses portes, \n";
    cout << "et détruit ses exemplaires :\n";
  };
};
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
