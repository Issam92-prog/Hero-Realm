#include "effets/EffetAction.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/CarteChampion.hpp"
#include <iostream>
#include <limits>

// ════════════════════════════════════════════════════════
// CALCULS DYNAMIQUES
// ════════════════════════════════════════════════════════

void EffetAction::bonusCombatParChampion(Joueur* joueur, int multiplicateur) {
    if (!joueur) return;
    
    // Compter TOUS les champions en jeu (toutes factions confondues)
    int nb_champions = 0;
    
    for (const auto* champion : joueur->zoneDeJeu().champions()) {
        if (champion) {
            nb_champions++;
        }
    }
    
    int bonus = nb_champions * multiplicateur;
    
    if (bonus > 0) {
        joueur->ajouterCombat(bonus);
        std::cout << "   ✨ Bonus : +" << bonus << " combat (" << nb_champions 
                  << " champion(s) × " << multiplicateur << ")" << std::endl;
    } else {
        std::cout << "   ℹ️  Aucun champion en jeu, pas de bonus" << std::endl;
    }
}

void EffetAction::bonusSanteParChampion(Joueur* joueur, int multiplicateur) {
    if (!joueur) return;
    
    // Compter TOUS les champions en jeu (toutes factions confondues)
    int nb_champions = 0;
    
    for (const auto* champion : joueur->zoneDeJeu().champions()) {
        if (champion) {
            nb_champions++;
        }
    }
    
    int bonus = nb_champions * multiplicateur;
    
    if (bonus > 0) {
        joueur->soigner(bonus);
        std::cout << "   ✨ Bonus : +" << bonus << " santé (" << nb_champions 
                  << " champion(s) × " << multiplicateur << ")" << std::endl;
    } else {
        std::cout << "   ℹ️  Aucun champion en jeu, pas de bonus" << std::endl;
    }
}


void EffetAction::bonusOrParChampion(Joueur* joueur, int multiplicateur) {
    if (!joueur) return;
    
    int nb_champions = joueur->zoneDeJeu().taille();
    int bonus = nb_champions * multiplicateur;
    
    if (bonus > 0) {
        joueur->ajouterOr(bonus);
        std::cout << "   ✨ Bonus : +" << bonus << " or (" << nb_champions 
                  << " champion(s) × " << multiplicateur << ")" << std::endl;
    } else {
        std::cout << "   ℹ️  Aucun champion en jeu, pas de bonus" << std::endl;
    }
}

// ════════════════════════════════════════════════════════
// ACTIONS SPÉCIALES
// ════════════════════════════════════════════════════════

void EffetAction::preparerChampion(Joueur* joueur, Game* /*game*/) {
    if (!joueur) return;
    
    auto& champions = joueur->zoneDeJeu().champions();
    
    if (champions.empty()) {
        std::cout << "   ℹ️  Aucun champion en jeu" << std::endl;
        return;
    }
    
    // Trouver les champions expended
    std::vector<CarteChampion*> expended_champions;
    for (auto* champion : champions) {
        if (champion && champion->estExpended()) {
            expended_champions.push_back(champion);
        }
    }
    
    if (expended_champions.empty()) {
        std::cout << "   ℹ️  Aucun champion expended à préparer" << std::endl;
        return;
    }
    
    // Afficher les champions expended
    std::cout << "\n   ⏸️  Champions expended :" << std::endl;
    for (size_t i = 0; i < expended_champions.size(); ++i) {
        std::cout << "      [" << (i+1) << "] " << expended_champions[i]->getNom() << std::endl;
    }
    
    // Choisir un champion à préparer
    std::cout << "\n   Quel champion voulez-vous préparer ? (1-" << expended_champions.size() << ") : ";
    int choix;
    std::cin >> choix;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix > 0 && choix <= static_cast<int>(expended_champions.size())) {
        CarteChampion* champion = expended_champions[choix - 1];
        champion->reparer();
        std::cout << "   ✅ " << champion->getNom() << " est maintenant prêt !" << std::endl;
    } else {
        std::cout << "   ⚠️  Choix invalide" << std::endl;
    }
}

void EffetAction::assommerChampion(Joueur* /*attaquant*/, Game* /*game*/) {
    std::cout << "   ⚠️  Effet 'Assommer champion' non encore implémenté" << std::endl;
    std::cout << "      (Nécessite l'accès à la classe Jeu)" << std::endl;
}

void EffetAction::defausserCarteAdverse(Joueur* /*attaquant*/, Game* /*game*/) {
    std::cout << "   ⚠️  Effet 'Défausser carte adverse' non encore implémenté" << std::endl;
    std::cout << "      (Nécessite l'accès à la classe Jeu)" << std::endl;
}

void EffetAction::sacrifierAutreCarte(Joueur* joueur, Game* /*game*/) {
    if (!joueur) return;
    
    // Collecter toutes les cartes sacrifiables (main + défausse)
    std::vector<Carte*> cartes_sacrifiables;
    std::vector<std::string> sources;
    
    // Cartes de la main
    for (size_t i = 0; i < joueur->main().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->main().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("main");
        }
    }
    
    // Cartes de la défausse
    for (size_t i = 0; i < joueur->defausse().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->defausse().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("défausse");
        }
    }
    
    if (cartes_sacrifiables.empty()) {
        std::cout << "   ℹ️  Aucune carte à sacrifier" << std::endl;
        return;
    }
    
    // Proposer de sacrifier
    std::cout << "\n   💀 Voulez-vous sacrifier une carte ? (o/n) : ";
    std::string reponse;
    std::getline(std::cin, reponse);
    
    if (reponse != "o" && reponse != "O" && reponse != "oui") {
        std::cout << "   ℹ️  Aucune carte sacrifiée" << std::endl;
        return;
    }
    
    // Afficher les cartes
    std::cout << "\n   Cartes disponibles :" << std::endl;
    for (size_t i = 0; i < cartes_sacrifiables.size(); ++i) {
        std::cout << "      [" << (i+1) << "] " << cartes_sacrifiables[i]->getNom() 
                  << " (" << sources[i] << ")" << std::endl;
    }
    
    // Choisir une carte
    std::cout << "\n   Carte à sacrifier (1-" << cartes_sacrifiables.size() << ") : ";
    int choix;
    std::cin >> choix;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix > 0 && choix <= static_cast<int>(cartes_sacrifiables.size())) {
        Carte* carte = cartes_sacrifiables[choix - 1];
        std::string source = sources[choix - 1];
        
        // Retirer de la source
        if (source == "main") {
            for (size_t i = 0; i < joueur->main().taille(); ++i) {
                if (joueur->main().getCarte(i) == carte) {
                    joueur->main().retirerCarte(i);
                    break;
                }
            }
        } else {
            joueur->defausse().retirerCarte(carte);
        }
        
        // Ajouter à la zone de sacrifice
        joueur->sacrifice().ajouterCarte(carte);
        std::cout << "   💀 " << carte->getNom() << " a été sacrifiée !" << std::endl;
    } else {
        std::cout << "   ⚠️  Choix invalide" << std::endl;
    }
}

// ════════════════════════════════════════════════════════
// MANIPULATION DE PILES
// ════════════════════════════════════════════════════════

void EffetAction::defausseSurDeck(Joueur* joueur, Game* /*game*/) {
    if (!joueur) return;
    
    if (joueur->defausse().estVide()) {
        std::cout << "   ℹ️  Défausse vide, aucune carte à placer" << std::endl;
        return;
    }
    
    // Proposer de placer une carte
    std::cout << "\n   🗑️  Voulez-vous placer une carte de votre défausse sur votre deck ? (o/n) : ";
    std::string reponse;
    std::getline(std::cin, reponse);
    
    if (reponse != "o" && reponse != "O" && reponse != "oui") {
        std::cout << "   ℹ️  Aucune carte déplacée" << std::endl;
        return;
    }
    
    // Afficher la défausse
    std::cout << "\n   Cartes dans la défausse :" << std::endl;
    joueur->defausse().afficher();
    
    // Choisir une carte
    std::cout << "\n   Carte à placer sur le deck (1-" << joueur->defausse().taille() << ") : ";
    int choix;
    std::cin >> choix;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix > 0 && choix <= static_cast<int>(joueur->defausse().taille())) {
        Carte* carte = const_cast<Carte*>(joueur->defausse().getCarte(choix - 1));
        joueur->defausse().retirerCarte(carte);
        joueur->pioche().ajouterDessus(carte);
        
        std::cout << "   ✅ " << carte->getNom() << " placée sur le dessus du deck !" << std::endl;
    } else {
        std::cout << "   ⚠️  Choix invalide" << std::endl;
    }
}

// ════════════════════════════════════════════════════════
// FLAGS TEMPORAIRES
// ════════════════════════════════════════════════════════

void EffetAction::prochaineActionSurDeck(Joueur* joueur) {
    if (!joueur) return;
    std::cout << "   📌 La prochaine carte Action achetée ira sur votre deck !" << std::endl;
    std::cout << "      ⚠️  (Flag non encore implémenté dans Joueur)" << std::endl;
}

void EffetAction::prochaineCarteEnMain(Joueur* joueur) {
    if (!joueur) return;
    std::cout << "   📌 La prochaine carte achetée ira directement dans votre main !" << std::endl;
    std::cout << "      ⚠️  (Flag non encore implémenté dans Joueur)" << std::endl;
}

void EffetAction::prochainChampionSurDeck(Joueur* joueur) {
    if (!joueur) return;
    std::cout << "   📌 Le prochain Champion acheté ira sur votre deck !" << std::endl;
    std::cout << "      ⚠️  (Flag non encore implémenté dans Joueur)" << std::endl;
}

// ════════════════════════════════════════════════════════
// CHOIX CONDITIONNELS
// ════════════════════════════════════════════════════════

void EffetAction::piocherPuisDefausser(Joueur* joueur, Game* /*game*/) {
    if (!joueur) return;
    
    std::cout << "\n   ❓ Voulez-vous piocher une carte ?" << std::endl;
    std::cout << "      (Si oui, vous devrez défausser une carte)" << std::endl;
    std::cout << "      [o/n] : ";
    
    std::string reponse;
    std::getline(std::cin, reponse);
    
    if (reponse == "o" || reponse == "O" || reponse == "oui" || reponse == "Oui") {
        joueur->piocher();
        std::cout << "      📚 Vous piochez 1 carte" << std::endl;
        
        if (joueur->main().taille() > 0) {
            std::cout << "\n      🗑️  Choisissez une carte à défausser :" << std::endl;
            joueur->afficherMain();
            
            std::cout << "\n      Carte (1-" << joueur->main().taille() << ") : ";
            int index;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (index > 0 && index <= static_cast<int>(joueur->main().taille())) {
                Carte* carte = const_cast<Carte*>(joueur->main().getCarte(index - 1));
                joueur->main().retirerCarte(index - 1);
                joueur->defausse().ajouterCarte(carte);
                std::cout << "      ✅ " << carte->getNom() << " défaussée" << std::endl;
            } else {
                std::cout << "      ⚠️  Index invalide" << std::endl;
            }
        }
    } else {
        std::cout << "      ℹ️  Vous choisissez de ne pas piocher" << std::endl;
    }
}

void EffetAction::piocherEtDefausserVariable(Joueur* joueur, int max, Game* /*game*/) {
    if (!joueur) return;
    
    std::cout << "\n   ❓ Combien de cartes voulez-vous piocher (0-" << max << ") ?" << std::endl;
    std::cout << "      (Vous devrez défausser autant de cartes)" << std::endl;
    std::cout << "      Choix : ";
    
    int nb_cartes;
    std::cin >> nb_cartes;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (nb_cartes < 0 || nb_cartes > max) {
        std::cout << "      ⚠️  Choix invalide" << std::endl;
        return;
    }
    
    if (nb_cartes == 0) {
        std::cout << "      ℹ️  Vous choisissez de ne pas piocher" << std::endl;
        return;
    }
    
    for (int i = 0; i < nb_cartes; ++i) {
        joueur->piocher();
    }
    std::cout << "      📚 Vous piochez " << nb_cartes << " carte(s)" << std::endl;
    
    for (int i = 0; i < nb_cartes; ++i) {
        if (joueur->main().taille() > 0) {
            std::cout << "\n      🗑️  Carte " << (i+1) << "/" << nb_cartes << " à défausser :" << std::endl;
            joueur->afficherMain();
            
            std::cout << "\n      Carte (1-" << joueur->main().taille() << ") : ";
            int index;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (index > 0 && index <= static_cast<int>(joueur->main().taille())) {
                Carte* carte = const_cast<Carte*>(joueur->main().getCarte(index - 1));
                joueur->main().retirerCarte(index - 1);
                joueur->defausse().ajouterCarte(carte);
                std::cout << "      ✅ " << carte->getNom() << " défaussée" << std::endl;
            }
        }
    }
}

// ════════════════════════════════════════════════════════
// EFFETS DE ZONE (AOE)
// ════════════════════════════════════════════════════════

void EffetAction::degatsDeZone(Joueur* /*attaquant*/, int /*degats*/, Game* /*game*/) {
    std::cout << "   ⚠️  Effet 'Dégâts de zone' non encore implémenté" << std::endl;
    std::cout << "      (Nécessite l'accès à la classe Jeu)" << std::endl;
}