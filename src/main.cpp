#include <iostream>
#include <memory>
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"

using namespace std;

int main() {
    Plateau p;
    p.ajouterJoueur(make_unique<Joueur>(1, "issam", 50));
    p.ajouterJoueur(make_unique<Joueur>(2, "alex", 50));
    p.demarrer();

    cout << "=== Mini Hero-Realms ===\n";
    cout << "Commandes : [a]ttaque 5 dmg, [p]asse, [q]uitte\n\n";

    while (p.estDemarree() && !p.estTerminee()) {
        auto* j = p.joueurCourant();
        auto* adv = p.adversaire();
        if (!j || !adv) break;

        cout << "Tour de " << j->nom()
             << " | PV: " << j->pv()
             << "  (Adv: " << adv->nom() << " = " << adv->pv() << " PV)\n> ";

        char cmd;
        if (!(cin >> cmd)) break;

        if (cmd == 'q') break;
        else if (cmd == 'a') {
            adv->subirDegats(5);
            cout << j->nom() << " inflige 5 dégâts à " << adv->nom()
                 << " (PV adv = " << adv->pv() << ")\n";
            if (adv->estMort()) {
                cout << adv->nom() << " est K.O. — "
                     << j->nom() << " gagne !\n";
                break;
            }
            p.finDeTour();
        } else if (cmd == 'p') {
            p.finDeTour();
        } else {
            cout << "Commande inconnue.\n";
        }
    }

    cout << "Fin de la partie.\n";
    return 0;
}
