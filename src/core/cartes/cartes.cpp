#include "cartes/cartes.hpp"
#include "Joueur/Joueur.hpp"

void Carte::jouer(Joueur* joueur) {
    if (or_ > 0) joueur->ajouterOr(or_);
    if (combat_ > 0) joueur->ajouterCombat(combat_);
}