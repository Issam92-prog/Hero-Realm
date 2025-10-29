#include "cartes/CarteItem.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>

CarteItem::CarteItem(int quantity, const std::string& nom, int cout, Faction faction, 
                     int or_val, int combat_val)
    : Carte(quantity, nom, cout, faction, ITEM),
      or_genere(or_val), combat_genere(combat_val),
      sacrifice_or(0), sacrifice_combat(0), sacrifice_sante(0), sacrifice_pioche(0) {
}

CarteItem::~CarteItem() {
}

void CarteItem::setEffets(int or_val, int combat_val) {
    or_genere = or_val;
    combat_genere = combat_val;
}

void CarteItem::setEffetSacrifice(int or_val, int combat_val, int sante_val, int pioche_val) {
    sacrifice_or = or_val;
    sacrifice_combat = combat_val;
    sacrifice_sante = sante_val;
    sacrifice_pioche = pioche_val;
}

void CarteItem::jouer(Joueur* joueur) {
    (void)joueur;
    std::cout << "Joue l'item: " << nom << std::endl;
    
    if (or_genere > 0) {
        std::cout << "  + " << or_genere << " or" << std::endl;
    }
    if (combat_genere > 0) {
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

int CarteItem::getSacrificeSante() const {
    return sacrifice_sante;
}

int CarteItem::getSacrificePioche() const {
    return sacrifice_pioche;
}