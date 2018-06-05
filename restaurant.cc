#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
#include <memory>
//==================================================
class Produit{
private:
  string nom;    //name of the product
  string unite;  //unit of measurement
public:
  Produit(string nom = "", string unite = "")
  :nom(nom) 
  ,unite(unite)
  {};

  string getNom() const{return nom;};
  string getUnite() const{return unite;};
  virtual string toString() const{return nom;};
  virtual const Produit* adapter(double n) const{return this;};
  virtual ~Produit() = default;
  virtual double quantiteTotale(const string& nomProduit) const{
    if(nom==nomProduit)
      return(1);
    else
      return(0);
  };
};
//===================================================
class Ingredient{
private:
  Produit const& produit;
  double quantite;
public:
  Ingredient(Produit const& produit, double quantite = 0)
  : produit(produit)
  , quantite(quantite)
  {}; 

  Produit const& getProduit() const{
    return produit;
  };
  
  double getQuantite() const{
    return quantite;
  };
 
  string descriptionAdaptee(){
    return to_string(quantite) + " " + produit.getUnite() + " de " + produit.adapter(quantite)->toString();
  };

  double quantiteTotale(const string& nomProduit){
    return quantite*produit.quantiteTotale(nomProduit);
  };
};
//=========================================================
class Recette{
private:
  string nom;   //name of the receipt
public:
  double nbFois_;  //how many times we want to make this
private:
  vector<unique_ptr<Ingredient> > ingredients; //list of ingredients
public:
  Recette(string nom, double nbFois_ = 1.0)
  : nom(nom), nbFois_(nbFois_)
  {};
//copy constructor - we must have it
  Recette(const Recette& autre):nom(autre.nom), nbFois_(autre.nbFois_){
    for(auto& ingredient : autre.ingredients)
      ingredients.push_back(unique_ptr<Ingredient>(new Ingredient(ingredient->getProduit(), ingredient->getQuantite())));
  };
  Recette& operator=(Recette autre){
    nom = autre.nom;
    nbFois_ = autre.nbFois_;
    for(auto& ingredient : autre.ingredients)
      ingredients.push_back(unique_ptr<Ingredient>(new Ingredient(ingredient->getProduit(), ingredient->getQuantite())));
  };
  void ajouter(const Produit& p, double quantite){
    ingredients.push_back(unique_ptr<Ingredient>(new Ingredient(p, nbFois_*quantite)));
  };

  Recette adapter(double n) const {
    Recette answer(nom, n*nbFois_);
    for(auto& ingredient : ingredients)
      answer.ajouter(ingredient->getProduit(), ingredient->getQuantite());
    return answer;
  };

  string toString() const {
    string answer = string("Recette ") + string("\"") + nom + string("\" x ") + to_string((int)(nbFois_+0.5)) + string(":");
    for(int i = 0; i < ingredients.size(); ++i){
      answer += string("\n") + to_string(i+1) + string(". ") + ingredients[i]->descriptionAdaptee();
    };
    return answer; 
  };

  double quantiteTotale(const string& nomProduit) const{
    double answer(0);
    for(auto& ingredient : ingredients)
      answer += ingredient->quantiteTotale(nomProduit);
    return answer;
  };
};
//ProduitCuisine est un produit qui a une recette
class ProduitCuisine: public Produit {
public:
  Recette recette;
public:
  ProduitCuisine(string name, double nbFois_ = 1.0)
  :Produit(name, "portion(s)")
  , recette(name, nbFois_)
  {};

  void ajouterARecette(const Produit& produit, double quantite){
    recette.ajouter(produit, quantite);
  };
  virtual const ProduitCuisine* adapter(double n) const{
    ProduitCuisine* answer(new ProduitCuisine(getNom(), n*recette.nbFois_));
    answer->recette = recette.adapter(n);
    return answer;
  };
  virtual string toString() const{
    return Produit::toString() + "\n" + recette.toString();
  };
  virtual double quantiteTotale(const string& nomProduit) const{
    if(getNom() == nomProduit)
      return(1);
    else
      return recette.quantiteTotale(nomProduit);
  }; 
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
