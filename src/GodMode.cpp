#include "GodMode.hpp"
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "zone/Marche.hpp"
#include "enum/Faction.hpp"     
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <limits>

// ════════════════════════════════════════════════════════
// CONSTRUCTEUR & DESTRUCTEUR
// ════════════════════════════════════════════════════════

GodMode::GodMode(Plateau& plateau) 
    : plateau_(plateau), actif_(false) {
}

GodMode::~GodMode() {
}

// ════════════════════════════════════════════════════════
// ACTIVATION / DÉSACTIVATION
// ════════════════════════════════════════════════════════

void GodMode::activer() {
    if (!actif_) {
        actif_ = true;
        std::cout << "\n⚡ GOD MODE ACTIVÉ ⚡" << std::endl;
        std::cout << "   Vous êtes désormais tout-puissant ! 🔥" << std::endl;
    } else {
        std::cout << "\n⚠️  God Mode déjà activé !" << std::endl;
    }
}

void GodMode::desactiver() {
    if (actif_) {
        actif_ = false;
        std::cout << "\n❌ GOD MODE DÉSACTIVÉ" << std::endl;
        std::cout << "   Retour au jeu normal." << std::endl;
    } else {
        std::cout << "\n⚠️  God Mode déjà désactivé !" << std::endl;
    }
}

void GodMode::basculer() {
    if (actif_) {
        desactiver();
    } else {
        activer();
    }
}

bool GodMode::estActif() const {
    return actif_;
}

// ════════════════════════════════════════════════════════
// MENU INTERACTIF
// ════════════════════════════════════════════════════════

void GodMode::afficherMenu() {
    bool quitter = false;
    
    while (!quitter) {
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║              ⚡ GOD MODE MENU ⚡                       ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
        
        std::cout << "\nÉtat : " << (actif_ ? "✅ ACTIVÉ" : "❌ DÉSACTIVÉ") << std::endl;
        
        std::cout << "\n1. " << (actif_ ? "Désactiver" : "Activer") << " le God Mode" << std::endl;
        std::cout << "2. Mettre tous les joueurs à 1 PV" << std::endl;
        std::cout << "3. Définir les PV d'un joueur spécifique" << std::endl;
        std::cout << "4. Acheter depuis tout le deck du marché" << std::endl;
        std::cout << "5. Afficher l'état du God Mode" << std::endl;
        std::cout << "6. Afficher tout le deck du marché" << std::endl;
        std::cout << "0. Retour au jeu" << std::endl;
        
        std::cout << "\nChoix : ";
        int choix = lireEntier(0, 6);
        
        switch (choix) {
            case 0:
                quitter = true;
                std::cout << "\n🔙 Retour au jeu..." << std::endl;
                break;
                
            case 1:
                basculer();
                pause();
                break;
                
            case 2:
                mettreJoueursA1PV();
                pause();
                break;
                
            case 3: {
                Joueur* joueur = selectionnerJoueur();
                if (joueur) {
                    std::cout << "\nNouveaux PV (1-100) : ";
                    int pv = lireEntier(1, 100);
                    definirPVJoueur(joueur, pv);
                }
                pause();
                break;
            }
                
            case 4:
                if (!actif_) {
                    std::cout << "\n⚠️  Vous devez activer le God Mode d'abord !" << std::endl;
                    pause();
                } else {
                    acheterDepuisDeckComplet();
                }
                break;
                
            case 5:
                afficherEtat();
                pause();
                break;
                
            case 6:
                afficherDeckComplet(true);
                pause();
                break;
                
            default:
                std::cout << "\n❌ Choix invalide !" << std::endl;
                pause();
                break;
        }
    }
}

// ════════════════════════════════════════════════════════
// FONCTIONNALITÉS GOD MODE
// ════════════════════════════════════════════════════════

void GodMode::mettreJoueursA1PV() {
    std::cout << "\n💀 Mise de tous les joueurs à 1 PV..." << std::endl;
    
    for (size_t i = 0; i < plateau_.nbJoueurs(); ++i) {
        Joueur* joueur = plateau_.getJoueur(i);
        if (joueur && !joueur->estMort()) {
            int pv_perdus = joueur->pv() - 1;
            joueur->subirDegats(pv_perdus);
        }
    }
    
    std::cout << "✅ Tous les joueurs sont désormais à 1 PV !" << std::endl;
}

void GodMode::mettreJoueurA1PV(Joueur* joueur) {
    if (!joueur) return;
    
    int pv_perdus = joueur->pv() - 1;
    joueur->subirDegats(pv_perdus);
    
    std::cout << "✅ " << joueur->nom() << " est maintenant à 1 PV !" << std::endl;
}

void GodMode::definirPVJoueur(Joueur* joueur, int pv) {
    if (!joueur) return;
    
    int diff = pv - joueur->pv();
    
    if (diff > 0) {
        joueur->soigner(diff);
    } else if (diff < 0) {
        joueur->subirDegats(-diff);
    }
    
    std::cout << "✅ " << joueur->nom() << " a maintenant " << pv << " PV !" << std::endl;
}

bool GodMode::acheterDepuisDeckComplet() {
    if (!actif_) {
        std::cout << "\n⚠️  God Mode non activé !" << std::endl;
        return false;
    }
    
    Joueur* joueur = plateau_.joueurActif();
    if (!joueur) {
        std::cout << "\n⚠️  Aucun joueur actif !" << std::endl;
        return false;
    }
    
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        🛒 ACHAT DEPUIS LE DECK COMPLET 🛒             ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    afficherDeckComplet(false);
    
    size_t nb_cartes = plateau_.marche().nbCartesDeck();
    
    if (nb_cartes == 0) {
        std::cout << "\n⚠️  Le deck du marché est vide !" << std::endl;
        pause();
        return false;
    }
    
    std::cout << "\n[0] Annuler" << std::endl;
    std::cout << "\nQuelle carte voulez-vous acheter (1-" << nb_cartes << ") ? ";
    
    int choix = lireEntier(0, static_cast<int>(nb_cartes));
    
    if (choix == 0) {
        std::cout << "\n❌ Achat annulé." << std::endl;
        pause();
        return false;
    }
    
    return acheterCarteDeck(choix - 1, joueur);
}

bool GodMode::acheterCarteDeck(size_t index_deck, Joueur* joueur) {
    if (!actif_ || !joueur) return false;
    
    // Acheter la carte directement depuis le deck
    Carte* carte = plateau_.marche().acheterCarteDuDeck(index_deck);
    
    if (carte) {
        // Placer directement dans la main (pas dans la défausse)
        joueur->main().ajouterCarte(carte);
        std::cout << "✅ " << carte->getNom() << " ajoutée directement à votre main !" << std::endl;
        pause();
        return true;
    }
    
    std::cout << "❌ Impossible d'acheter cette carte." << std::endl;
    pause();
    return false;
}

// ════════════════════════════════════════════════════════
// AFFICHAGE
// ════════════════════════════════════════════════════════

void GodMode::afficherEtat() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              ⚡ ÉTAT DU GOD MODE ⚡                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\nÉtat : " << (actif_ ? "✅ ACTIVÉ" : "❌ DÉSACTIVÉ") << std::endl;
    
    if (actif_) {
        std::cout << "\n🔥 Pouvoirs disponibles :" << std::endl;
        std::cout << "   ✓ Modifier les PV des joueurs" << std::endl;
        std::cout << "   ✓ Acheter depuis tout le deck du marché" << std::endl;
        std::cout << "   ✓ Cartes achetées vont directement dans la main" << std::endl;
    } else {
        std::cout << "\n💤 Mode normal - Aucun pouvoir spécial actif" << std::endl;
    }
    
    std::cout << "\n📊 État du plateau :" << std::endl;
    std::cout << "   Joueurs : " << plateau_.nbJoueurs() << std::endl;
    std::cout << "   Tour : " << plateau_.numeroTour() << std::endl;
    std::cout << "   Joueur actif : " << plateau_.joueurActif()->nom() << std::endl;
}

void GodMode::afficherDeckComplet(bool afficher_details) const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           📚 DECK COMPLET DU MARCHÉ 📚                 ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    const auto& deck = plateau_.marche().getDeckCartes();
    size_t nb_cartes = deck.size();
    
    std::cout << "\n📦 Nombre de cartes dans le deck : " << nb_cartes << std::endl;
    
    if (nb_cartes == 0) {
        std::cout << "   (Le deck est vide)" << std::endl;
        return;
    }
    
    std::cout << "\n--- Liste des cartes ---" << std::endl;
    
    for (size_t i = 0; i < deck.size(); ++i) {
        const Carte* carte = deck[i];
        
        // Icônes de faction
        std::string icone_faction;
        switch(carte->getFaction()) {
            case Faction::IMPERIAL: icone_faction = "👑"; break;
            case Faction::GUILD:    icone_faction = "🏹"; break;
            case Faction::NECROS:   icone_faction = "💀"; break;
            case Faction::WILD:     icone_faction = "🐺"; break;
            default:                icone_faction = "⚪"; break;
        }
        
        // Icônes de type
        std::string icone_type;
        switch(carte->getType()) {
            case TypeCarte::ACTION:   icone_type = "⚡"; break;
            case TypeCarte::CHAMPION: icone_type = "👤"; break;
            case TypeCarte::ITEM:     icone_type = "🔨"; break;
            default:                  icone_type = "❓"; break;
        }
        
        std::cout << "[" << (i+1) << "] " 
                  << icone_faction << " " 
                  << icone_type << " "
                  << carte->getNom() 
                  << " (Coût: " << carte->getCout() << " or)";
        
        std::cout << std::endl;
        
        if (afficher_details) {
            std::cout << "    " << carte->getDescription() << std::endl;
        }
    }
}

// ════════════════════════════════════════════════════════
// MÉTHODES PRIVÉES UTILITAIRES
// ════════════════════════════════════════════════════════

Joueur* GodMode::selectionnerJoueur() {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              👥 SÉLECTION DU JOUEUR                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    for (size_t i = 0; i < plateau_.nbJoueurs(); ++i) {
        Joueur* joueur = plateau_.getJoueur(i);
        std::cout << "\n[" << (i+1) << "] " << joueur->nom();
        std::cout << " (PV: " << joueur->pv() << ")";
        if (joueur->estMort()) {
            std::cout << " 💀 MORT";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n[0] Annuler" << std::endl;
    std::cout << "\nQuel joueur (0-" << plateau_.nbJoueurs() << ") ? ";
    
    int choix = lireEntier(0, static_cast<int>(plateau_.nbJoueurs()));
    
    if (choix == 0) {
        return nullptr;
    }
    
    return plateau_.getJoueur(choix - 1);
}

int GodMode::lireEntier(int min, int max) const {
    int valeur;
    
    while (true) {
        std::cin >> valeur;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Entrée invalide. Entrez un nombre entre " << min << " et " << max << " : ";
        } else if (valeur < min || valeur > max) {
            std::cout << "❌ Valeur hors limites. Entrez un nombre entre " << min << " et " << max << " : ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valeur;
        }
    }
}

void GodMode::pause(const std::string& message) const {
    std::cout << "\n" << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}