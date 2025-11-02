#include "cartes/CarteAction.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>
#include <limits>

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
    if (!joueur) {
        std::cerr << "❌ Erreur : Joueur invalide !" << std::endl;
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  ⚡ ACTION JOUÉE                                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n⚡ " << nom << std::endl;
    std::cout << "   " << getFactionIcon() << " " << getFactionNom() << std::endl;

    // ════════════════════════════════════════════════════════
    // 1. EFFETS PRINCIPAUX (toujours activés)
    // ════════════════════════════════════════════════════════

    std::cout << "\n🎯 Effets principaux :" << std::endl;
    
    bool a_effet_principal = false;

    if (or_principal > 0) {
        joueur->ajouterOr(or_principal);
        a_effet_principal = true;
    }
    
    if (combat_principal > 0) {
        joueur->ajouterCombat(combat_principal);
        a_effet_principal = true;
    }
    
    if (soin_principal > 0) {
        joueur->soigner(soin_principal);
        a_effet_principal = true;
    }
    
    if (pioche_principal > 0) {
        std::cout << "   📚 Pioche " << pioche_principal << " carte(s)" << std::endl;
        for (int i = 0; i < pioche_principal; ++i) {
            joueur->piocher();
        }
        a_effet_principal = true;
    }

    if (!a_effet_principal) {
        std::cout << "   ℹ️  Aucun effet principal" << std::endl;
    }

    // ════════════════════════════════════════════════════════
    // 2. EFFETS ALLIÉS (si une autre carte de même faction a été jouée)
    // ════════════════════════════════════════════════════════

    if (aEffetAllie()) {
        // Vérifier si le joueur a joué une autre carte de la même faction ce tour
        bool allie_active = joueur->aJoueFaction(faction);
        
        if (allie_active) {
            std::cout << "\n🤝 Effet ALLIÉ activé ! (autre carte " << getFactionNom() << " jouée)" << std::endl;
            activerAllie(joueur);
        } else {
            std::cout << "\n💤 Effet ALLIÉ disponible (jouez une autre carte " << getFactionNom() << " pour l'activer)" << std::endl;
        }
    }

    // ════════════════════════════════════════════════════════
    // 3. CHOIX DU SACRIFICE (optionnel)
    // ════════════════════════════════════════════════════════

    if (aEffetSacrifice()) {
        std::cout << "\n💀 SACRIFICE disponible !" << std::endl;
        std::cout << "   Cette carte peut être sacrifiée pour un effet bonus" << std::endl;
        
        // Afficher les effets du sacrifice
        std::cout << "\n   Effets du sacrifice :" << std::endl;
        if (or_sacrifice > 0) {
            std::cout << "      💰 +" << or_sacrifice << " or" << std::endl;
        }
        if (combat_sacrifice > 0) {
            std::cout << "      ⚔️  +" << combat_sacrifice << " combat" << std::endl;
        }
        if (soin_sacrifice > 0) {
            std::cout << "      💚 +" << soin_sacrifice << " PV" << std::endl;
        }
        if (pioche_sacrifice > 0) {
            std::cout << "      📚 Pioche " << pioche_sacrifice << " carte(s)" << std::endl;
        }

        // Demander au joueur s'il veut sacrifier
        std::cout << "\n❓ Voulez-vous SACRIFIER cette carte ? (o/n) : ";
        std::string reponse;
        std::getline(std::cin, reponse);

        if (reponse == "o" || reponse == "O" || reponse == "oui" || reponse == "Oui") {
            sacrifier(joueur);
        } else {
            std::cout << "   ℹ️  Carte non sacrifiée (ira en défausse)" << std::endl;
        }
    }

    // ════════════════════════════════════════════════════════
    // RÉSUMÉ
    // ════════════════════════════════════════════════════════

    std::cout << "\n✅ " << nom << " a été jouée !" << std::endl;
    std::cout << "════════════════════════════════════════════════════════════" << std::endl;
}

void CarteAction::activerAllie(Joueur* joueur) {
    if (!joueur) return;

    std::cout << "   🤝 Activation des effets alliés :" << std::endl;

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
        for (int i = 0; i < pioche_allie; ++i) {
            joueur->piocher();
        }
    }
}

void CarteAction::sacrifier(Joueur* joueur) {
    if (!joueur) return;
    
    if (!a_effet_sacrifice) {
        std::cout << "⚠️  Cette carte n'a pas d'effet de sacrifice." << std::endl;
        return;
    }

    std::cout << "\n💀 SACRIFICE de " << nom << " !" << std::endl;
    std::cout << "   (Cette carte est retirée définitivement du jeu)" << std::endl;

    // Appliquer les effets du sacrifice
    if (or_sacrifice > 0) {
        joueur->ajouterOr(or_sacrifice);
    }
    
    if (combat_sacrifice > 0) {
        joueur->ajouterCombat(combat_sacrifice);
    }
    
    if (soin_sacrifice > 0) {
        joueur->soigner(soin_sacrifice);
    }
    
    if (pioche_sacrifice > 0) {
        std::cout << "   📚 Pioche " << pioche_sacrifice << " carte(s)" << std::endl;
        for (int i = 0; i < pioche_sacrifice; ++i) {
            joueur->piocher();
        }
    }

    std::cout << "   ✅ Effets du sacrifice appliqués !" << std::endl;
}

void CarteAction::afficher() const {
    Carte::afficher();
    
    std::cout << "\n🎯 Effets principaux:" << std::endl;
    if (or_principal > 0) std::cout << "   💰 Or: +" << or_principal << std::endl;
    if (combat_principal > 0) std::cout << "   ⚔️  Combat: +" << combat_principal << std::endl;
    if (soin_principal > 0) std::cout << "   💚 Soin: +" << soin_principal << std::endl;
    if (pioche_principal > 0) std::cout << "   📚 Pioche: +" << pioche_principal << std::endl;
    
    if (aEffetAllie()) {
        std::cout << "\n🤝 Effet allié:" << std::endl;
        if (or_allie > 0) std::cout << "   💰 Or: +" << or_allie << std::endl;
        if (combat_allie > 0) std::cout << "   ⚔️  Combat: +" << combat_allie << std::endl;
        if (soin_allie > 0) std::cout << "   💚 Soin: +" << soin_allie << std::endl;
        if (pioche_allie > 0) std::cout << "   📚 Pioche: +" << pioche_allie << std::endl;
    }
    
    if (aEffetSacrifice()) {
        std::cout << "\n💀 Effet sacrifice:" << std::endl;
        if (or_sacrifice > 0) std::cout << "   💰 Or: +" << or_sacrifice << std::endl;
        if (combat_sacrifice > 0) std::cout << "   ⚔️  Combat: +" << combat_sacrifice << std::endl;
        if (soin_sacrifice > 0) std::cout << "   💚 Soin: +" << soin_sacrifice << std::endl;
        if (pioche_sacrifice > 0) std::cout << "   📚 Pioche: +" << pioche_sacrifice << std::endl;
    }
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