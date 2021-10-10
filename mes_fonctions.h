#ifndef header_fonction_h
#define header_fonction_h
#include<locale>
#include "Joueur.h"


void Clear();

void afficheMenu();

int getNbJoueurs();

void remplirMains(std::vector<Joueur>& J, Deques& d);

void gestionDuSens(bool& sens_croissant, int& num_joueur, const int& nb_joueurs);

void afficheMain(const Joueur& J);

void afficheDefausse(const Deques& d);

int  getUserAction();

int getIndiceCarte(const Joueur& J, const Deques& d);

void pioche(Joueur& J, Deques& d);

void demandeCouleur(const std::vector<std::string>& listCouleur, Deques& d);

void gestionCarteSpeciale(Deques& d, bool& sens_croissant, int& num_joueur, const int& nb_joueurs, const int& num_joueur_actuel, std::vector<Joueur>& Joueurs, const std::vector<std::string>& listCouleur);

class addJoueurs
{
public:
    addJoueurs() : i(0) { }
    Joueur operator()();
private:
    int i;
    std::string pseudo;
};

class afficherJoueurs
{
public:
    void operator()(Joueur j);
};
#endif