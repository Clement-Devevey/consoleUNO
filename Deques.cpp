#include "Deques.h"

using namespace std;

Deques::Deques()
{
    /* Utilisé pour mélanger le deck */
    seed = chrono::system_clock::now().time_since_epoch().count();


}
void Deques::init()
{
    this->remplirDeck();
    this->Melanger();
    this->retourneCarte();
}
void Deques::remplirDeck()
{
    deck.clear();
    generate_n(back_inserter(deck), 72, normalCartes()); //Genère les cartes de 1 à 9 en x2 de chaque couleur
    deck.push_back(Carte("Jaune",0));
    deck.push_back(Carte("Rouge",0)); //Genère les 0 en x1 de chaque couleur
    deck.push_back(Carte("Bleu",0));
    deck.push_back(Carte("Vert",0));
    generate_n(back_inserter(deck), 32, specialCartes()); //Genère les cartes spéciales : 8x P, S, +2 et 4x +4, C
}

void Deques::retourneCarte() //retourne une carte du deck pour la mettre sur la défausse (pour commencer le jeu)
{
    while (deck.back().getEffet()!="")
    {
        Melanger();
    }
    
    defausse.push_back(deck.back()); //On pose la carte sur la défausse
    deck.pop_back(); //On la retire du deck*
}

void Deques::afficheDerniereCarteDefausse() const //affiche la dernière carte posée sur la défausse
{
    defausse.back().afficher();
}

void Deques::afficheDeck() //affiche la dernière carte posée sur la défausse
{
    for_each(deck.begin(), deck.end(), afficher());   //Et on affiche les éléments
}

Carte Deques::tirerUneCarte()
{
    Carte temp(deck.back());
    deck.pop_back();
    if (deck.size() == 0)
    {
        this->Permuter();
        defausse.push_back(deck.back());
        deck.pop_back();
    }
    return temp;
}

vector<Carte> Deques::tirerNCarte(int n)
{
    vector<Carte> c;
    for(int i =0;i<n;++i) { c.push_back(tirerUneCarte()); }
    return c;
}

Carte Deques::derniereCarteJouee() const
{
    return defausse.back();
}

vector<Carte> Deques::genererCartes(int nb)
{
    vector<Carte> c;
    for (int i = 0; i<nb;++i)
    {
        c.push_back(tirerUneCarte());
    }
    return c;
}

void Deques::Melanger() // permet de mélanger les cartes
{
    shuffle (deck.begin(), deck.end(), default_random_engine(seed));
}
void Deques::Permuter() //Echange le deck et la défausse quand le deck est vide
{
    defausse.swap(deck);
    //this->Melanger();

}

void Deques::cartePosee(const Carte& c)
{
    defausse.push_back(c);
}

/* ----- Foncteur pour création cartes------ */
normalCartes::normalCartes(): i(0), j(0), couleur("Jaune")
{
}

Carte normalCartes::operator()()
{
    ++i;
    if(i==10)
    {
        this->couleur = listCouleur[j];
        ++j;
        i=1;
    }
    return Carte(this->couleur, i);
    
}

specialCartes::specialCartes(): i(-1), j(0), k(0), couleur("Jaune")
{
}

Carte specialCartes::operator()()
{
    ++i;
    if(i==10)
    {
        this->couleur = listCouleur[k];
        ++k; //on passe à la couleur suivante
        j=0;
        i=0;
    }
    if (i%2==0 && i!=0)
    {
        j++;
    }
    if (listEffet[j] == "+4" || listEffet[j] == "C")
    {
        this->couleur = "Noir";
        ++i;
    }
    return Carte(this->couleur, -1, listEffet[j]);
    
}