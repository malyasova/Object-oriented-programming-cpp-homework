#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  Coordonnees position_;
  Pavillon pavillon_;
  Etat etat_;
public:
  Navire(int x, int y, Pavillon const& pavillon, Etat const& etat = Intact)
  : position_(x,y),
    pavillon_(pavillon),
    etat_(etat)
  {};
//destructors in virtual classes must be declared virtual
  virtual ~Navire() = 0;
  Coordonnees const& position() const{
    return position_;
  }
  void avancer(int de_x, int de_y){
    if(etat_ != Coule){
      position_ += Coordonnees(de_x, de_y);
    };
  };
  void renflouer(){  
    etat_ = Intact;
  };
  ostream& afficher(ostream& sortie) const;
  string virtual nom_generique() const{return "";};
  void virtual attaque(Navire& autre) = 0;
  void virtual replique(Navire& autre) = 0;
  void virtual est_touche() = 0;
  void rencontrer(Navire& autre);
private:
  static constexpr unsigned int rayon_rencontre = 10;
};
Navire::~Navire(){};
void Coordonnees::operator+=(Coordonnees const& autre)
{
  x_ += autre.x();
  y_ += autre.y();
};
double distance(Coordonnees const& one, Coordonnees const& two)
{
  return sqrt(sq(one.x() - two.x()) + sq(one.y() - two.y()));
};

double distance(Navire const& one, Navire const& two)
{ 
  return distance(one.position(), two.position());
};
void Navire::rencontrer(Navire& autre){
  if (distance(*this, autre) < Navire::rayon_rencontre\
    and etat_ != Coule and autre.etat_ != Coule \
    and pavillon_ != autre.pavillon_)
  {
    attaque(autre);
    autre.replique(*this);
  };    
};
//surcharge d'operateur <<: coordonnees, pavillon, etat, navir
ostream& operator<<(ostream& sortie, Coordonnees const& point)
{
  sortie << "(" << point.x() << ", " << point.y() << ")";
  return sortie;
};
ostream& operator<<(ostream& sortie, Pavillon flag)
{
  if(flag == JollyRogers)
    sortie << "pirate";
  else if(flag == CompagnieDuSenegal)
    sortie << "français";
  else if(flag == CompagnieDOstende)
    sortie << "autrichien";
  else
    sortie << "pavillon inconnu";
  return sortie;
};
ostream& operator<<(ostream& sortie, Etat state)
{
  if(state == Intact)
    sortie << "intact";
  else if(state == Endommage)
    sortie << "ayant subi des dommages";
  else if(state == Coule)
    sortie << "coulé";
  else
    sortie << "état inconnu";
  return sortie;
};
ostream& operator<<(ostream& sortie, Navire& ship)
{
  ship.afficher(sortie);
  return sortie;
};

ostream& Navire::afficher(ostream& sortie) const{
  sortie << nom_generique() << " en " << position_ << " battant pavillon " << pavillon_ << ", " << etat_;
  return sortie;
};

class Pirate: public virtual Navire{
public:
  Pirate(int x, int y, Pavillon flag): Navire(x,y, flag){};
  void virtual attaque(Navire& autre) override{
    if(etat_ != Coule){
      cout << "A l'abordage !\n";
      autre.est_touche();
    };
  };
  void virtual replique(Navire& autre) override{
    if(etat_ != Coule){
      cout << "Non mais, ils nous attaquent ! On riposte !!\n";
      attaque(autre);
    };
  };
  void virtual est_touche() override{
    if(etat_ == Intact)
      etat_ = Endommage;
    else if(etat_ == Endommage)
      etat_ = Coule;
  };
  string virtual nom_generique() const override{
    return "bateau pirate";
  };
};
class Marchand: public virtual Navire{
public:
  Marchand(int x, int y, Pavillon flag): Navire(x,y, flag){};
  void virtual attaque(Navire& autre) override{
    if(etat_ != Coule)
      cout << "On vous aura ! (insultes)\n";
  };
  void virtual replique(Navire& autre) override{
    if(etat_ == Coule)
      cout << "SOS je coule !\n";
    else
      cout << "Même pas peur !\n";
  };
  void virtual est_touche() override{
    etat_ = Coule;
  };                                                                                                                                                                           
  string virtual nom_generique() const override{
    return "navire marchand";
  };
};
class Felon: public Marchand, public Pirate{
public:
  Felon(int x, int y, Pavillon flag): \
       Navire(x,y,flag),\
       Marchand(x,y,flag),\
       Pirate(x,y,flag){};

  void virtual attaque(Navire& autre) final{
    Pirate::attaque(autre);
  };
  void virtual replique(Navire& autre) final{
    Marchand::replique(autre);
  };
  void virtual est_touche() final{
    Pirate::est_touche();
  };                                                                                                                                                                           
  string virtual nom_generique() const final{
    return "navire félon";
  };
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);

  return 0;
}
