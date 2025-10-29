#include "Joueur/Joueur.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteItem.hpp"
#include "enum/Faction.hpp"
#include <algorithm>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 g{ std::random_device{}() };
    return g;
}

// ====== Ctor/Dtor ======
Joueur::Joueur(Id id, const std::string& nom, int pv_initial)
    : id_(id), nom_(nom), pv_(pv_initial) {
    initialiserDeckDeBase();
}

Joueur::~Joueur() {
    // Nettoyer toutes les cartes
    for (auto* c : main_) delete c;
    for (auto* c : deck_) delete c;
    for (auto* c : defausse_) delete c;
}

// ====== Identité ======
Joueur::Id Joueur::id() const { return id_; }
const std::string& Joueur::nom() const { return nom_; }

// ====== PV ======
int Joueur::pv() const { return pv_; }
void Joueur::soigner(int v) { pv_ += v; }
void Joueur::subirDegats(int v) { pv_ = std::max(0, pv_ - std::max(0, v)); }
bool Joueur::estMort() const { return pv_ <= 0; }

// ====== Ressources ======
int  Joueur::orTour() const { return or_tour_; }
int  Joueur::combatTour() const { return combat_tour_; }
void Joueur::ajouterOr(int n) { or_tour_ += n; }
void Joueur::ajouterCombat(int n) { combat_tour_ += n; }
void Joueur::resetRessources() { or_tour_ = 0; combat_tour_ = 0; }

// ====== Cycle ======
void Joueur::debutDeTour() {
    resetRessources();
    // (effets début de tour à ajouter plus tard)
}

void Joueur::finDeTour() {
    // main -> défausse
    for (auto* c : main_) defausse_.push_back(c);
    main_.clear();
    // reset ressources
    resetRessources();
    // repioche 5
    piocher(5);
}

// ====== Pioche/main/défausse ======
void Joueur::piocher(int n) {
    while (n--) {
        if (deck_.empty()) {
            if (defausse_.empty()) return;
            std::shuffle(defausse_.begin(), defausse_.end(), rng());
            // on remet toute la défausse sur le deck
            while (!defausse_.empty()) { deck_.push_back(defausse_.back()); defausse_.pop_back(); }
        }
        main_.push_back(deck_.back());
        deck_.pop_back();
    }
}

void Joueur::initialiserDeckDeBase() {
    // Création d'un deck de base : 7 Or (1 or), 3 Dague (1 combat)
    for (int i = 0; i < 7; ++i) deck_.push_back(new CarteItem(1, "Or", 0, Faction::NONE, 1, 0));
    for (int i = 0; i < 3; ++i) deck_.push_back(new CarteItem(1, "Dague", 0, Faction::NONE, 0, 1));

    std::shuffle(deck_.begin(), deck_.end(), rng());
    piocher(5);
}

// ====== Accès ======
std::vector<Carte*>& Joueur::main() { return main_; }
std::vector<Carte*>& Joueur::deck() { return deck_; }
std::vector<Carte*>& Joueur::defausse() { return defausse_; }

const std::vector<Carte*>& Joueur::main() const { return main_; }
const std::vector<Carte*>& Joueur::deck() const { return deck_; }
const std::vector<Carte*>& Joueur::defausse() const { return defausse_; }
