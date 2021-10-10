#include"Carte.h"
using namespace std;

Carte::Carte(string couleur, int numero, string effet) : couleur(couleur), numero(numero), effet(effet)
{
    if (this->numero > 9)
    {
        cout <<"Erreur sur le numero de la carte : " << this->numero <<endl;
    }

    vector<string> listCouleur{"Rouge", "Jaune", "Bleu", "Vert", "Noir"};

    if (!(find(begin(listCouleur), end(listCouleur), this->couleur) != end(listCouleur))) //Vérifie si la couleur est dans la liste des couleurs
    {
        cout << "Erreur sur la couleur : " << this->couleur <<endl;
    }
}

void Carte::afficher() const
{
    /* Pour changer la couleur du background et du text :
https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
white        37         47
*/
    if (this->effet == "")
    {

        if(this->couleur == "Rouge")
        {
            cout << "\033[1;37;41m "<<this->numero <<" \033[0m "; 
        }

        else if(this->couleur == "Jaune")
        {
            cout << "\033[1;37;43m "<<this->numero <<" \033[0m "; 
        }

        else if(this->couleur == "Vert")
        {
            cout << "\033[1;37;42m "<<this->numero <<" \033[0m "; 
        }

        else if(this->couleur == "Bleu")
        {
            cout << "\033[1;37;44m "<<this->numero <<" \033[0m "; 
        }
                
    }
    else
    {
        if(this->couleur == "Rouge")
        {
            cout << "\033[1;37;41m "<<this->effet <<" \033[0m "; 
        }

        else if(this->couleur == "Jaune")
        {
            cout << "\033[1;37;43m "<<this->effet <<" \033[0m "; 
        }

        else if(this->couleur == "Vert")
        {
            cout << "\033[1;37;42m "<<this->effet <<" \033[0m "; 
        }

        else if(this->couleur == "Bleu")
        {
            cout << "\033[1;37;44m "<<this->effet <<" \033[0m "; 
        }

        else if(this->couleur == "Noir")
        {
            cout << "\033[1;37;40m "<<this->effet <<" \033[0m "; 
        }
    }
}