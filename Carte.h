#ifndef header_cartes_h
#define header_cartes_h
#include <string>
#include<iostream>
#include<vector>
#include <algorithm>

class Carte
{
protected:
    std::string couleur;
    int numero;
    std::string effet;

public:
    Carte(std::string couleur, int numero, std::string effet = ""); /*couleur et numero sont obligatoires, effet est facultatif. -> Un 4 rouge n'a aucun effet -> Un +4 a un effet */
    //Pas besoin de destructeur
    std::string getCouleur() const { return this->couleur; }
    void setCouleur(std::string couleur) { this->couleur = couleur; }
    int getNumero() const { return this->numero; }
    std::string getEffet() const { return this->effet; }
    void afficher() const;

};


#endif