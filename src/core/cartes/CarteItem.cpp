#include "cartes/CarteItem.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>

CarteItem::CarteItem(int quantity, const std::string& nom, int cout, Faction faction, 
                     int or_val, int combat_val)
    : Carte(quantity, nom, cout, faction, ITEM),
      or_genere(or_val), combat_genere(combat_val),
      sacrifice_or(0), sacrifice_combat(0) {
}

CarteItem::~CarteItem() {
}

void CarteItem::setEffets(int or_val, int combat_val) {
    or_genere = or_val;
    combat_genere = combat_val;
}

void CarteItem::setEffetSacrifice(int or_val, int combat_val) {
    sacrifice_or = or_val;
    sacrifice_combat = combat_val;
}

void CarteItem::jouer(Joueur* joueur) {
    std::cout << "Joue l'item: " << nom << std::endl;
    
    if (or_genere > 0) {
        joueur->ajouterOr(or_genere);
        std::cout << "  + " << or_genere << " or" << std::endl;
    }
    if (combat_genere > 0) {
        joueur->ajouterCombat(combat_genere);
        std::cout << "  + " << combat_genere << " combat" << std::endl;
    }
}

void CarteItem::afficher() const {
    Carte::afficher();
    
    std::cout << "\nEffets:" << std::endl;
    if (or_genere > 0) {
        std::cout << "  Or: +" << or_genere << std::endl;
    }
    if (combat_genere > 0) {
        std::cout << "  Combat: +" << combat_genere << std::endl;
    }
    
    if (aEffetSacrifice()) {
        std::cout << "\nEffet sacrifice:" << std::endl;
        if (sacrifice_or > 0) {
            std::cout << "  Or: +" << sacrifice_or << std::endl;
        }
        if (sacrifice_combat > 0) {
            std::cout << "  Combat: +" << sacrifice_combat << std::endl;
        }
    }
}

bool CarteItem::aEffetSacrifice() const {
    return (sacrifice_or > 0 || sacrifice_combat > 0);
}

void CarteItem::sacrifier(Joueur* joueur) {
    if (!aEffetSacrifice()) {
        std::cout << "Cet item n'a pas d'effet de sacrifice." << std::endl;
        return;
    }
    
    std::cout << "Sacrifice " << nom << std::endl;
    
    if (sacrifice_or > 0) {
        joueur->ajouterOr(sacrifice_or);
        std::cout << "  + " << sacrifice_or << " or" << std::endl;
    }
    if (sacrifice_combat > 0) {
        joueur->ajouterCombat(sacrifice_combat);
        std::cout << "  + " << sacrifice_combat << " combat" << std::endl;
    }
}

int CarteItem::getOr() const {
    return or_genere;
}

int CarteItem::getCombat() const {
    return combat_genere;
}

int CarteItem::getSacrificeOr() const {
    return sacrifice_or;
}

int CarteItem::getSacrificeCombat() const {
    return sacrifice_combat;
}