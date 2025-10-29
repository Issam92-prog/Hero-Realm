#include "cartes/CarteChampion.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>

CarteChampion::CarteChampion(int quantity, const std::string& nom, int cout, 
                             Faction faction, int defense, bool garde)
    : Carte(quantity, nom, cout, faction, CHAMPION),
      defense(defense), defense_actuelle(defense), est_garde(garde), est_expended(false),
      or_principal(0), combat_principal(0), soin_principal(0), pioche_principal(0),
      or_expend(0), combat_expend(0), soin_expend(0), pioche_expend(0),
      or_allie(0), combat_allie(0), soin_allie(0), pioche_allie(0) {
}

CarteChampion::~CarteChampion() {
}

void CarteChampion::setEffetPrincipal(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_principal = or_val;
    combat_principal = combat_val;
    soin_principal = soin_val;
    pioche_principal = pioche_val;
}

void CarteChampion::setEffetExpend(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_expend = or_val;
    combat_expend = combat_val;
    soin_expend = soin_val;
    pioche_expend = pioche_val;
}

void CarteChampion::setEffetAllie(int or_val, int combat_val, int soin_val, int pioche_val) {
    or_allie = or_val;
    combat_allie = combat_val;
    soin_allie = soin_val;
    pioche_allie = pioche_val;
}

void CarteChampion::jouer(Joueur* joueur) {
    (void)joueur; // Pour éviter le warning "unused parameter"
    std::cout << "Pose le champion: " << nom << " (Défense: " << defense << ")";
    if (est_garde) {
        std::cout << " [GARDE]";
    }
    std::cout << std::endl;
    
    // Appliquer les effets principaux à la pose
    if (aEffetPrincipal()) {
        std::cout << "  Effets à la pose:" << std::endl;
        if (or_principal > 0) {
            std::cout << "    + " << or_principal << " or" << std::endl;
        }
        if (combat_principal > 0) {
            std::cout << "    + " << combat_principal << " combat" << std::endl;
        }
        if (soin_principal > 0) {
            std::cout << "    + " << soin_principal << " santé" << std::endl;
        }
        if (pioche_principal > 0) {
            std::cout << "    Pioche " << pioche_principal << " carte(s)" << std::endl;
        }
    }
    
    // Le champion est maintenant prêt pour être utilisé (pas expended)
    est_expended = false;
}

void CarteChampion::utiliserExpend(Joueur* joueur) {
    if (est_expended) {
        std::cout << nom << " a déjà été utilisé ce tour." << std::endl;
        return;
    }
    
    if (!aEffetExpend()) {
        std::cout << nom << " n'a pas d'effet Expend." << std::endl;
        return;
    }
    
    std::cout << "Active Expend de " << nom << ":" << std::endl;
    if (or_expend > 0) {
        std::cout << "  + " << or_expend << " or" << std::endl;
    }
    if (combat_expend > 0) {
        std::cout << "  + " << combat_expend << " combat" << std::endl;
    }
    if (soin_expend > 0) {
        std::cout << "  + " << soin_expend << " santé" << std::endl;
    }
    if (pioche_expend > 0) {
        std::cout << "  Pioche " << pioche_expend << " carte(s)" << std::endl;
    }
    
    est_expended = true;
}

void CarteChampion::activerAllie(Joueur* joueur) {
    if (!aEffetAllie()) {
        return;
    }
    
    std::cout << "Active l'effet allié de " << nom << ":" << std::endl;
    if (or_allie > 0) {
        std::cout << "  + " << or_allie << " or" << std::endl;
    }
    if (combat_allie > 0) {
        std::cout << "  + " << combat_allie << " combat" << std::endl;
    }
    if (soin_allie > 0) {
        std::cout << "  + " << soin_allie << " santé" << std::endl;
    }
    if (pioche_allie > 0) {
        std::cout << "  Pioche " << pioche_allie << " carte(s)" << std::endl;
    }
}

void CarteChampion::subirDegats(int degats) {
    defense_actuelle -= degats;
    std::cout << nom << " subit " << degats << " dégâts. ";
    
    if (estVivant()) {
        std::cout << "Défense restante: " << defense_actuelle << std::endl;
    } else {
        std::cout << "Le champion est vaincu!" << std::endl;
    }
}

void CarteChampion::preparerPourNouveauTour() {
    est_expended = false;
}

void CarteChampion::reparer() {
    defense_actuelle = defense;
}

void CarteChampion::afficher() const {
    Carte::afficher();
    
    std::cout << "Défense: " << defense;
    if (est_garde) {
        std::cout << " [GARDE]";
    }
    std::cout << std::endl;
    
    if (aEffetPrincipal()) {
        std::cout << "\nEffets à la pose:" << std::endl;
        if (or_principal > 0) std::cout << "  Or: +" << or_principal << std::endl;
        if (combat_principal > 0) std::cout << "  Combat: +" << combat_principal << std::endl;
        if (soin_principal > 0) std::cout << "  Soin: +" << soin_principal << std::endl;
        if (pioche_principal > 0) std::cout << "  Pioche: +" << pioche_principal << std::endl;
    }
    
    if (aEffetExpend()) {
        std::cout << "\nEffet Expend:" << std::endl;
        if (or_expend > 0) std::cout << "  Or: +" << or_expend << std::endl;
        if (combat_expend > 0) std::cout << "  Combat: +" << combat_expend << std::endl;
        if (soin_expend > 0) std::cout << "  Soin: +" << soin_expend << std::endl;
        if (pioche_expend > 0) std::cout << "  Pioche: +" << pioche_expend << std::endl;
    }
    
    if (aEffetAllie()) {
        std::cout << "\nEffet allié:" << std::endl;
        if (or_allie > 0) std::cout << "  Or: +" << or_allie << std::endl;
        if (combat_allie > 0) std::cout << "  Combat: +" << combat_allie << std::endl;
        if (soin_allie > 0) std::cout << "  Soin: +" << soin_allie << std::endl;
        if (pioche_allie > 0) std::cout << "  Pioche: +" << pioche_allie << std::endl;
    }
}

int CarteChampion::getDefense() const {
    return defense;
}

int CarteChampion::getDefenseActuelle() const {
    return defense_actuelle;
}

bool CarteChampion::estGarde() const {
    return est_garde;
}

bool CarteChampion::estExpended() const {
    return est_expended;
}

bool CarteChampion::estVivant() const {
    return defense_actuelle > 0;
}

bool CarteChampion::aEffetExpend() const {
    return (or_expend > 0 || combat_expend > 0 || soin_expend > 0 || pioche_expend > 0);
}

bool CarteChampion::aEffetAllie() const {
    return (or_allie > 0 || combat_allie > 0 || soin_allie > 0 || pioche_allie > 0);
}

bool CarteChampion::aEffetPrincipal() const {
    return (or_principal > 0 || combat_principal > 0 || soin_principal > 0 || pioche_principal > 0);
}
