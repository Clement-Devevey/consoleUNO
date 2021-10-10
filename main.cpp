#include "mes_fonctions.h"
using namespace std;

int main()
{
    
/* Déclaration des variables */
    string choix_couleur = "0";
    int nb_joueurs,numero_joueur_actuel;
    bool sens_croissant = true;
    vector<Joueur> Joueurs;
    Deques d;
    int num_joueur = -1, choix;
    vector<string> listCouleur{"Rouge", "Jaune", "Bleu", "Vert"};

/* boucle infinie + boucle qui récupère le nb de joueurs */
    while (1) // Boucle globale
    {
        afficheMenu();
        nb_joueurs = getNbJoueurs();

/* Remise à 0 du deck + défausse, de la liste des joueurs dans le cas ou on relance une partie */
        Joueurs.clear();
        d.init();

/* Générer liste des joueurs */
        generate_n(back_inserter(Joueurs), nb_joueurs, addJoueurs());
        // affichage des pseudos si besoin : for_each(Joueurs.begin(), Joueurs.end(), afficherJoueurs());

        remplirMains(Joueurs, d);

/* Boucle de jeu : on continue la partie tant qu'il y au moins 2 joueurs */

        while(Joueurs.size() > 1)
        {
            Clear();
            gestionDuSens(sens_croissant, num_joueur, nb_joueurs);
            afficheMain(Joueurs[num_joueur]);
            afficheDefausse(d);

            if (getUserAction() == 1) //il veut poser une carte
            {
                choix = getIndiceCarte(Joueurs[num_joueur], d); //Récupère indice de la carte qu'il veut poser
                if ( choix == -1) //-1 pour lui laisser une chance de piocher, (au cas ou il ne peut rien poser)
                {
                    pioche(Joueurs[num_joueur], d);
                }
            /* Il pose une carte : */
                else
                {
                    numero_joueur_actuel = num_joueur;
                    cout <<"Vous avez posé une carte !"<<endl;
                    d.cartePosee(Joueurs[num_joueur].getMain()[choix-1]); //On annonce à la defausse la carte qui a été posée.

                    if (d.derniereCarteJouee().getEffet() !="") //Si la carte a un effet, alors on fait ce qu'il faut
                    {
                        gestionCarteSpeciale(d, sens_croissant, num_joueur, nb_joueurs, numero_joueur_actuel, Joueurs, listCouleur);
                    }
                    
                    Joueurs[numero_joueur_actuel].eraseCarte(choix); //On supprime la carte de la main du joueur
                    if (!Joueurs[numero_joueur_actuel].aDesCartes()) //Si le joueur n'a plus de carte, il est exclu de la partie
                    {
                        Joueurs.erase(Joueurs.begin() + numero_joueur_actuel);
                        --nb_joueurs;
                    }
                }
            }

        /* Pioche */
            else
            {
                pioche(Joueurs[num_joueur], d);
            }
        }
        cout << "Partie terminée. Rejouer ? "<<endl;
    }

    return 0;
}