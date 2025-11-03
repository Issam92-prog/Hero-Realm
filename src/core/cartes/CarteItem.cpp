#include "cartes/CarteItem.hpp"
#include "Joueur/Joueur.hpp"
#include <iostream>
#include <limits>

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
    if (!joueur) {
        std::cerr << "❌ Erreur : Joueur invalide !" << std::endl;
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  🔨 ITEM JOUÉ                                          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n🔨 " << nom << std::endl;
    std::cout << "   " << getFactionIcon() << " " << getFactionNom() << std::endl;

    // ════════════════════════════════════════════════════════
    // 1. EFFETS PRINCIPAUX (toujours appliqués)
    // ════════════════════════════════════════════════════════

    std::cout << "\n🎯 Effets :" << std::endl;
    
    bool a_des_effets = false;

    if (or_genere > 0) {
        joueur->ajouterOr(or_genere);
        a_des_effets = true;
    }
    
    if (combat_genere > 0) {
        joueur->ajouterCombat(combat_genere);
        a_des_effets = true;
    }

    if (!a_des_effets) {
        std::cout << "   ℹ️  Aucun effet" << std::endl;
    }

    // ════════════════════════════════════════════════════════
    // 2. PROPOSITION DE SACRIFICE (si disponible)
    // ════════════════════════════════════════════════════════

    if (aEffetSacrifice()) {
        std::cout << "\n💀 SACRIFICE disponible !" << std::endl;
        std::cout << "   Cette carte peut être sacrifiée pour un effet bonus" << std::endl;
        
        // Afficher les effets du sacrifice
        std::cout << "\n   Effets du sacrifice :" << std::endl;
        if (sacrifice_or > 0) {
            std::cout << "      💰 +" << sacrifice_or << " or" << std::endl;
        }
        if (sacrifice_combat > 0) {
            std::cout << "      ⚔️  +" << sacrifice_combat << " combat" << std::endl;
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

    std::cout << "\n✅ " << nom << " a été joué(e) !" << std::endl;
    std::cout << "════════════════════════════════════════════════════════════" << std::endl;
}

void CarteItem::afficher() const {
    Carte::afficher();
    
    std::cout << "\n🎯 Effets:" << std::endl;
    if (or_genere > 0) {
        std::cout << "   💰 Or: +" << or_genere << std::endl;
    }
    if (combat_genere > 0) {
        std::cout << "   ⚔️  Combat: +" << combat_genere << std::endl;
    }
    
    if (aEffetSacrifice()) {
        std::cout << "\n💀 Effet sacrifice:" << std::endl;
        if (sacrifice_or > 0) {
            std::cout << "   💰 Or: +" << sacrifice_or << std::endl;
        }
        if (sacrifice_combat > 0) {
            std::cout << "   ⚔️  Combat: +" << sacrifice_combat << std::endl;
        }
    }
}

bool CarteItem::aEffetSacrifice() const {
    return (sacrifice_or > 0 || sacrifice_combat > 0);
}

void CarteItem::sacrifier(Joueur* joueur) {
    if (!joueur) return;
    
    if (!aEffetSacrifice()) {
        std::cout << "⚠️  Cet item n'a pas d'effet de sacrifice." << std::endl;
        return;
    }
    
    std::cout << "\n💀 SACRIFICE de " << nom << " !" << std::endl;
    std::cout << "   (Cette carte est retirée définitivement du jeu)" << std::endl;
    
    if (sacrifice_or > 0) {
        joueur->ajouterOr(sacrifice_or);
    }
    
    if (sacrifice_combat > 0) {
        joueur->ajouterCombat(sacrifice_combat);
    }
    
    std::cout << "   ✅ Effets du sacrifice appliqués !" << std::endl;
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