#include "effets/EffetChampion.hpp"
#include "Joueur/Joueur.hpp"
#include "Jeu.hpp"
#include <iostream>

// ════════════════════════════════════════════════════════
// EFFETS DE PIOCHE CONDITIONNELS (ALLY)
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
