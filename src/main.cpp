#include <iostream>
#include <memory>
#include <iomanip>
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "zone/marche.hpp"

using namespace std;

// Fonction utilitaire pour afficher la main d'un joueur
void afficherMain(const Joueur* j) {
    cout << "\nMain de " << j->nom() << ":\n";
    const auto& main = j->main();
    for (size_t i = 0; i < main.size(); ++i) {
        cout << "[" << i + 1 << "] ";
        main[i]->afficher();
    }
    cout << "\n";
}

int main() {
    Plateau p;
    p.ajouterJoueur(make_unique<Joueur>(1, "issam", 50));
    p.ajouterJoueur(make_unique<Joueur>(2, "alex", 50));
    p.demarrer();

    cout << "=== Hero-Realms ===\n";
    cout << "Commandes : [j N]ouer carte N, [a]ttaquer, [m]ain, [b N]acheter carte N\n";
    cout << "           [v]oir marché, [p]asser, [q]uitter\n\n";

    while (p.estDemarree() && !p.estTerminee()) {
        auto* j = p.joueurCourant();
        auto* adv = p.adversaire();
        if (!j || !adv) break;

        cout << "\nTour de " << j->nom()
             << " | PV: " << j->pv()
             << " | Or: " << j->orTour()
             << " | Combat: " << j->combatTour()
             << "\nAdversaire: " << adv->nom() << " (" << adv->pv() << " PV)\n> ";

        // Afficher la main au début de chaque tour
        afficherMain(j);
        cout << "Or: " << j->orTour() << " | Combat: " << j->combatTour() << "\n> ";

        char cmd;
        if (!(cin >> cmd)) break;

        if (cmd == 'q') break;
        else if (cmd == 'm') {
            afficherMain(j);
        }
        else if (cmd == 'v') {
            p.marche().afficher();
        }
        else if (cmd == 'b') {
            int index;
            cin >> index;
            index--; // Convertir en 0-based
            
            auto& marche = p.marche();
            if (index >= 0 && (size_t)index < marche.nbCartes()) {
                Carte* carte = marche.cartesDisponibles()[index];
                if (j->orTour() >= carte->getCout()) {
                    j->ajouterOr(-carte->getCout());  // Payer le coût
                    carte = marche.acheterCarte(index);
                    j->defausse().push_back(carte);
                    cout << "Acheté ";
                    carte->afficher();
                    cout << " (Or restant: " << j->orTour() << ")\n";
                } else {
                    cout << "Pas assez d'or pour acheter cette carte!\n";
                }
            } else {
                cout << "Numéro de carte invalide.\n";
            }
        }
        else if (cmd == 'j') {
            int index;
            cin >> index;  // Lire le numéro de la carte
            index--; // Convertir en 0-based index
            
            auto& main = j->main();
            if (index >= 0 && (size_t)index < main.size()) {
                Carte* carte = main[index];
                cout << "\nJoue ";
                carte->afficher();
                carte->jouer(j);
                main.erase(main.begin() + index);
                
                // Afficher les ressources après avoir joué la carte
                cout << " → Or: " << j->orTour() << " | Combat: " << j->combatTour() << "\n";
                
                // Réafficher la main mise à jour
                afficherMain(j);
            } else {
                cout << "Numéro de carte invalide.\n";
            }
        }
        else if (cmd == 'a') {
            int degats = j->combatTour();
            if (degats > 0) {
                adv->subirDegats(degats);
                cout << j->nom() << " inflige " << degats << " dégâts à " << adv->nom()
                     << " (PV restants : " << adv->pv() << ")\n";
                j->ajouterCombat(-degats);  // Consomme les points de combat
                if (adv->estMort()) {
                    cout << adv->nom() << " est K.O. — "
                         << j->nom() << " gagne !\n";
                    break;
                }
            } else {
                cout << "Pas de points de combat disponibles.\n";
            }
        }
        else if (cmd == 'p') {
            p.finDeTour();
        }
        else {
            cout << "Commande inconnue. Utilisez:\n"
                 << "  j N : jouer la carte N de votre main\n"
                 << "  m   : voir votre main\n"
                 << "  a   : attaquer avec vos points de combat\n"
                 << "  p   : passer votre tour\n"
                 << "  q   : quitter\n";
        }
    }

    cout << "Fin de la partie.\n";
    return 0;
}
