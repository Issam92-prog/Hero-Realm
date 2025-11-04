#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include "Regle.hpp"
#include <iostream>
#include <algorithm>

// ====== Constructeur & Destructeur ======

Plateau::Plateau() 
    : joueur_actif_index_(0), 
      numero_tour_(0), 
      partie_demarree_(false),
      prochain_id_(1) {
}

Plateau::~Plateau() {
    nettoyer();
}

// ====== Initialisation ======

void Plateau::initialiser(const std::vector<std::string>& noms_joueurs, int pv_initial) {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        🎮 Initialisation de Hero Realms 🎮            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    // Nettoyer si déjà initialisé
    nettoyer();

    // Créer les joueurs avec la distribution de cartes appropriée
    std::cout << "\n👥 Création des joueurs..." << std::endl;
    int position = 1;
    int nb_joueurs = noms_joueurs.size();
    
    for (const auto& nom : noms_joueurs) {
        int nb_cartes = Regle::getCartesDepart(position, nb_joueurs);
        ajouterJoueur(nom, pv_initial, nb_cartes);
        position++;
    }

    // Initialiser le marché
    marche_.initialiser();

    std::cout << "\n✅ Plateau initialisé avec " << joueurs_.size() << " joueur(s)" << std::endl;
}

Joueur* Plateau::ajouterJoueur(const std::string& nom, int pv_initial, int nb_cartes_initiales) {
    Joueur::Id id = genererIdJoueur();
    
    // Créer le joueur sans initialiser le deck automatiquement
    // (on le fera manuellement avec le bon nombre de cartes)
    Joueur* joueur = new Joueur(id, nom, pv_initial);
    
    // Le constructeur a déjà appelé initialiserDeckDeBase(5)
    // Si on a besoin d'un nombre différent, on ajuste
    if (nb_cartes_initiales != 5) {
        // Vider la main actuelle
        while (!joueur->main().estVide()) {
            Carte* carte = joueur->main().retirerCarte(static_cast<size_t>(0));
            joueur->pioche().cartes().push_back(carte);
        }
        // Remélanger et piocher le bon nombre
        joueur->pioche().melanger();
        joueur->piocher(nb_cartes_initiales);
    }
    
    joueurs_.push_back(joueur);
    
    std::cout << "   ✅ Joueur #" << id << ": " << nom << " (PV: " << pv_initial << ", Main: " << nb_cartes_initiales << " cartes)" << std::endl;
    
    return joueur;
}

void Plateau::nettoyer() {
    // Supprimer tous les joueurs
    for (auto* joueur : joueurs_) {
        delete joueur;
    }
    joueurs_.clear();

    // Nettoyer le marché
    marche_.nettoyer();

    // Réinitialiser les variables
    joueur_actif_index_ = 0;
    numero_tour_ = 0;
    partie_demarree_ = false;
    prochain_id_ = 1;
}

Joueur::Id Plateau::genererIdJoueur() {
    return prochain_id_++;
}

// ====== Gestion des Tours ======

void Plateau::demarrerPartie() {
    if (joueurs_.empty()) {
        std::cout << "⚠️  Aucun joueur ! Impossible de démarrer la partie." << std::endl;
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🎲 DÉBUT DE LA PARTIE 🎲                  ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    partie_demarree_ = true;
    joueur_actif_index_ = 0;
    numero_tour_ = 1;

    std::cout << "\n🎯 " << joueurs_[0]->nom() << " commence !" << std::endl;
}

void Plateau::joueurSuivant() {
    if (joueurs_.empty()) return;

    // Passer au joueur suivant (en sautant les joueurs morts)
    int tentatives = 0;
    do {
        joueur_actif_index_ = (joueur_actif_index_ + 1) % joueurs_.size();
        tentatives++;

        // Si on a fait le tour complet, incrémenter le numéro de tour
        if (joueur_actif_index_ == 0) {
            numero_tour_++;
        }

        // Sécurité : éviter boucle infinie si tous morts
        if (tentatives > static_cast<int>(joueurs_.size())) {
            break;
        }

    } while (joueurs_[joueur_actif_index_]->estMort());

    std::cout << "\n🔄 Tour suivant : " << joueurActif()->nom() << std::endl;
}

Joueur* Plateau::joueurActif() {
    if (joueurs_.empty()) return nullptr;
    return joueurs_[joueur_actif_index_];
}

const Joueur* Plateau::joueurActif() const {
    if (joueurs_.empty()) return nullptr;
    return joueurs_[joueur_actif_index_];
}

int Plateau::numeroTour() const {
    return numero_tour_;
}

int Plateau::indexJoueurActif() const {
    return joueur_actif_index_;
}

// ====== Gestion de la Partie ======

bool Plateau::partieTerminee() const {
    int nb_vivants = nbJoueursVivants();
    return nb_vivants <= 1;
}

std::vector<Joueur*> Plateau::gagnants() const {
    std::vector<Joueur*> gagnants_liste;
    
    for (auto* joueur : joueurs_) {
        if (!joueur->estMort()) {
            gagnants_liste.push_back(joueur);
        }
    }
    
    return gagnants_liste;
}

int Plateau::nbJoueursVivants() const {
    int count = 0;
    for (const auto* joueur : joueurs_) {
        if (!joueur->estMort()) {
            count++;
        }
    }
    return count;
}

std::vector<Joueur*> Plateau::adversaires() const {
    return adversairesDe(joueurActif());
}

std::vector<Joueur*> Plateau::adversairesDe(const Joueur* joueur) const {
    std::vector<Joueur*> adv;
    
    for (auto* j : joueurs_) {
        if (j != joueur && !j->estMort()) {
            adv.push_back(j);
        }
    }
    
    return adv;
}

// ====== Accès au Marché ======

Marche& Plateau::marche() {
    return marche_;
}

const Marche& Plateau::marche() const {
    return marche_;
}

// ====== Accès aux Joueurs ======

Joueur* Plateau::getJoueur(size_t index) {
    if (index >= joueurs_.size()) {
        return nullptr;
    }
    return joueurs_[index];
}

const Joueur* Plateau::getJoueur(size_t index) const {
    if (index >= joueurs_.size()) {
        return nullptr;
    }
    return joueurs_[index];
}

Joueur* Plateau::getJoueurParId(Joueur::Id id) {
    for (auto* joueur : joueurs_) {
        if (joueur->id() == id) {
            return joueur;
        }
    }
    return nullptr;
}

size_t Plateau::nbJoueurs() const {
    return joueurs_.size();
}

const std::vector<Joueur*>& Plateau::joueurs() const {
    return joueurs_;
}

// ====== Affichage ======

void Plateau::afficher() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              📊 ÉTAT DU PLATEAU 📊                     ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n🎲 Tour n°" << numero_tour_ << std::endl;
    std::cout << "👤 Joueur actif: " << joueurActif()->nom() << std::endl;
    std::cout << "👥 Joueurs vivants: " << nbJoueursVivants() << "/" << joueurs_.size() << std::endl;

    afficherJoueurs();
    afficherMarche(false);
}

void Plateau::afficherJoueurs() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                  👥 JOUEURS                            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    for (size_t i = 0; i < joueurs_.size(); ++i) {
        const Joueur* joueur = joueurs_[i];
        
        // Indicateur joueur actif
        std::string actif = (static_cast<int>(i) == joueur_actif_index_) ? "👉 " : "   ";
        
        // Statut
        std::string statut = joueur->estMort() ? "💀 MORT" : "💚 VIVANT";
        
        std::cout << actif << "Joueur #" << joueur->id() << ": " 
                  << joueur->nom() << " - " << statut;
        
        if (!joueur->estMort()) {
            std::cout << " (PV: " << joueur->pv() << ")";
        }
        
        std::cout << std::endl;
        
        // Détails si joueur actif
        if (static_cast<int>(i) == joueur_actif_index_ && !joueur->estMort()) {
            std::cout << "      💰 Or: " << joueur->orTour() << " | "
                      << "⚔️  Combat: " << joueur->combatTour() << " | "
                      << "✋ Main: " << joueur->main().taille() << " | "
                      << "⚔️  Champions: " << joueur->zoneDeJeu().taille() << std::endl;
        }
    }
}

void Plateau::afficherMarche(bool afficher_details) const {
    marche_.afficher(afficher_details);
}

void Plateau::afficherStatistiques() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            📊 STATISTIQUES DE LA PARTIE 📊             ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n🎲 Tour actuel: " << numero_tour_ << std::endl;
    std::cout << "👥 Nombre de joueurs: " << joueurs_.size() << std::endl;
    std::cout << "💚 Joueurs vivants: " << nbJoueursVivants() << std::endl;
    std::cout << "💀 Joueurs éliminés: " << (joueurs_.size() - nbJoueursVivants()) << std::endl;

    // Statistiques du marché
    std::cout << "\n🏪 Marché:" << std::endl;
    std::cout << "   📦 Cartes disponibles: " << marche_.nbCartesDisponibles() << "/5" << std::endl;
    std::cout << "   📚 Cartes restantes: " << marche_.nbCartesDeck() << std::endl;
    std::cout << "   🗑️  Cartes défaussées: " << marche_.nbCartesDefaussees() << std::endl;

    // Statistiques des joueurs
    std::cout << "\n👥 Détails des joueurs:" << std::endl;
    for (const auto* joueur : joueurs_) {
        std::cout << "\n   " << joueur->nom() << ":" << std::endl;
        std::cout << "      💚 PV: " << joueur->pv() << std::endl;
        
        if (!joueur->estMort()) {
            int total_cartes = joueur->pioche().taille() + 
                              joueur->main().taille() + 
                              joueur->defausse().taille() + 
                              joueur->zoneDeJeu().taille() +
                              joueur->sacrifice().taille();
            
            std::cout << "      🎴 Cartes totales: " << total_cartes << std::endl;
            std::cout << "      💀 Cartes sacrifiées: " << joueur->sacrifice().taille() << std::endl;
            std::cout << "      ⚔️  Champions en jeu: " << joueur->zoneDeJeu().taille() << std::endl;
        }
    }
}

void Plateau::afficherClassement() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                  🏆 CLASSEMENT 🏆                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    // Trier les joueurs par PV (du plus élevé au plus bas)
    std::vector<const Joueur*> joueurs_tries = {joueurs_.begin(), joueurs_.end()};
    std::sort(joueurs_tries.begin(), joueurs_tries.end(), 
        [](const Joueur* a, const Joueur* b) {
            return a->pv() > b->pv();
        }
    );

    int rang = 1;
    for (const auto* joueur : joueurs_tries) {
        std::string medaille;
        if (rang == 1) medaille = "🥇";
        else if (rang == 2) medaille = "🥈";
        else if (rang == 3) medaille = "🥉";
        else medaille = "   ";

        std::string statut = joueur->estMort() ? "💀" : "💚";

        std::cout << medaille << " #" << rang << " - " 
                  << joueur->nom() << " " << statut 
                  << " (PV: " << joueur->pv() << ")" << std::endl;

        rang++;
    }
}

// ====== Opérateurs ======

Joueur* Plateau::operator[](size_t index) {
    return getJoueur(index);
}

const Joueur* Plateau::operator[](size_t index) const {
    return getJoueur(index);
}