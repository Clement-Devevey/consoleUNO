#include "Joueur.h"
using namespace std;

void Joueur::afficherMain() const
{
    for_each(main.begin(), main.end(), afficher());   //On réutilise le foncteur afficher définit dans deques.h
}

bool Joueur::joueCarte(const Carte& carte_a_poser, const Carte& carte_defausse) const//renvoie true si c'est possible de la poser sur la défausse
{
    if (carte_a_poser.getCouleur()=="Noir")
    {
        return true;
    }
    else if (carte_a_poser.getEffet() == "")
    {
        return (carte_defausse.getNumero() == carte_a_poser.getNumero()) || (carte_defausse.getCouleur() == carte_a_poser.getCouleur());
    }
    else
    {
        return (carte_defausse.getEffet() == carte_a_poser.getEffet()) || (carte_defausse.getCouleur() == carte_a_poser.getCouleur());
    }
    
}

void Joueur::pioche(const Carte& c) //pioche nb cartes
{
    main.push_back(c);
}

void Joueur::genereMain(const vector<Carte>& main)
{
    this->main = main;
}

void Joueur::eraseCarte(int choix)
{
    main.erase(main.begin() + choix-1);
}

bool Joueur::aDesCartes()
{
    return !this->main.empty();
}

void Joueur::pioche_n_carte(const vector<Carte>& c) //pioche nb cartes
{
    for (vector<Carte>::const_iterator it = c.begin() ; it != c.end(); ++it)
    {
        this->pioche(*it);
    }
}