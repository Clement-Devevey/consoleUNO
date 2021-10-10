#ifndef header_deques_h
#define header_deques_h
#include "Carte.h"
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <list>
class Deques
{
protected:
    std::vector<Carte> deck;
    std::vector<Carte> defausse;
    unsigned seed;
public:
    Deques();
    void init();
    void setCouleurDefausse(std::string couleur) { defausse.back().setCouleur(couleur); }
    void remplirDeck();
    void retourneCarte(); //retourne une carte du deck pour la mettre sur la défausse (pour commencer le jeu)
    void afficheDerniereCarteDefausse() const; //affiche la dernière carte posée sur la défausse
    void afficheDeck();
    Carte tirerUneCarte();
    std::vector<Carte> tirerNCarte(int n);
    Carte derniereCarteJouee() const;
    std::vector<Carte>& getDefausse() {return defausse;}
    void Melanger(); // permet de mélanger les cartes
    void Permuter(); //Echange le deck et la défausse quand le deck est vide
    std::vector<Carte> genererCartes(int nb);
    void cartePosee(const Carte& c);
};


/* ----- Foncteur création cartes normales ------- */
class normalCartes
{
public:
    normalCartes();
    Carte operator()();
protected:
    int i,j;
    std::string couleur;
    std::vector<std::string> listCouleur{"Rouge", "Bleu", "Vert", "Jaune", "Rouge", "Bleu", "Vert"};
};

/* ----- Foncteur création cartes spéciales ------- */
class specialCartes
{
public:
    specialCartes();
    Carte operator()();
protected:
    int i,j,k;
    std::string couleur;
    std::vector<std::string> listCouleur{"Rouge", "Bleu", "Vert"};
    std::vector<std::string> listEffet{"P", "S", "+2", "+4", "C"};
};



/* ----- Foncteur affichage du deck ------- */
class afficher
{
public:
    void operator()(Carte c) { c.afficher(); };
};

#endif