#include "Jeu.hpp"
#include "Regle.hpp"
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteAction.hpp"
#include "cartes/cartechampion.hpp"
#include "cartes/CarteItem.hpp"
#include "GodMode.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

// ====== Constructeur & Destructeur ======

Jeu::Jeu() 
    : jeu_en_cours_(false), 
      quitter_(false),
      nb_joueurs_(2),
      pv_initial_(50),
      god_mode_(nullptr) {  
}

Jeu::~Jeu() {
    if (god_mode_) {  
        delete god_mode_;
        god_mode_ = nullptr;
    }
}
// ====== Initialisation ======

void Jeu::lancer() {
    afficherTitre();

    while (!quitter_) {
        afficherMenuPrincipal();

        int choix = lireEntier(1, 4);

        switch (choix) {
            case 1:
                nouvellePartie();
                break;
            case 2:
                Regle::afficherMenuRegles();
                break;
            case 3:
                std::cout << "\n📊 Info:" << std::endl;
                std::cout << "   Hero Realms - Jeu de cartes" << std::endl;
                std::cout << "   Développé par: Issam Atoui et Alexandre Fakhfakh" << std::endl;
                std::cout << "   Date: 2025-11-02" << std::endl;
                pause();
                break;
            case 4:
                quitter_ = true;
                std::cout << "\n👋 Merci d'avoir joué à Hero Realms !" << std::endl;
                break;
        }
    }
}

void Jeu::nouvellePartie() {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            🎮 NOUVELLE PARTIE 🎮                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    configurerJoueurs();

    // Initialiser le plateau
    plateau_.initialiser(noms_joueurs_, pv_initial_);

    // Créer le God Mode (après l'initialisation du plateau)
    if (god_mode_) {
        delete god_mode_;
    }
    god_mode_ = new GodMode(plateau_);  

    // Démarrer la partie
    plateau_.demarrerPartie();

    pause();

    // Lancer la boucle de jeu
    boucleDeJeu();
}

void Jeu::configurerJoueurs() {
    // Nombre de joueurs
    std::cout << "\n👥 Nombre de joueurs (2-4): ";
    nb_joueurs_ = lireEntier(2, 4);

    // Noms des joueurs
    noms_joueurs_.clear();
    for (int i = 1; i <= nb_joueurs_; ++i) {
        std::cout << "Nom du joueur " << i << ": ";
        std::string nom = lireChaine();
        if (nom.empty()) {
            nom = "Joueur " + std::to_string(i);
        }
        noms_joueurs_.push_back(nom);
    }

    // Points de vie initiaux
    std::cout << "\n💚 Points de vie initiaux (50 par défaut): ";
    pv_initial_ = lireEntier(10, 100);

    std::cout << "\n✅ Configuration terminée !" << std::endl;
}

// ====== Boucle de Jeu ======

void Jeu::boucleDeJeu() {
    jeu_en_cours_ = true;

    while (jeu_en_cours_ && !plateau_.partieTerminee()) {
        Joueur* joueur = plateau_.joueurActif();

        // Vérifier si le joueur est mort (skip)
        if (joueur->estMort()) {
            plateau_.joueurSuivant();
            continue;
        }

        // Exécuter le tour du joueur
        executerTour(joueur);

        // Vérifier si le joueur a quitté
        if (!jeu_en_cours_) {
            std::cout << "\n⚠️  Partie interrompue par abandon." << std::endl;
            pause();
            return;  // Sortir sans afficher les résultats normaux
        }

        // Vérifier la fin de partie
        if (plateau_.partieTerminee()) {
            jeu_en_cours_ = false;
            break;
        }

        // Passer au joueur suivant
        plateau_.joueurSuivant();
    }

    // Afficher les résultats (seulement si fin naturelle)
    if (plateau_.partieTerminee()) {
        afficherResultats();
    }
}

void Jeu::executerTour(Joueur* joueur) {
    clearScreen();

    // Début de tour
    joueur->debutDeTour();

    bool tour_termine = false;

    while (!tour_termine) {
        clearScreen();
        
        // Afficher l'état du plateau
        plateau_.afficher();

        // Afficher les zones du joueur
        std::cout << "\n";
        joueur->afficherZones();

        // Menu du tour
        afficherMenuTour();

        int choix = lireEntier(1, 9);  // ← CHANGÉ de 8 à 9

        switch (choix) {
            case 1:
                phaseJeu(joueur);
                break;
            case 2:
                phaseAchat(joueur);
                break;
            case 3:
                phaseAttaque(joueur);
                break;
            case 4:
                phaseChampions(joueur);
                break;
            case 5:
                joueur->afficherStatistiques();
                pause();
                break;
            case 6:
                afficherAide();
                break;
            case 7:
                if (confirmer("Êtes-vous sûr de vouloir terminer votre tour ?")) {
                    joueur->finDeTour();
                    tour_termine = true;
                }
                break;
            case 8:  // ← NOUVEAU : God Mode
                if (god_mode_) {
                    god_mode_->afficherMenu();
                } else {
                    std::cout << "\n⚠️  God Mode non disponible !" << std::endl;
                    pause();
                }
                break;
            case 9:  // ← MODIFIÉ : Quitter (était case 8)
                if (quitterPartie()) {
                    jeu_en_cours_ = false;
                    tour_termine = true;
                }
                break;
        }
        if (!jeu_en_cours_) {
            break;
        }
    }
}

bool Jeu::quitterPartie() {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🚪 QUITTER LA PARTIE 🚪                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n⚠️  Attention : Vous êtes sur le point de quitter la partie en cours." << std::endl;
    std::cout << "   Toute progression sera perdue.\n" << std::endl;

    if (confirmer("Êtes-vous vraiment sûr de vouloir quitter ?")) {
        std::cout << "\n📊 État de la partie avant abandon :" << std::endl;
        
        // Afficher le classement actuel
        plateau_.afficherClassement();

        std::cout << "\n👋 Partie abandonnée." << std::endl;
        std::cout << "   Retour au menu principal...\n" << std::endl;
        
        pause();
        return true;  // Confirme la sortie
    }

    std::cout << "\n✅ Retour à la partie..." << std::endl;
    pause();
    return false;  // Annule la sortie
}

// ====== Phases de Jeu ======

void Jeu::phaseJeu(Joueur* joueur) {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🎴 PHASE DE JEU 🎴                        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    joueur->afficherMain();

    if (joueur->main().estVide()) {
        std::cout << "\n⚠️  Vous n'avez aucune carte à jouer !" << std::endl;
        pause();
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Quelle carte voulez-vous jouer ?                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n  [1-" << joueur->main().taille() << "] Jouer une carte spécifique" << std::endl;
    std::cout << "  [ALL] Jouer TOUTES les cartes de la main" << std::endl;
    std::cout << "  [0] Annuler" << std::endl;
    std::cout << "\nChoix : ";

    std::string choix_str;
    std::getline(std::cin, choix_str);

    // Convertir en minuscules pour faciliter la comparaison
    std::transform(choix_str.begin(), choix_str.end(), choix_str.begin(), ::tolower);

    if (choix_str == "0") {
        return;
    }
    else if (choix_str == "all" || choix_str == "a") {
        // Jouer toutes les cartes
        jouerToutesLesCartes(joueur);
    }
    else {
        // Jouer une carte spécifique
        try {
            int choix = std::stoi(choix_str);
            if (choix < 1 || choix > static_cast<int>(joueur->main().taille())) {
                std::cout << "\n⚠️  Choix invalide !" << std::endl;
            } else {
                if (jouerCarte(joueur, choix - 1)) {
                    std::cout << "\n✅ Carte jouée avec succès !" << std::endl;
                } else {
                    std::cout << "\n⚠️  Impossible de jouer cette carte !" << std::endl;
                }
            }
        } catch (...) {
            std::cout << "\n⚠️  Entrée invalide !" << std::endl;
        }
    }

    pause();
}

void Jeu::jouerToutesLesCartes(Joueur* joueur) {
    if (!joueur) return;

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  🎴 JOUER TOUTES LES CARTES                            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    int nb_cartes = joueur->main().taille();
    std::cout << "\n📋 Vous allez jouer " << nb_cartes << " carte(s)" << std::endl;
    std::cout << "   (Les choix de sacrifice seront proposés individuellement)\n" << std::endl;

    pause("Appuyez sur Entrée pour commencer...");

    int cartes_jouees = 0;
    int champions_joues = 0;
    int actions_jouees = 0;
    int items_joues = 0;
    int cartes_sacrifiees = 0;

    // Jouer toutes les cartes une par une
    while (!joueur->main().estVide()) {
        clearScreen();
        
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║  Carte " << (cartes_jouees + 1) << "/" << nb_cartes << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

        // Afficher l'état actuel
        std::cout << "\n📊 État actuel :" << std::endl;
        std::cout << "   💰 Or : " << joueur->orTour() << std::endl;
        std::cout << "   ⚔️  Combat : " << joueur->combatTour() << std::endl;
        std::cout << "   💚 PV : " << joueur->pv() << std::endl;
        std::cout << "   🎴 Cartes restantes : " << joueur->main().taille() << std::endl;

        // Récupérer la première carte de la main
        Carte* carte = joueur->main().getCarte(size_t(0));
        if (!carte) {
            break;
        }

        std::cout << "\n▶️  Carte en cours : " << carte->getNom() << std::endl;
        std::cout << "═══════════════════════════════════════════════════════════" << std::endl;

        // Retirer la carte de la main
        joueur->main().retirerCarte(size_t(0));

        // Enregistrer la faction jouée (pour effets alliés)
        joueur->enregistrerFactionJouee(carte->getFaction());

        // Jouer la carte (gestion interne du sacrifice)
        carte->jouer(joueur);

        // Gestion selon le type de carte
        CarteChampion* champion = dynamic_cast<CarteChampion*>(carte);
        CarteAction* action = dynamic_cast<CarteAction*>(carte);
        CarteItem* item = dynamic_cast<CarteItem*>(carte);

        if (champion) {
            // Les champions vont dans la zone de jeu
            joueur->zoneDeJeu().ajouterChampion(champion);
            std::cout << "\n✅ " << champion->getNom() << " entre en jeu !" << std::endl;
            champions_joues++;
        } 
        else {
            // Vérifier si la carte a un effet de sacrifice
            bool a_sacrifice = (action && action->aEffetSacrifice()) || 
                              (item && item->aEffetSacrifice());
            
            if (a_sacrifice) {
                // Demander confirmation pour le sacrifice
                std::cout << "\n💀 Cette carte a-t-elle été sacrifiée ?" << std::endl;
                if (confirmer("Confirmer le sacrifice")) {
                    // Carte sacrifiée -> zone de sacrifice
                    joueur->sacrifice().ajouterCarte(carte);
                    std::cout << "💀 " << carte->getNom() << " a été sacrifiée (retirée du jeu)" << std::endl;
                    cartes_sacrifiees++;
                } else {
                    // Carte non sacrifiée -> défausse
                    joueur->defausse().ajouterCarte(carte);
                    std::cout << "🗑️  " << carte->getNom() << " va en défausse" << std::endl;
                }
            } else {
                // Pas de sacrifice possible -> défausse
                joueur->defausse().ajouterCarte(carte);
                std::cout << "🗑️  " << carte->getNom() << " va en défausse" << std::endl;
            }

            if (action) actions_jouees++;
            if (item) items_joues++;
        }

        cartes_jouees++;

        // Petite pause entre chaque carte (sauf pour la dernière)
        if (!joueur->main().estVide()) {
            pause("\nAppuyez sur Entrée pour la carte suivante...");
        }
    }

    // Résumé final
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  ✅ TOUTES LES CARTES ONT ÉTÉ JOUÉES !                 ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n📊 Résumé du tour :" << std::endl;
    std::cout << "   🎴 Cartes jouées : " << cartes_jouees << std::endl;
    std::cout << "      👤 Champions : " << champions_joues << std::endl;
    std::cout << "      ⚡ Actions : " << actions_jouees << std::endl;
    std::cout << "      🔨 Items : " << items_joues << std::endl;
    if (cartes_sacrifiees > 0) {
        std::cout << "   💀 Cartes sacrifiées : " << cartes_sacrifiees << std::endl;
    }

    std::cout << "\n📈 État final :" << std::endl;
    std::cout << "   💰 Or total : " << joueur->orTour() << std::endl;
    std::cout << "   ⚔️  Combat total : " << joueur->combatTour() << std::endl;
    std::cout << "   💚 PV : " << joueur->pv() << std::endl;
    std::cout << "   🛡️  Champions en jeu : " << joueur->zoneDeJeu().taille() << std::endl;
}

void Jeu::phaseAchat(Joueur* joueur) {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              💰 PHASE D'ACHAT 💰                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n💰 Or disponible: " << joueur->orTour() << std::endl;

    plateau_.afficherMarche(true);

    std::cout << "\nQue voulez-vous acheter ?" << std::endl;
    std::cout << "  [0] Gemme de Feu (2 or)" << std::endl;
    std::cout << "  [1-5] Carte du marché" << std::endl;
    std::cout << "  [6] Annuler" << std::endl;
    std::cout << "\nChoix: ";

    int choix = lireEntier(0, 6);

    if (choix == 6) {
        return;
    }

    if (acheterCarte(joueur, choix)) {
        std::cout << "\n✅ Achat réussi !" << std::endl;
    } else {
        std::cout << "\n⚠️  Achat impossible !" << std::endl;
    }

    pause();
}

void Jeu::phaseAttaque(Joueur* joueur) {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              ⚔️  PHASE D'ATTAQUE ⚔️                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n⚔️  Combat disponible: " << joueur->combatTour() << std::endl;

    if (joueur->combatTour() <= 0) {
        std::cout << "\n⚠️  Vous n'avez pas de combat disponible !" << std::endl;
        pause();
        return;
    }

    // Sélectionner la cible
    Joueur* cible = selectionnerCible(joueur);
    if (!cible) {
        return;
    }

    // Vérifier si la cible a des champions Garde
    if (cible->aChampionsGarde()) {
        std::cout << "\n🛡️  " << cible->nom() << " a des champions Garde !" << std::endl;
        std::cout << "Vous devez d'abord attaquer les champions Garde." << std::endl;

        cible->zoneDeJeu().afficher(true);

        std::cout << "\nQuel champion voulez-vous attaquer ? (0 pour annuler): ";
        int choix = lireEntier(0, static_cast<int>(cible->zoneDeJeu().taille()));

        if (choix == 0) {
            return;
        }

        std::cout << "\nCombien de dégâts ? (max: " << joueur->combatTour() << "): ";
        int degats = lireEntier(1, joueur->combatTour());

        attaquerChampion(joueur, cible, choix - 1, degats);
    } else {
        // Attaquer directement le joueur ou ses champions
        std::cout << "\n1. Attaquer " << cible->nom() << " directement" << std::endl;
        if (!cible->zoneDeJeu().estVide()) {
            std::cout << "2. Attaquer un champion" << std::endl;
        }
        std::cout << "0. Annuler" << std::endl;

        int choix = lireEntier(0, cible->zoneDeJeu().estVide() ? 1 : 2);

        if (choix == 0) {
            return;
        } else if (choix == 1) {
            // Attaque directe
            std::cout << "\nCombien de dégâts ? (max: " << joueur->combatTour() << "): ";
            int degats = lireEntier(1, joueur->combatTour());
            attaquer(joueur, cible, degats);
        } else if (choix == 2) {
            // Attaque d'un champion
            cible->zoneDeJeu().afficher(true);

            std::cout << "\nQuel champion voulez-vous attaquer ? (0 pour annuler): ";
            int choix_champion = lireEntier(0, static_cast<int>(cible->zoneDeJeu().taille()));

            if (choix_champion == 0) {
                return;
            }

            std::cout << "\nCombien de dégâts ? (max: " << joueur->combatTour() << "): ";
            int degats = lireEntier(1, joueur->combatTour());

            attaquerChampion(joueur, cible, choix_champion - 1, degats);
        }
    }

    pause();
}

void Jeu::phaseChampions(Joueur* joueur) {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          👤 ACTIVATION DES CHAMPIONS 👤                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    auto& champions = joueur->zoneDeJeu().champions();
    
    if (champions.empty()) {
        std::cout << "\n⚠️  Vous n'avez aucun champion en jeu !" << std::endl;
        pause();
        return;
    }

    // Afficher les champions avec leurs capacités
    joueur->afficherChampions();

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Actions disponibles                                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n  [1] Utiliser une capacité EXPEND" << std::endl;
    std::cout << "  [0] Retour" << std::endl;
    std::cout << "\nChoix: ";
    
    int choix = lireEntier(0, 1);
    
    if (choix == 0) {
        return;
    }
    
    if (choix == 1) {
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║  Quel champion voulez-vous utiliser ?                  ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "\n  [1-" << champions.size() << "] Choisir un champion" << std::endl;
        std::cout << "  [0] Annuler" << std::endl;
        std::cout << "\nChoix: ";
        
        int index = lireEntier(0, static_cast<int>(champions.size()));
        
        if (index > 0 && index <= static_cast<int>(champions.size())) {
            CarteChampion* champion = champions[index - 1];
            
            if (!champion) {
                std::cout << "\n⚠️  Champion invalide !" << std::endl;
            } else if (!champion->aEffetExpend()) {
                std::cout << "\n⚠️  " << champion->getNom() << " n'a pas de capacité Expend !" << std::endl;
            } else if (champion->estExpended()) {
                std::cout << "\n⚠️  " << champion->getNom() << " a déjà utilisé sa capacité Expend ce tour !" << std::endl;
            } else {
                champion->utiliserExpend(joueur);
            }
        }
    }
    
    pause();
}

// ====== Actions de Jeu ======

bool Jeu::jouerCarte(Joueur* joueur, int index) {
    Carte* carte = joueur->main().getCarte(index);
    if (!carte) {
        return false;
    }

    // Retirer la carte de la main
    joueur->main().retirerCarte(index);

    // Enregistrer la faction jouée (pour effets alliés)
    joueur->enregistrerFactionJouee(carte->getFaction());

    // Jouer la carte
    carte->jouer(joueur);

    // Gestion selon le type de carte
    CarteChampion* champion = dynamic_cast<CarteChampion*>(carte);
    if (champion) {
        // Les champions vont dans la zone de jeu
        joueur->zoneDeJeu().ajouterChampion(champion);
        std::cout << "✅ " << champion->getNom() << " entre en jeu !" << std::endl;
    } else {
        // Vérifier si c'est une Action ou un Item avec sacrifice
        CarteAction* action = dynamic_cast<CarteAction*>(carte);
        CarteItem* item = dynamic_cast<CarteItem*>(carte);
        
        bool a_sacrifice = (action && action->aEffetSacrifice()) || 
                          (item && item->aEffetSacrifice());
        
        if (a_sacrifice) {
            if (confirmer("Cette carte a-t-elle été sacrifiée ?")) {
                // Carte sacrifiée -> zone de sacrifice
                joueur->sacrifice().ajouterCarte(carte);
                std::cout << "💀 " << carte->getNom() << " a été sacrifiée (retirée du jeu)" << std::endl;
            } else {
                // Carte non sacrifiée -> défausse
                joueur->defausse().ajouterCarte(carte);
                std::cout << "🗑️  " << carte->getNom() << " va en défausse" << std::endl;
            }
        } else {
            // Pas de sacrifice possible -> défausse
            joueur->defausse().ajouterCarte(carte);
            std::cout << "🗑️  " << carte->getNom() << " va en défausse" << std::endl;
        }
    }

    return true;
}

bool Jeu::acheterCarte(Joueur* joueur, int choix) {
    if (choix == 0) {
        // Acheter une Gemme de Feu
        if (joueur->orTour() >= 2) {
            Carte* gemme = plateau_.marche().acheterGemmeDeFeu();
            joueur->ajouterOr(-2);
            joueur->defausse().ajouterCarte(gemme);
            return true;
        } else {
            std::cout << "⚠️  Pas assez d'or ! (Coût: 2)" << std::endl;
            return false;
        }
    } else if (choix >= 1 && choix <= 5) {
        // Acheter une carte du marché
        const Carte* carte = plateau_.marche()[choix - 1];
        if (!carte) {
            std::cout << "⚠️  Aucune carte à cet emplacement !" << std::endl;
            return false;
        }

        if (joueur->orTour() >= carte->getCout()) {
            Carte* carte_achetee = plateau_.marche().acheterCarte(choix - 1);
            joueur->ajouterOr(-carte_achetee->getCout());
            joueur->defausse().ajouterCarte(carte_achetee);
            return true;
        } else {
            std::cout << "⚠️  Pas assez d'or ! (Coût: " << carte->getCout() << ")" << std::endl;
            return false;
        }
    }

    return false;
}

void Jeu::attaquer(Joueur* attaquant, Joueur* cible, int degats) {
    std::cout << "\n⚔️  " << attaquant->nom() << " attaque " << cible->nom() 
              << " pour " << degats << " dégâts !" << std::endl;

    cible->subirDegats(degats);
    attaquant->ajouterCombat(-degats);

    if (cible->estMort()) {
        std::cout << "\n💀 " << cible->nom() << " a été vaincu !" << std::endl;
    }
}

void Jeu::attaquerChampion(Joueur* attaquant, Joueur* cible, int index_champion, int degats) {
    CarteChampion* champion = cible->zoneDeJeu().getChampion(index_champion);
    if (!champion) {
        std::cout << "⚠️  Champion invalide !" << std::endl;
        return;
    }

    std::cout << "\n⚔️  " << attaquant->nom() << " attaque " << champion->getNom() 
              << " pour " << degats << " dégâts !" << std::endl;

    champion->subirDegats(degats);
    attaquant->ajouterCombat(-degats);

    // Vérifier si le champion est mort
    cible->defausserChampionsMorts();
}

// ====== Utilitaires ======

void Jeu::afficherMenuPrincipal() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              📜 MENU PRINCIPAL 📜                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n  [1] 🎮 Nouvelle Partie" << std::endl;
    std::cout << "  [2] 📖 Règles du Jeu" << std::endl;
    std::cout << "  [3] 📊 Info du Jeu" << std::endl;
    std::cout << "  [4] 🚪 Quitter" << std::endl;
    std::cout << "\nChoix: ";
}

void Jeu::afficherMenuTour() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              📜 MENU DU TOUR 📜                        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n  [1] 🎴 Jouer une Carte" << std::endl;
    std::cout << "  [2] 💰 Acheter une Carte" << std::endl;
    std::cout << "  [3] ⚔️  Attaquer" << std::endl;
    std::cout << "  [4] 👤 Activer les Champions" << std::endl;
    std::cout << "  [5] 📊 Voir Statistiques" << std::endl;
    std::cout << "  [6] ❓ Aide" << std::endl;
    std::cout << "  [7] ✅ Terminer le Tour" << std::endl;
    std::cout << "  [8] ⚡ God Mode" << std::endl;           
    std::cout << "  [9] 🚪 Quitter la Partie" << std::endl;  
    std::cout << "\nChoix: ";
}

void Jeu::afficherResultats() const {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🎉 FIN DE LA PARTIE 🎉                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    plateau_.afficherClassement();

    auto gagnants = plateau_.gagnants();
    if (!gagnants.empty()) {
        std::cout << "\n🏆 GAGNANT : " << gagnants[0]->nom() << " ! 🏆" << std::endl;
    }

    plateau_.afficherStatistiques();

    pause("\nAppuyez sur Entrée pour retourner au menu principal...");
}

void Jeu::pause(const std::string& message) const {
    std::cout << "\n" << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Jeu::clearScreen() const {
    // Simulation de nettoyage d'écran (portable)
    std::cout << "\n\n\n";
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
}

int Jeu::lireEntier(int min, int max) const {
    int valeur;
    while (true) {
        std::cin >> valeur;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "⚠️  Entrée invalide ! Veuillez entrer un nombre entre " 
                      << min << " et " << max << ": ";
        } else if (valeur < min || valeur > max) {
            std::cout << "⚠️  Valeur hors limites ! Veuillez entrer un nombre entre " 
                      << min << " et " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valeur;
        }
    }
}

std::string Jeu::lireChaine() const {
    std::string chaine;
    std::getline(std::cin, chaine);
    return chaine;
}

bool Jeu::confirmer(const std::string& question) const {
    std::cout << "\n" << question << " (o/n): ";
    std::string reponse = lireChaine();
    return (reponse == "o" || reponse == "O" || reponse == "oui" || reponse == "Oui");
}

void Jeu::afficherRegles() const {
    Regle::afficherMenuRegles();
}

void Jeu::afficherAide() const {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              ❓ AIDE ❓                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n💰 OR: Utilisé pour acheter des cartes au marché" << std::endl;
    std::cout << "⚔️  COMBAT: Utilisé pour attaquer les adversaires" << std::endl;
    std::cout << "💚 PV: Points de vie, si 0 vous êtes éliminé" << std::endl;

    std::cout << "\n🎴 ZONES:" << std::endl;
    std::cout << "   📚 Pioche: Vos cartes à piocher" << std::endl;
    std::cout << "   ✋ Main: Vos cartes jouables" << std::endl;
    std::cout << "   ⚔️  Zone de jeu: Vos champions actifs" << std::endl;
    std::cout << "   🗑️  Défausse: Vos cartes jouées (remélangées)" << std::endl;
    std::cout << "   💀 Sacrifice: Cartes retirées définitivement" << std::endl;

    std::cout << "\n🏪 MARCHÉ:" << std::endl;
    std::cout << "   5 cartes disponibles + 16 Gemmes de Feu au début" << std::endl;

    std::cout << "\n👤 CHAMPIONS:" << std::endl;
    std::cout << "   ⏸️  EXPEND: Capacité utilisable une fois par tour" << std::endl;
    std::cout << "   🤝 ALLIÉ: Se déclenche quand une carte de même faction est jouée" << std::endl;

    pause();
}

void Jeu::afficherTitre() const {
    clearScreen();
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                        ║" << std::endl;
    std::cout << "║            ⚔️  HERO REALMS ⚔️                          ║" << std::endl;
    std::cout << "║                                                        ║" << std::endl;
    std::cout << "║              Jeu de Cartes de Combat                   ║" << std::endl;
    std::cout << "║                                                        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
}

Joueur* Jeu::selectionnerCible(Joueur* attaquant) const {
    auto adversaires = plateau_.adversairesDe(attaquant);

    if (adversaires.empty()) {
        std::cout << "\n⚠️  Aucun adversaire disponible !" << std::endl;
        return nullptr;
    }

    std::cout << "\n👥 Sélectionnez votre cible:" << std::endl;
    for (size_t i = 0; i < adversaires.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << adversaires[i]->nom() 
                  << " (PV: " << adversaires[i]->pv() << ")";
        
        if (adversaires[i]->aChampionsGarde()) {
            std::cout << " 🛡️ (Gardes actifs)";
        }
        
        std::cout << std::endl;
    }
    std::cout << "  [0] Annuler" << std::endl;

    std::cout << "\nChoix: ";
    int choix = lireEntier(0, static_cast<int>(adversaires.size()));

    if (choix == 0) {
        return nullptr;
    }

    return adversaires[choix - 1];
}