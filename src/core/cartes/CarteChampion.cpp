#include "cartes/CarteChampion.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>

// ════════════════════════════════════════════════════════
// CONSTRUCTEUR & DESTRUCTEUR
// ════════════════════════════════════════════════════════

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

// ════════════════════════════════════════════════════════
// SETTERS POUR EFFETS
// ════════════════════════════════════════════════════════

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

// ════════════════════════════════════════════════════════
// MÉTHODE PRINCIPALE : JOUER UN CHAMPION
// ════════════════════════════════════════════════════════

void CarteChampion::jouer(Joueur* joueur) {
    if (!joueur) {
        std::cerr << "❌ Erreur : Joueur invalide !" << std::endl;
        return;
    }

    // ════════════════════════════════════════════════════════
    // AFFICHAGE
    // ════════════════════════════════════════════════════════

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  👤 CHAMPION JOUÉ                                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n👤 " << nom << std::endl;
    std::cout << "   " << getFactionIcon() << " " << getFactionNom() << std::endl;
    std::cout << "   💪 Défense : " << defense << "/" << defense << std::endl;
    
    if (est_garde) {
        std::cout << "   🛡️  GARDE : Protège son propriétaire" << std::endl;
    }

    // ════════════════════════════════════════════════════════
    // 1. EFFETS PRINCIPAUX (quand le champion entre en jeu)
    // ════════════════════════════════════════════════════════

    if (aEffetPrincipal()) {
        std::cout << "\n🎯 Effets à la pose :" << std::endl;
        
        if (or_principal > 0) {
            joueur->ajouterOr(or_principal);
        }
        
        if (combat_principal > 0) {
            joueur->ajouterCombat(combat_principal);
        }
        
        if (soin_principal > 0) {
            joueur->soigner(soin_principal);
        }
        
        if (pioche_principal > 0) {
            std::cout << "   📚 Pioche " << pioche_principal << " carte(s)" << std::endl;
            joueur->piocher(pioche_principal);
        }
    } else {
        std::cout << "\n   ℹ️  Aucun effet immédiat à la pose" << std::endl;
    }

    // ════════════════════════════════════════════════════════
    // 2. ENREGISTRER la faction AVANT de vérifier les alliés
    // ════════════════════════════════════════════════════════
    
    if (faction != Faction::NONE) {
        joueur->enregistrerFactionJouee(faction);
    }

    // ════════════════════════════════════════════════════════
    // 3. VÉRIFIER LES ALLIÉS des champions DÉJÀ EN JEU
    // ════════════════════════════════════════════════════════
    
    if (faction != Faction::NONE) {
        auto& champions = joueur->zoneDeJeu().champions();
        for (auto* champion : champions) {
            if (champion && champion != this) {  // Ne pas se vérifier soi-même
                champion->verifierEtActiverAllie(joueur);
            }
        }
    }

    // ════════════════════════════════════════════════════════
    // 4. VÉRIFIER si CE champion peut activer son propre allié
    // ════════════════════════════════════════════════════════

    if (aEffetAllie()) {
        // L'effet allié s'active si au moins 2 cartes de la faction sont en jeu/jouées
        int nb_cartes_faction = joueur->compterCartesJoueesFaction(faction);
        
        if (nb_cartes_faction >= 2) {
            std::cout << "\n🤝 Effet ALLIÉ de " << nom << " activé !" << std::endl;
            activerAllie(joueur);
        } else {
            std::cout << "\n💤 Effet ALLIÉ disponible (jouez une autre carte " 
                      << getFactionNom() << " pour l'activer)" << std::endl;
        }
    }

    // ════════════════════════════════════════════════════════
    // 5. CAPACITÉ EXPEND (disponible tant que pas utilisée)
    // ════════════════════════════════════════════════════════

    if (aEffetExpend()) {
        std::cout << "\n⏸️  Capacité EXPEND disponible" << std::endl;
        std::cout << "   (Peut être utilisée une fois par tour)" << std::endl;
        
        // Afficher l'effet Expend
        std::cout << "   Effets Expend :" << std::endl;
        if (or_expend > 0) {
            std::cout << "      💰 +" << or_expend << " or" << std::endl;
        }
        if (combat_expend > 0) {
            std::cout << "      ⚔️  +" << combat_expend << " combat" << std::endl;
        }
        if (soin_expend > 0) {
            std::cout << "      💚 +" << soin_expend << " PV" << std::endl;
        }
        if (pioche_expend > 0) {
            std::cout << "      📚 Pioche " << pioche_expend << " carte(s)" << std::endl;
        }
    }

    // Le champion entre en jeu prêt (pas expended)
    est_expended = false;

    // ════════════════════════════════════════════════════════
    // RÉSUMÉ
    // ════════════════════════════════════════════════════════

    std::cout << "\n✅ " << nom << " entre en jeu !" << std::endl;
    std::cout << "   État : ⚡ PRÊT (peut utiliser ses capacités)" << std::endl;
    std::cout << "════════════════════════════════════════════════════════════" << std::endl;
}

// ════════════════════════════════════════════════════════
// UTILISER LA CAPACITÉ EXPEND
// ════════════════════════════════════════════════════════

void CarteChampion::utiliserExpend(Joueur* joueur) {
    if (!joueur) {
        std::cerr << "❌ Erreur : Joueur invalide !" << std::endl;
        return;
    }

    if (est_expended) {
        std::cout << "⚠️  " << nom << " a déjà utilisé sa capacité Expend ce tour." << std::endl;
        return;
    }
    
    if (!aEffetExpend()) {
        std::cout << "⚠️  " << nom << " n'a pas d'effet Expend." << std::endl;
        return;
    }
    
    std::cout << "\n⏸️  Activation de la capacité EXPEND de " << nom << " :" << std::endl;
    
    if (or_expend > 0) {
        joueur->ajouterOr(or_expend);
    }
    
    if (combat_expend > 0) {
        joueur->ajouterCombat(combat_expend);
    }
    
    if (soin_expend > 0) {
        joueur->soigner(soin_expend);
    }
    
    if (pioche_expend > 0) {
        std::cout << "   📚 Pioche " << pioche_expend << " carte(s)" << std::endl;
        joueur->piocher(pioche_expend);
    }
    
    est_expended = true;
    std::cout << "   ✅ " << nom << " est maintenant EXPENDED" << std::endl;
}

// ════════════════════════════════════════════════════════
// ACTIVER LES EFFETS ALLIÉS
// ════════════════════════════════════════════════════════

void CarteChampion::activerAllie(Joueur* joueur) {
    if (!joueur) return;
    
    if (!aEffetAllie()) {
        return;
    }
    
    std::cout << "   🤝 Activation des effets alliés de " << nom << " :" << std::endl;
    
    if (or_allie > 0) {
        joueur->ajouterOr(or_allie);
    }
    
    if (combat_allie > 0) {
        joueur->ajouterCombat(combat_allie);
    }
    
    if (soin_allie > 0) {
        joueur->soigner(soin_allie);
    }
    
    if (pioche_allie > 0) {
        std::cout << "      📚 Pioche " << pioche_allie << " carte(s)" << std::endl;
        joueur->piocher(pioche_allie);
    }
}

// ════════════════════════════════════════════════════════
// VÉRIFIER ET ACTIVER ALLIÉ (pour champions déjà en jeu)
// ════════════════════════════════════════════════════════

void CarteChampion::verifierEtActiverAllie(Joueur* joueur) {
    if (!joueur || !aEffetAllie()) {
        return;
    }
    
    // Vérifier si au moins 2 cartes de la même faction sont en jeu/jouées
    int nb_cartes_faction = joueur->compterCartesJoueesFaction(faction);
    
    if (nb_cartes_faction >= 2) {
        std::cout << "\n🤝 Effet ALLIÉ de " << nom << " (déjà en jeu) activé !" << std::endl;
        activerAllie(joueur);
    }
}

// ════════════════════════════════════════════════════════
// DÉGÂTS ET GESTION DE L'ÉTAT
// ════════════════════════════════════════════════════════

void CarteChampion::subirDegats(int degats) {
    if (degats <= 0) return;

    defense_actuelle -= degats;
    
    std::cout << "💥 " << nom << " subit " << degats << " dégâts" << std::endl;
    
    if (estVivant()) {
        std::cout << "   💪 Défense restante: " << defense_actuelle << "/" << defense << std::endl;
    } else {
        std::cout << "   💀 " << nom << " a été vaincu !" << std::endl;
    }
}

void CarteChampion::preparerPourNouveauTour() {
    est_expended = false;
}

void CarteChampion::reparer() {
    defense_actuelle = defense;
}

// ════════════════════════════════════════════════════════
// AFFICHAGE
// ════════════════════════════════════════════════════════

void CarteChampion::afficher() const {
    Carte::afficher();
    
    std::cout << "   💪 Défense: " << defense_actuelle << "/" << defense;
    if (est_garde) {
        std::cout << " 🛡️  [GARDE]";
    }
    std::cout << std::endl;
    
    if (est_expended) {
        std::cout << "   ⏸️  État: EXPENDED" << std::endl;
    } else {
        std::cout << "   ⚡ État: PRÊT" << std::endl;
    }
    
    if (aEffetPrincipal()) {
        std::cout << "\n   🎯 Effets à la pose:" << std::endl;
        if (or_principal > 0) std::cout << "      💰 Or: +" << or_principal << std::endl;
        if (combat_principal > 0) std::cout << "      ⚔️  Combat: +" << combat_principal << std::endl;
        if (soin_principal > 0) std::cout << "      💚 Soin: +" << soin_principal << std::endl;
        if (pioche_principal > 0) std::cout << "      📚 Pioche: +" << pioche_principal << std::endl;
    }
    
    if (aEffetExpend()) {
        std::cout << "\n   ⏸️  Effet Expend:" << std::endl;
        if (or_expend > 0) std::cout << "      💰 Or: +" << or_expend << std::endl;
        if (combat_expend > 0) std::cout << "      ⚔️  Combat: +" << combat_expend << std::endl;
        if (soin_expend > 0) std::cout << "      💚 Soin: +" << soin_expend << std::endl;
        if (pioche_expend > 0) std::cout << "      📚 Pioche: +" << pioche_expend << std::endl;
    }
    
    if (aEffetAllie()) {
        std::cout << "\n   🤝 Effet allié:" << std::endl;
        if (or_allie > 0) std::cout << "      💰 Or: +" << or_allie << std::endl;
        if (combat_allie > 0) std::cout << "      ⚔️  Combat: +" << combat_allie << std::endl;
        if (soin_allie > 0) std::cout << "      💚 Soin: +" << soin_allie << std::endl;
        if (pioche_allie > 0) std::cout << "      📚 Pioche: +" << pioche_allie << std::endl;
    }
}

// ════════════════════════════════════════════════════════
// GETTERS
// ════════════════════════════════════════════════════════

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

// Getters effets principaux
int CarteChampion::getOrPrincipal() const { return or_principal; }
int CarteChampion::getCombatPrincipal() const { return combat_principal; }
int CarteChampion::getSoinPrincipal() const { return soin_principal; }
int CarteChampion::getPiochePrincipal() const { return pioche_principal; }

// Getters effets Expend
int CarteChampion::getOrExpend() const { return or_expend; }
int CarteChampion::getCombatExpend() const { return combat_expend; }
int CarteChampion::getSoinExpend() const { return soin_expend; }
int CarteChampion::getPiocheExpend() const { return pioche_expend; }

// Getters effets alliés
int CarteChampion::getOrAllie() const { return or_allie; }
int CarteChampion::getCombatAllie() const { return combat_allie; }
int CarteChampion::getSoinAllie() const { return soin_allie; }
int CarteChampion::getPiocheAllie() const { return pioche_allie; }