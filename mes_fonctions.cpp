#include"mes_fonctions.h"

using namespace std;

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void afficheMenu()
{

    cout << "Bienvenue sur " << endl;

    cout << R"(

██╗   ██╗███╗   ██╗ ██████╗ 
██║   ██║████╗  ██║██╔═══██╗
██║   ██║██╔██╗ ██║██║   ██║
██║   ██║██║╚██╗██║██║   ██║
╚██████╔╝██║ ╚████║╚██████╔╝
╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ 
                            

    )" << '\n';
}

int getNbJoueurs()
{
    string nb_joueurs;
    do
    {
        cout << "Saisissez le nombre de joueurs [2-4] (q pour quitter) : ";
        cin >> nb_joueurs;
        if(nb_joueurs[0] == 'q') { return 0; }
        // On s'assure que la valeur récupérée est comprise entre 2 et 4, ne contient pas plus d'un caractère, ou alors qu'elle est équivalent à q
    } while (nb_joueurs[0]-48<2 || nb_joueurs[0]-48 > 4); //-48 convertit un char en int
    return nb_joueurs[0]-48;
}


void remplirMains(std::vector<Joueur>& J, Deques& d)
{
    for (vector<Joueur>::iterator it = J.begin(); it != J.end(); ++it)
    {
        it->genereMain(d.genererCartes(6));
    }
}

void gestionDuSens(bool& sens_croissant, int& num_joueur, const int& nb_joueurs)
{
    if(sens_croissant) 
    { 
        ++num_joueur; 
        if (num_joueur >= nb_joueurs)
        {
            num_joueur = 0;
        }
    }
    else 
    { 
        --num_joueur; 
        if (num_joueur < 0)
        {
            num_joueur = nb_joueurs-1;
        }
    }
}

void afficheMain(const Joueur& J)
{
    cout << "C'est au tour de " << J.getPseudo() << endl << "Voici tes cartes : ";
    J.afficherMain();
}

void afficheDefausse(const Deques& d)
{
    cout <<endl<< "Voici la défausse : ";
    d.afficheDerniereCarteDefausse();
    cout <<endl;
}

int getUserAction()
{
    int choix;
    do 
    {
        cout << "1 - Poser une carte, 2 - Piocher une carte [1-2] : ";
        cin >> choix;
    }while(choix != 1 && choix != 2);
    return choix;
}

int getIndiceCarte(const Joueur& J, const Deques& d)
{
    int choix;
    bool carte_non_posable;
    do 
    {
        cout << "Saisir l'indice de la carte que vous souhaitez poser (-1 si vous voulez piocher) [1-" << J.getMain().size() << "] : ";
        cin >> choix;
        if ((choix>(int)J.getMain().size() || choix < 1))
        {
            carte_non_posable = true;
        }
        else if (choix != -1)
        {
            carte_non_posable = !J.joueCarte(J.getMain()[choix-1], d.derniereCarteJouee());
            
        }
        if (choix == -1)
        {
            carte_non_posable = false;
        }
    }while(carte_non_posable);

    return choix;
}

void pioche(Joueur& J, Deques& d)
{
    cout << "Vous piochez une carte" << endl;
    J.pioche(d.tirerUneCarte());
    cout << "voici vos cartes : ";
    J.afficherMain();
    cout << "Appuyer sur entrée  pour continuer";
    cin.ignore();
    cin.get();
}

void demandeCouleur(const std::vector<std::string>& listCouleur, Deques& d)
{
    string choix_couleur;
    do 
    {
        cout << "Choisir couleur [Rouge, Bleu, Vert, Jaune] : ";
        cin >> choix_couleur;
    }while(!(find(begin(listCouleur), end(listCouleur), choix_couleur) != end(listCouleur)));
    d.setCouleurDefausse(choix_couleur);
    cout << "Vous avez choisi la couleur : " << choix_couleur << " - Appuyer sur entrée pour continuer";
    cin.ignore();
    cin.get();
}

void gestionCarteSpeciale(Deques& d, bool& sens_croissant, int& num_joueur, const int& nb_joueurs, const int& num_joueur_actuel, vector<Joueur>& Joueurs, const vector<string>& listCouleur)
{
    if (d.derniereCarteJouee().getEffet() == "P" && sens_croissant)
    {
        ++num_joueur;
        if (num_joueur>=nb_joueurs) { num_joueur = 0; }
    }

    else if (d.derniereCarteJouee().getEffet() == "P" && !sens_croissant)
    {
        --num_joueur;
        if (num_joueur<0) { num_joueur = nb_joueurs-1; }
    }

    else if (d.derniereCarteJouee().getEffet() == "S") { sens_croissant = !sens_croissant; }

    else if (d.derniereCarteJouee().getEffet() == "+2" && sens_croissant)
    {
        if(num_joueur+1 >= nb_joueurs)
        {
            Joueurs[0].pioche_n_carte(d.tirerNCarte(2));
        }
        else
        {
            Joueurs[num_joueur_actuel+1].pioche_n_carte(d.tirerNCarte(2));
        }

    }

    else if (d.derniereCarteJouee().getEffet() == "+2" && !sens_croissant)
    {
        if(num_joueur-1 < 0)
        {
            Joueurs[nb_joueurs-1].pioche_n_carte(d.tirerNCarte(2));
        }
        else
        {
            Joueurs[num_joueur_actuel-1].pioche_n_carte(d.tirerNCarte(2));
        }
    }

    else if (d.derniereCarteJouee().getEffet() == "+4" && sens_croissant)
    {
        if(num_joueur+1 >= nb_joueurs)
        {
            Joueurs[0].pioche_n_carte(d.tirerNCarte(4));
            demandeCouleur(listCouleur, d);
        }
        else
        {
            Joueurs[num_joueur_actuel+1].pioche_n_carte(d.tirerNCarte(4));
            demandeCouleur(listCouleur, d);
        }

    }

    else if (d.derniereCarteJouee().getEffet() == "+4" && !sens_croissant)
    {
        if(num_joueur-1 < 0)
        {
            Joueurs[nb_joueurs-1].pioche_n_carte(d.tirerNCarte(4));
            demandeCouleur(listCouleur, d);
        }
        else
        {
            Joueurs[num_joueur_actuel-1].pioche_n_carte(d.tirerNCarte(4));
            demandeCouleur(listCouleur, d);
        }
    }

    else if (d.derniereCarteJouee().getEffet() == "C")
    {
        demandeCouleur(listCouleur, d);
    }
}

Joueur addJoueurs::operator()()
{
    ++i;
    cout << endl << "Joueur " << i << ", quel est votre pseudo ?";
    cin >> pseudo;
    return Joueur(pseudo);

}



void afficherJoueurs::operator()(Joueur j)
{
    cout << j.getPseudo()<<endl;
}