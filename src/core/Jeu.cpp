#include "Jeu.hpp"
#include "Regle.hpp"
#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteAction.hpp"
#include "cartes/cartechampion.hpp"
#include "cartes/CarteItem.hpp"
#include <iostream>
#include <limits>

// ====== Constructeur & Destructeur ======

Jeu::Jeu() 
    : jeu_en_cours_(false), 
      quitter_(false),
      nb_joueurs_(2),
      pv_initial_(50) {
}

Jeu::~Jeu() {
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
                std::cout << "\n📊 Crédits:" << std::endl;
                std::cout << "   Hero Realms - Jeu de cartes" << std::endl;
                std::cout << "   Développé par: Issam et Alexandre" << std::endl;
                std::cout << "   Date: 2025-10-29" << std::endl;
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

        // Vérifier la fin de partie
        if (plateau_.partieTerminee()) {
            jeu_en_cours_ = false;
            break;
        }

        // Passer au joueur suivant
        plateau_.joueurSuivant();
    }

    // Afficher les résultats
    afficherResultats();
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

        int choix = lireEntier(1, 6);

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
                joueur->afficherStatistiques();
                pause();
                break;
            case 5:
                afficherAide();
                break;
            case 6:
                if (confirmer("Êtes-vous sûr de vouloir terminer votre tour ?")) {
                    joueur->finDeTour();
                    tour_termine = true;
                }
                break;
        }
    }
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

    std::cout << "\nQuelle carte voulez-vous jouer ? (0 pour annuler): ";
    int choix = lireEntier(0, static_cast<int>(joueur->main().taille()));

    if (choix == 0) {
        return;
    }

    if (jouerCarte(joueur, choix - 1)) {
        std::cout << "\n✅ Carte jouée avec succès !" << std::endl;
    } else {
        std::cout << "\n⚠️  Impossible de jouer cette carte !" << std::endl;
    }

    pause();
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

// ====== Actions de Jeu ======

bool Jeu::jouerCarte(Joueur* joueur, int index) {
    Carte* carte = joueur->main().getCarte(index);
    if (!carte) {
        return false;
    }

    // Retirer la carte de la main
    joueur->main().retirerCarte(index);

    // Jouer la carte
    carte->jouer(joueur);

    // Gestion selon le type de carte
    CarteChampion* champion = dynamic_cast<CarteChampion*>(carte);
    if (champion) {
        // Les champions vont dans la zone de jeu
        joueur->zoneDeJeu().ajouterChampion(champion);
        std::cout << "✅ " << champion->getNom() << " entre en jeu !" << std::endl;
    } else {
        // Les actions/items vont en défausse
        joueur->defausse().ajouterCarte(carte);
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
    std::cout << "  [3] 📊 Crédits" << std::endl;
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
    std::cout << "  [4] 📊 Voir Statistiques" << std::endl;
    std::cout << "  [5] ❓ Aide" << std::endl;
    std::cout << "  [6] ✅ Terminer le Tour" << std::endl;
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
    std::cout << "\n\n\n\n\n\n\n\n\n\n";
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
    std::cout << "   5 cartes disponibles + Gemmes de Feu infinies" << std::endl;

    pause();
}

void Jeu::afficherTitre() const {
    clearScreen();
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                        ║" << std::endl;
    std::cout << "║            ⚔️  HERO REALMS ⚔️                         ║" << std::endl;
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