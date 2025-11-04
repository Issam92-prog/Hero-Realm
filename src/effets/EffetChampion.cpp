#include "effets/EffetChampion.hpp"
#include "Joueur/Joueur.hpp"
#include "Jeu.hpp"
#include "cartes/CarteChampion.hpp"
#include <iostream>
#include <limits>

// ════════════════════════════════════════════════════════
// EFFETS DE PIOCHE CONDITIONNELS (ALLY) - EXISTANTS
// ════════════════════════════════════════════════════════

void EffetChampion::cronBerserkerAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   🌿 Effet ALLIÉ Wild : Pioche 1 carte" << std::endl;
    joueur->piocher(1);
}

void EffetChampion::grakStormGiantAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   ⚡ Effet ALLIÉ : Pioche 1 carte, puis défausse 1 carte" << std::endl;
    
    // Piocher une carte
    joueur->piocher(1);
    
    // Défausser une carte de la main
    auto& main = joueur->main().cartes();
    
    if (main.empty()) {
        std::cout << "   ℹ️  Aucune carte en main à défausser" << std::endl;
        return;
    }
    
    std::cout << "\n📋 Choisissez une carte à défausser :" << std::endl;
    for (size_t i = 0; i < main.size(); ++i) {
        std::cout << "   [" << i + 1 << "] " << main[i]->getNom() << std::endl;
    }
    
    int choix = -1;
    std::cout << "Votre choix : ";
    std::cin >> choix;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choix < 1 || choix > static_cast<int>(main.size())) {
        std::cout << "⚠️  Choix invalide, défausse annulée" << std::endl;
        return;
    }
    
    Carte* carte_defaussee = main[choix - 1];
    joueur->defausse().ajouterCarte(carte_defaussee);
    main.erase(main.begin() + (choix - 1));
    
    std::cout << "   ✅ " << carte_defaussee->getNom() << " défaussée" << std::endl;
}

void EffetChampion::orcGruntAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   🌿 Effet ALLIÉ Wild : Pioche 1 carte" << std::endl;
    joueur->piocher(1);
}

void EffetChampion::lysUnseenAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   💀 Effet ALLIÉ Necros : Pioche 1 carte" << std::endl;
    joueur->piocher(1);
}

void EffetChampion::varrickNecromancerAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   💀 Effet ALLIÉ Necros : Pioche 1 carte" << std::endl;
    joueur->piocher(1);
}

void EffetChampion::krakaHighPriestAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "   👑 Effet ALLIÉ Imperial : Pioche 1 carte" << std::endl;
    joueur->piocher(1);
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - CHOIX BINAIRES
// ════════════════════════════════════════════════════════

void EffetChampion::darianWarMageExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      ⚖️  Darian vous offre un choix :" << std::endl;
    std::cout << "         [1] Gain 3 combat" << std::endl;
    std::cout << "         [2] Gain 4 health" << std::endl;
    std::cout << "      Votre choix : ";
    
    int choix = jeu->lireEntier(1, 2);
    
    if (choix == 1) {
        joueur->ajouterCombat(3);
        std::cout << "      ✅ +3 combat" << std::endl;
    } else {
        joueur->soigner(4);
        std::cout << "      ✅ +4 PV" << std::endl;
    }
}

void EffetChampion::streetThugExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      ⚖️  Street Thug vous offre un choix :" << std::endl;
    std::cout << "         [1] Gain 1 gold" << std::endl;
    std::cout << "         [2] Gain 2 combat" << std::endl;
    std::cout << "      Votre choix : ";
    
    int choix = jeu->lireEntier(1, 2);
    
    if (choix == 1) {
        joueur->ajouterOr(1);
        std::cout << "      ✅ +1 or" << std::endl;
    } else {
        joueur->ajouterCombat(2);
        std::cout << "      ✅ +2 combat" << std::endl;
    }
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - SACRIFICE AVEC BONUS
// ════════════════════════════════════════════════════════

void EffetChampion::krythosMasterVampireExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      💀 Voulez-vous sacrifier une carte pour +3 combat supplémentaire ? (o/n) : ";
    
    if (!jeu->confirmer("Sacrifier une carte ?")) {
        std::cout << "      ℹ️  Aucune carte sacrifiée" << std::endl;
        return;
    }
    
    // Collecter cartes sacrifiables
    std::vector<Carte*> cartes_sacrifiables;
    std::vector<std::string> sources;
    
    for (size_t i = 0; i < joueur->main().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->main().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("main");
        }
    }
    
    for (size_t i = 0; i < joueur->defausse().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->defausse().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("défausse");
        }
    }
    
    if (cartes_sacrifiables.empty()) {
        std::cout << "      ℹ️  Aucune carte à sacrifier" << std::endl;
        return;
    }
    
    std::cout << "\n      Cartes disponibles :" << std::endl;
    for (size_t i = 0; i < cartes_sacrifiables.size(); ++i) {
        std::cout << "         [" << (i+1) << "] " << cartes_sacrifiables[i]->getNom() 
                  << " (" << sources[i] << ")" << std::endl;
    }
    
    std::cout << "      Carte à sacrifier (1-" << cartes_sacrifiables.size() << ") : ";
    int choix = jeu->lireEntier(1, cartes_sacrifiables.size());
    
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
    
    joueur->sacrifice().ajouterCarte(carte);
    joueur->ajouterCombat(3);
    
    std::cout << "      💀 " << carte->getNom() << " sacrifiée !" << std::endl;
    std::cout << "      ✅ +3 combat supplémentaire" << std::endl;
}

void EffetChampion::lysTheUnseenExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      💀 Voulez-vous sacrifier une carte pour +2 combat supplémentaire ? (o/n) : ";
    
    if (!jeu->confirmer("Sacrifier une carte ?")) {
        std::cout << "      ℹ️  Aucune carte sacrifiée" << std::endl;
        return;
    }
    
    // Collecter cartes sacrifiables
    std::vector<Carte*> cartes_sacrifiables;
    std::vector<std::string> sources;
    
    for (size_t i = 0; i < joueur->main().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->main().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("main");
        }
    }
    
    for (size_t i = 0; i < joueur->defausse().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->defausse().getCarte(i));
        if (carte) {
            cartes_sacrifiables.push_back(carte);
            sources.push_back("défausse");
        }
    }
    
    if (cartes_sacrifiables.empty()) {
        std::cout << "      ℹ️  Aucune carte à sacrifier" << std::endl;
        return;
    }
    
    std::cout << "\n      Cartes disponibles :" << std::endl;
    for (size_t i = 0; i < cartes_sacrifiables.size(); ++i) {
        std::cout << "         [" << (i+1) << "] " << cartes_sacrifiables[i]->getNom() 
                  << " (" << sources[i] << ")" << std::endl;
    }
    
    std::cout << "      Carte à sacrifier (1-" << cartes_sacrifiables.size() << ") : ";
    int choix = jeu->lireEntier(1, cartes_sacrifiables.size());
    
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
    
    joueur->sacrifice().ajouterCarte(carte);
    joueur->ajouterCombat(2);
    
    std::cout << "      💀 " << carte->getNom() << " sacrifiée !" << std::endl;
    std::cout << "      ✅ +2 combat supplémentaire" << std::endl;
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - ADVERSAIRE DÉFAUSSE
// ════════════════════════════════════════════════════════

void EffetChampion::broelynLoreweaverAlly(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      🎯 L'adversaire doit défausser une carte" << std::endl;
    std::cout << "      ⚠️  (Fonctionnalité nécessitant accès au Plateau - à implémenter dans Jeu)" << std::endl;
}

void EffetChampion::torgenRocksplitterExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      🎯 L'adversaire doit défausser une carte" << std::endl;
    std::cout << "      ⚠️  (Fonctionnalité nécessitant accès au Plateau - à implémenter dans Jeu)" << std::endl;
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - ASSOMMER CHAMPION
// ════════════════════════════════════════════════════════

void EffetChampion::rakeMasterAssassinExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      💥 Voulez-vous assommer un champion adverse ? (o/n) : ";
    
    if (!jeu->confirmer("Assommer un champion ?")) {
        std::cout << "      ℹ️  Aucun champion assommé" << std::endl;
        return;
    }
    
    std::cout << "      🎯 Assommer un champion adverse" << std::endl;
    std::cout << "      ⚠️  (Fonctionnalité nécessitant accès au Plateau - à implémenter dans Jeu)" << std::endl;
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - PIOCHER/DÉFAUSSER OPTIONNEL
// ════════════════════════════════════════════════════════

void EffetChampion::grakStormGiantExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      ❓ Voulez-vous piocher une carte ? (vous devrez en défausser une) (o/n) : ";
    
    if (!jeu->confirmer("Piocher et défausser ?")) {
        std::cout << "      ℹ️  Vous choisissez de ne pas piocher" << std::endl;
        return;
    }
    
    joueur->piocher(1);
    std::cout << "      📚 Vous piochez 1 carte" << std::endl;
    
    if (joueur->main().taille() == 0) {
        std::cout << "      ℹ️  Aucune carte en main à défausser" << std::endl;
        return;
    }
    
    std::cout << "\n      🗑️  Choisissez une carte à défausser :" << std::endl;
    joueur->afficherMain();
    
    std::cout << "\n      Carte (1-" << joueur->main().taille() << ") : ";
    int index = jeu->lireEntier(1, joueur->main().taille());
    
    Carte* carte = const_cast<Carte*>(joueur->main().getCarte(index - 1));
    joueur->main().retirerCarte(index - 1);
    joueur->defausse().ajouterCarte(carte);
    
    std::cout << "      ✅ " << carte->getNom() << " défaussée" << std::endl;
}

// ════════════════════════════════════════════════════════
// NOUVEAUX EFFETS - MANIPULATION DE DECK
// ════════════════════════════════════════════════════════

void EffetChampion::varrickNecromancerExpend(Joueur* joueur, Jeu* jeu) {
    if (!joueur || !jeu) {
        std::cerr << "❌ Erreur : Joueur ou Jeu invalide !" << std::endl;
        return;
    }
    
    std::cout << "      🧟 Récupération d'un champion de la défausse..." << std::endl;
    
    // Collecter les champions dans la défausse
    std::vector<Carte*> champions_defausse;
    
    for (size_t i = 0; i < joueur->defausse().taille(); ++i) {
        Carte* carte = const_cast<Carte*>(joueur->defausse().getCarte(i));
        if (carte && carte->getType() == CHAMPION) {
            champions_defausse.push_back(carte);
        }
    }
    
    if (champions_defausse.empty()) {
        std::cout << "      ℹ️  Aucun champion dans votre défausse" << std::endl;
        return;
    }
    
    std::cout << "\n      Champions disponibles dans la défausse :" << std::endl;
    for (size_t i = 0; i < champions_defausse.size(); ++i) {
        std::cout << "         [" << (i+1) << "] " << champions_defausse[i]->getNom() << std::endl;
    }
    
    std::cout << "      Champion à placer sur le deck (1-" << champions_defausse.size() << ") : ";
    int choix = jeu->lireEntier(1, champions_defausse.size());
    
    Carte* champion = champions_defausse[choix - 1];
    
    // Retirer de la défausse
    joueur->defausse().retirerCarte(champion);
    
    // Placer sur le dessus de la pioche
    joueur->pioche().ajouterDessus(champion);
    
    std::cout << "      ✅ " << champion->getNom() << " placé sur le dessus de votre deck !" << std::endl;
}