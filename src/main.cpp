#include <iostream>
#include <memory>
#include <iomanip>
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/cartes.hpp"

using namespace std;

// Fonction utilitaire pour afficher la main d'un joueur
void afficherMain(const Joueur* j) {
    cout << "\nMain de " << j->nom() << ":\n";
    const auto& main = j->main();
    for (size_t i = 0; i < main.size(); ++i) {
        cout << "[" << i + 1 << "] " << *main[i] << "\n";
    }
    cout << "\n";
}

int main() {
    Plateau p;
    p.ajouterJoueur(make_unique<Joueur>(1, "issam", 50));
    p.ajouterJoueur(make_unique<Joueur>(2, "alex", 50));
    p.demarrer();

    cout << "=== Hero-Realms ===\n";
    cout << "Commandes : [j N]ouer carte N, [a]ttaquer, [m]ain, [p]asser, [q]uitter\n\n";

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

        string input;
        if (!(cin >> input)) break;

        // Gestion des commandes numériques (1,2,3...) pour jouer des cartes
        if (isdigit(input[0])) {
            int index = stoi(input) - 1;  // -1 car l'affichage commence à 1
            if (index >= 0 && (size_t)index < j->main().size()) {
                auto& main = j->main();
                Carte* carte = main[index];
                cout << "\nJoue " << *carte;
                carte->jouer(j);
                main.erase(main.begin() + index);
                
                // Afficher les ressources après avoir joué la carte
                cout << " → Or: " << j->orTour() << " | Combat: " << j->combatTour() << "\n";
            } else {
                cout << "Numéro de carte invalide.\n";
            }
            continue; // Continue le tour avec la prochaine entrée
        }

        // Autres commandes
        char cmd = input[0];
        if (cmd == 'q') break;
        else if (cmd == 'm') {
            afficherMain(j);
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
