#include "CarteAction.hpp"
#include "Joueur.hpp"
#include <iostream>

CarteAction::CarteAction(int quantity, const std::string& nom, int cout, Faction faction)
    : Carte(quantity, nom, cout, faction, ACTION),
      or_principal(0), combat_principal(0), soin_principal(0), pioche_principal(0),
      or_allie(0), combat_allie(0), soin_allie(0), pioche_allie(0),
      or_sacrifice(0), combat_sacrifice(0), soin_sacrifice(0), pioche_sacrifice(0),
      a_effet_sacrifice(false) {
}

CarteAction::~CarteAction() {
}

void CarteAction::setEffetPrincipal(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_principal = or_val;
    combat_principal = combat_val;
    soin_principal = soin_val;
    pioche_principal = pioche_val;
}

void CarteAction::setEffetAllie(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_allie = or_val;
    combat_allie = combat_val;
    soin_allie = soin_val;
    pioche_allie = pioche_val;
}

void CarteAction::setEffetSacrifice(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_sacrifice = or_val;
    combat_sacrifice = combat_val;
    soin_sacrifice = soin_val;
    pioche_sacrifice = pioche_val;
    a_effet_sacrifice = (or_val > 0 || combat_val > 0 || soin_val > 0 || pioche_val > 0);
}

void CarteAction::jouer(Joueur* joueur) {
    // TODO: Implémenter la logique de jeu
    std::cout << "Joue la carte action: " << nom << std::endl;
    
    // Appliquer les effets principaux
    if (or_principal > 0) {
        std::cout << "  + " << or_principal << " or" << std::endl;
    }
    if (combat_principal > 0) {
        std::cout << "  + " << combat_principal << " combat" << std::endl;
    }
    if (soin_principal > 0) {
        std::cout << "  + " << soin_principal << " santé" << std::endl;
    }
    if (pioche_principal > 0) {
        std::cout << "  Pioche " << pioche_principal << " carte(s)" << std::endl;
    }
}

void CarteAction::afficher() const {
    Carte::afficher();
    
    std::cout << "\nEffets principaux:" << std::endl;
    if (or_principal > 0) std::cout << "  Or: +" << or_principal << std::endl;
    if (combat_principal > 0) std::cout << "  Combat: +" << combat_principal << std::endl;
    if (soin_principal > 0) std::cout << "  Soin: +" << soin_principal << std::endl;
    if (pioche_principal > 0) std::cout << "  Pioche: +" << pioche_principal << std::endl;
    
    if (aEffetAllie()) {
        std::cout << "\nEffet allié:" << std::endl;
        if (or_allie > 0) std::cout << "  Or: +" << or_allie << std::endl;
        if (combat_allie > 0) std::cout << "  Combat: +" << combat_allie << std::endl;
        if (soin_allie > 0) std::cout << "  Soin: +" << soin_allie << std::endl;
        if (pioche_allie > 0) std::cout << "  Pioche: +" << pioche_allie << std::endl;
    }
    
    if (aEffetSacrifice()) {
        std::cout << "\nEffet sacrifice:" << std::endl;
        if (or_sacrifice > 0) std::cout << "  Or: +" << or_sacrifice << std::endl;
        if (combat_sacrifice > 0) std::cout << "  Combat: +" << combat_sacrifice << std::endl;
        if (soin_sacrifice > 0) std::cout << "  Soin: +" << soin_sacrifice << std::endl;
        if (pioche_sacrifice > 0) std::cout << "  Pioche: +" << pioche_sacrifice << std::endl;
    }
}

void CarteAction::activerAllie(Joueur* joueur) {
    std::cout << "Active l'effet allié de " << nom << std::endl;
    // TODO: Implémenter
}

void CarteAction::sacrifier(Joueur* joueur) {
    if (!a_effet_sacrifice) {
        std::cout << "Cette carte n'a pas d'effet de sacrifice." << std::endl;
        return;
    }
    std::cout << "Sacrifice " << nom << std::endl;
    // TODO: Implémenter
}

bool CarteAction::aEffetAllie() const {
    return (or_allie > 0 || combat_allie > 0 || soin_allie > 0 || pioche_allie > 0);
}

bool CarteAction::aEffetSacrifice() const {
    return a_effet_sacrifice;
}

int CarteAction::getOrPrincipal() const { return or_principal; }
int CarteAction::getCombatPrincipal() const { return combat_principal; }
int CarteAction::getSoinPrincipal() const { return soin_principal; }
int CarteAction::getPiochePrincipal() const { return pioche_principal; }