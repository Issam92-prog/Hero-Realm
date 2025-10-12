#include "Plateau.hpp"
#include "Joueur/Joueur.hpp"
#include <stdexcept>
#include <memory>

using namespace std;

Joueur* Plateau::ajouterJoueur(unique_ptr<Joueur> j) {
    if (demarree_) throw runtime_error("La partie est déjà démarrée.");
    if (!j) return nullptr;
    joueurs_.push_back(move(j));
    return joueurs_.back().get();
}

Joueur* Plateau::joueurCourant() {
    if (joueurs_.empty()) return nullptr;
    if (idx_ < 0 || (size_t)idx_ >= joueurs_.size()) return nullptr;
    return joueurs_[idx_].get();
}

const Joueur* Plateau::joueurCourant() const {
    if (joueurs_.empty()) return nullptr;
    if (idx_ < 0 || (size_t)idx_ >= joueurs_.size()) return nullptr;
    return joueurs_[idx_].get();
}

Joueur* Plateau::adversaire() {
    if (joueurs_.size() != 2) return nullptr;
    return (idx_ == 0) ? joueurs_[1].get() : joueurs_[0].get();
}

const Joueur* Plateau::adversaire() const {
    if (joueurs_.size() != 2) return nullptr;
    return (idx_ == 0) ? joueurs_[1].get() : joueurs_[0].get();
}

void Plateau::demarrer() {
    if (demarree_) return;
    if (joueurs_.size() < 2)
        throw runtime_error("Il faut au moins 2 joueurs pour démarrer.");
    demarree_ = true;
    terminee_ = false;
    idx_ = 0;

    if (auto* j = joueurCourant()) j->debutDeTour();
}

void Plateau::finDeTour() {
    if (!demarree_ || terminee_) return;

    if (auto* j = joueurCourant()) j->finDeTour();
    changerTour();
    if (auto* j = joueurCourant()) j->debutDeTour();

    const Joueur* a = adversaire();
    const Joueur* c = joueurCourant();
    if ((a && a->estMort()) || (c && c->estMort())) terminee_ = true;
}

void Plateau::changerTour() {
    if (!demarree_ || terminee_ || joueurs_.empty()) return;
    idx_ = (idx_ + 1) % static_cast<int>(joueurs_.size());
}
