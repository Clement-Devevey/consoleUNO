#ifndef header_joueur_h
#define header_joueur_h
#include "Deques.h"

class Joueur
{
protected:
    std::vector<Carte> main;
    std::string pseudo;

public:
    Joueur(std::string pseudo) : pseudo(pseudo) { }

    void setPseudo(std::string pseudo) { this->pseudo = pseudo; }
    std::string getPseudo() const { return this->pseudo; }
    std::vector<Carte> getMain() const { return this->main; }
    void afficherMain() const;
    bool joueCarte(const Carte& carte_a_poser, const Carte& carte_defausse) const; //renvoie true si c'est possible de la poser sur la défausse
    void pioche(const Carte& c); 
    void pioche_n_carte(const std::vector<Carte>& c); //pioche nb cartes
    void genereMain(const std::vector<Carte>& main);
    void eraseCarte(int choix);
    bool aDesCartes();
};
#endif