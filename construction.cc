#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique(Forme form, Couleur color)
  {
      forme = form;
      couleur = color;
  };
  ostream& afficher(ostream& sortie) const
  {
      if(couleur.empty())
          sortie << forme;
      else
          sortie << "(" << forme << ", " << couleur << ")";
      return sortie;
  };  
};

ostream& operator<<(ostream& sortie, const Brique& brique){
    brique.afficher(sortie);
    return sortie;
}

typedef vector<vector<vector<Brique> > > Grid;

class Construction
{
  friend class Grader;
private:
  Grid contenu;
public:
  Construction(Brique brique){
      contenu = {{{brique}}};
  };
  ostream& afficher(ostream& sortie) const
  {
      for(int i = contenu.size()-1; i>=0; i--)
      {
          sortie << "Couche " << i << " :\n";
          for(auto ligne : contenu[i])
          {
              for(auto brique : ligne)
                  sortie << brique << ' ';
              sortie << endl;
          };
      };
      return(sortie);
  };
/*******************************************************
* Add a roof to building (height is 1st dimension)     *
*******************************************************/
  Construction& operator^=(const Construction& toit){
      contenu.insert(contenu.end(), toit.contenu.begin(), toit.contenu.end());
      return(*this);
  };
/*******************************************************
* Add a wall to building from behind (2nd dimension)   *
* Does nothing if wall is not as high as building      *
* Ignores the part of the wall higher than building    *
*******************************************************/
  Construction& operator-=(const Construction& mur){
      //validity check
      size_t N = contenu.size();
      if (mur.contenu.size() < N)
          return *this;
      //operator
      size_t max_depth = 0;
      for(auto couche : contenu)
          max_depth = max(couche.size(), max_depth);
      for(size_t i = 0; i<N; i++)
//          contenu[i].insert(max_depth, mur.contenu[i].begin(), mur.contenu[i].end());
            contenu[i].insert(contenu[i].end(), mur.contenu[i].begin(), mur.contenu[i].end()); 
      return(*this);
  };
/*******************************************************
* Add a wall to building from right (3rd dimension)    *
* Does nothing if wall is not as high as building      *
* Ignores the part of the wall higher than building    *
*******************************************************/
  Construction& operator+=(const Construction& mur){
      size_t N = contenu.size();
      //validity check
      if (mur.contenu.size() < N)
          return *this;
      for(size_t i = 0; i < N; ++i)
          if(mur.contenu[i].size() < contenu[i].size())
              return *this;
      //operator
      size_t max_width = 0;          
      for(auto couche : contenu)
          for(auto ligne : couche)
              max_width = max(ligne.size(), max_width);
      for(size_t i = 0; i < N; ++i)
          for(size_t j = 0; j < contenu[i].size(); ++j)
//              contenu[i].insert(max_width, mur.contenu[i][j].begin(), mur.contenu[i][j].end());
                contenu[i][j].insert(contenu[i][j].end(), mur.contenu[i][j].begin(), mur.contenu[i][j].end());
      return(*this);
  };
};
const Construction operator^(Construction fondement, Construction const& toit){
    fondement ^= toit;
    return(fondement);
};
const Construction operator+(Construction fondement, Construction const& mur){
    fondement += mur;
    return(fondement);
};
const Construction operator-(Construction fondement, Construction const& mur){
    fondement -= mur;
    return(fondement);
};
const Construction operator*(unsigned int n, Construction const& maison){
    Construction answer = maison;
    for(unsigned int i = 0; i < n-1; i++)
        answer += maison;
    return(answer);
};
const Construction operator/(unsigned int n, Construction const& maison){
    Construction answer = maison;
    for(unsigned int i = 0; i < n-1; i++)
        answer ^= maison;
    return(answer);
};
const Construction operator%(unsigned int n, Construction const& maison){
    Construction answer = maison;
    for(unsigned int i = 0; i < n-1; i++)
        answer -= maison;
    return(answer);
};
ostream& operator<<(ostream& sortie, const Construction& construction){
    construction.afficher(sortie);
    return(sortie);
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
