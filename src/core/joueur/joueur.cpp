#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteItem.hpp"
#include "cartes/cartechampion.hpp"
#include "enum/Faction.hpp"
#include <algorithm>
#include <iostream>

// ====== Ctor/Dtor ======
Joueur::Joueur(Id id, const std::string& nom, int pv_initial)
    : id_(id), nom_(nom), pv_(pv_initial) {
    initialiserDeckDeBase();
}

Joueur::~Joueur() {
    // Nettoyer toutes les cartes de toutes les zones
    // Note: Chaque zone contient des pointeurs vers les cartes,
    // mais une carte peut être dans une seule zone à la fois.
    // On doit éviter les double-delete.
    
    // Collecter tous les pointeurs uniques
    std::vector<Carte*> toutes_cartes;
    
    // Ajouter les cartes de chaque zone
    for (auto* c : main_.cartes()) toutes_cartes.push_back(c);
    for (auto* c : pioche_.cartes()) toutes_cartes.push_back(c);
    for (auto* c : defausse_.cartes()) toutes_cartes.push_back(c);
    for (auto* c : zone_de_jeu_.champions()) toutes_cartes.push_back(c);
    for (auto* c : sacrifice_.cartes()) toutes_cartes.push_back(c);
    
    // Supprimer toutes les cartes
    for (auto* c : toutes_cartes) {
        delete c;
    }
}

// ====== Identité ======
Joueur::Id Joueur::id() const { return id_; }
const std::string& Joueur::nom() const { return nom_; }

// ====== PV ======
int Joueur::pv() const { return pv_; }
void Joueur::soigner(int v) { 
    pv_ += v;
    std::cout << "💚 " << nom_ << " récupère " << v << " PV (Total: " << pv_ << ")" << std::endl;
}
void Joueur::subirDegats(int v) { 
    int degats = std::max(0, v);
    pv_ = std::max(0, pv_ - degats);
    std::cout << "💔 " << nom_ << " subit " << degats << " dégâts (PV restants: " << pv_ << ")" << std::endl;
}
bool Joueur::estMort() const { return pv_ <= 0; }

// ====== Ressources ======
int  Joueur::orTour() const { return or_tour_; }
int  Joueur::combatTour() const { return combat_tour_; }
void Joueur::ajouterOr(int n) { 
    or_tour_ += n;
    if (n > 0) {
        std::cout << "💰 +" << n << " or (Total: " << or_tour_ << ")" << std::endl;
    }
}
void Joueur::ajouterCombat(int n) { 
    combat_tour_ += n;
    if (n > 0) {
        std::cout << "⚔️  +" << n << " combat (Total: " << combat_tour_ << ")" << std::endl;
    }
}
void Joueur::resetRessources() { 
    or_tour_ = 0; 
    combat_tour_ = 0; 
}

// ====== Cycle ======
void Joueur::debutDeTour() {
    std::cout << "\n╔════════════════════════════════════╗" << std::endl;
    std::cout << "║  Tour de " << nom_ << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    
    resetRessources();
    reinitialiserFactionsJouees();  // important pour les effets alliés
    preparerChampions();
}

void Joueur::finDeTour() {
    std::cout << "\n--- Fin du tour de " << nom_ << " ---" << std::endl;
    
    // Défausser tous les champions morts
    defausserChampionsMorts();
    
    // Main -> défausse
    main_.defausserTout(defausse_.cartes());
    
    // Reset ressources
    resetRessources();
    
    // Repioche 5
    piocher(5);
}

// ====== Pioche ======
void Joueur::piocher(int n) {
    auto cartes_piochees = pioche_.piocher(n, defausse_.cartes());
    for (auto* carte : cartes_piochees) {
        main_.ajouterCarte(carte);
    }
    
    if (!cartes_piochees.empty()) {
        std::cout << "🎴 " << nom_ << " pioche " << cartes_piochees.size() << " carte(s)" << std::endl;
    }
}

void Joueur::initialiserDeckDeBase() {
    std::cout << "🎲 Initialisation du deck de " << nom_ << "..." << std::endl;
    
    // Création d'un deck de base : 7 Or (1 or), 3 Dague (1 combat)
    for (int i = 0; i < 7; ++i) {
        pioche_.cartes().push_back(new CarteItem(1, "Or", 0, Faction::NONE, 1, 0));
    }
    for (int i = 0; i < 3; ++i) {
        pioche_.cartes().push_back(new CarteItem(1, "Dague", 0, Faction::NONE, 0, 1));
    }

    pioche_.melanger();
    piocher(5);
    
    std::cout << "✅ Deck initialisé (7 Or + 3 Dague)" << std::endl;
}

// ====== Gestion des Champions ======
void Joueur::jouerChampion(CarteChampion* champion) {
    // Retirer le champion de la main
    if (!main_.retirerCarte(champion)) {
        std::cout << "⚠️  Champion non trouvé dans la main !" << std::endl;
        return;
    }
    
    // Ajouter à la zone de jeu
    zone_de_jeu_.ajouterChampion(champion);
    
    // Jouer le champion (effets d'entrée en jeu)
    champion->jouer(this);
    
    std::cout << "✅ " << champion->getNom() << " entre en jeu !" << std::endl;
}

void Joueur::preparerChampions() {
    // Au début du tour, tous les champions sont prêts (pas expended)
    zone_de_jeu_.preparerTous();
    
    if (!zone_de_jeu_.estVide()) {
        std::cout << "⚡ " << zone_de_jeu_.taille() << " champion(s) préparé(s)" << std::endl;
    }
}

void Joueur::defausserChampionsMorts() {
    // Retire automatiquement les champions morts et les met en défausse
    int nb_morts = zone_de_jeu_.retirerMorts(defausse_.cartes());
    
    if (nb_morts > 0) {
        std::cout << "💀 " << nb_morts << " champion(s) vaincu(s)" << std::endl;
    }
}

bool Joueur::aChampionsGarde() const {
    return zone_de_jeu_.aChampionsGarde();
}

// ====== Gestion du Sacrifice ======
void Joueur::sacrifierCarte(Carte* carte) {
    // Retirer la carte de la main
    if (!main_.retirerCarte(carte)) {
        std::cout << "⚠️  Carte non trouvée dans la main !" << std::endl;
        return;
    }
    
    // Mettre la carte dans la zone sacrifice (retirée définitivement)
    sacrifice_.ajouterCarte(carte);
}

// ====== Affichage ======
void Joueur::afficherZones() const {
    std::cout << "\n╔════════════════════════════════════╗" << std::endl;
    std::cout << "║  Zones de " << nom_ << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n📊 Vue d'ensemble:" << std::endl;
    std::cout << "   💚 PV: " << pv_ << std::endl;
    std::cout << "   💰 Or: " << or_tour_ << std::endl;
    std::cout << "   ⚔️  Combat: " << combat_tour_ << std::endl;
    std::cout << "   📚 Pioche: " << pioche_.taille() << " cartes" << std::endl;
    
    // Afficher la main
    main_.afficher(false);
    
    // Afficher la zone de jeu
    zone_de_jeu_.afficher(false);
    
    // Afficher la défausse
    defausse_.afficher(false);
    
    // Afficher zone sacrifice
    if (!sacrifice_.estVide()) {
        sacrifice_.afficher(false);
    } else {
        std::cout << "\n💀 Zone Sacrifice: (aucune carte sacrifiée)" << std::endl;
    }
}

void Joueur::afficherMain() const {
    main_.afficher(true);
}

void Joueur::afficherChampions() const {
    zone_de_jeu_.afficher(true);
}

void Joueur::afficherStatistiques() const {
    std::cout << "\n📊 Statistiques de " << nom_ << ":" << std::endl;
    std::cout << "   💚 Points de vie: " << pv_ << std::endl;
    std::cout << "   💰 Or du tour: " << or_tour_ << std::endl;
    std::cout << "   ⚔️  Combat du tour: " << combat_tour_ << std::endl;
    std::cout << "\n   📦 Cartes totales:" << std::endl;
    std::cout << "      - Pioche: " << pioche_.taille() << std::endl;
    std::cout << "      - Main: " << main_.taille() << std::endl;
    std::cout << "      - Zone de jeu: " << zone_de_jeu_.taille() << std::endl;
    std::cout << "      - Défausse: " << defausse_.taille() << std::endl;
    std::cout << "      - Sacrifiées: " << sacrifice_.taille() << std::endl;
    
    int total = pioche_.taille() + main_.taille() + zone_de_jeu_.taille() + 
                defausse_.taille() + sacrifice_.taille();
    std::cout << "      - TOTAL: " << total << std::endl;
    
    if (!zone_de_jeu_.estVide()) {
        std::cout << "\n   ⚔️  Champions:" << std::endl;
        std::cout << "      - Vivants: " << zone_de_jeu_.compterVivants() << "/" << zone_de_jeu_.taille() << std::endl;
        std::cout << "      - Gardes: " << zone_de_jeu_.compterGardes() << std::endl;
        std::cout << "      - Défense totale: " << zone_de_jeu_.defenseTotal() << std::endl;
    }
}

// ====== Accesseurs des Zones (non-const) ======
Pioche& Joueur::pioche() { return pioche_; }
MainJoueur& Joueur::main() { return main_; }
ZoneDeJeu& Joueur::zoneDeJeu() { return zone_de_jeu_; }
Defausse& Joueur::defausse() { return defausse_; }
Sacrifice& Joueur::sacrifice() { return sacrifice_; }

// ====== Accesseurs des Zones (const) ======
const Pioche& Joueur::pioche() const { return pioche_; }
const MainJoueur& Joueur::main() const { return main_; }
const ZoneDeJeu& Joueur::zoneDeJeu() const { return zone_de_jeu_; }
const Defausse& Joueur::defausse() const { return defausse_; }
const Sacrifice& Joueur::sacrifice() const { return sacrifice_; }

// ====== GESTION DES EFFETS ALLIÉS ======

bool Joueur::aJoueFaction(Faction faction) const {
    for (const auto& f : factions_jouees_ce_tour_) {
        if (f == faction) {
            return true;
        }
    }
    return false;
}

void Joueur::enregistrerFactionJouee(Faction faction) {
    factions_jouees_ce_tour_.push_back(faction);
}

void Joueur::reinitialiserFactionsJouees() {
    factions_jouees_ce_tour_.clear();
}