#include "zone/Pioche.hpp"
#include "cartes/Carte.hpp"
#include <algorithm>
#include <iostream>
#include <random>

// ====== Constructeur & Destructeur ======

Pioche::Pioche() : rng_(std::random_device{}()) {
}

Pioche::~Pioche() {
    // Note: Les cartes ne sont pas supprimées ici
    // C'est le Joueur qui gère la mémoire de toutes ses cartes
}

// ====== Pioche de Cartes ======

std::vector<Carte*> Pioche::piocher(int n, std::vector<Carte*>& defausse) {
    std::vector<Carte*> cartes_piochees;
    
    for (int i = 0; i < n; ++i) {
        Carte* carte = piocherUne(defausse);
        if (carte) {
            cartes_piochees.push_back(carte);
        } else {
            // Impossible de piocher plus (pioche et défausse vides)
            break;
        }
    }
    
    return cartes_piochees;
}

Carte* Pioche::piocherUne(std::vector<Carte*>& defausse) {
    // Vérifier et remélanger si besoin
    if (!verifierEtRemelanger(defausse)) {
        // Impossible de piocher (pioche ET défausse vides)
        return nullptr;
    }
    
    // Piocher la carte du dessus
    Carte* carte = cartes_.back();
    cartes_.pop_back();
    
    return carte;
}

// ====== Gestion de la Pioche ======

void Pioche::ajouterDessus(Carte* carte) {
    if (carte) {
        cartes_.push_back(carte);
    }
}

void Pioche::ajouterDessous(Carte* carte) {
    if (carte) {
        cartes_.insert(cartes_.begin(), carte);
    }
}

void Pioche::melanger() {
    std::shuffle(cartes_.begin(), cartes_.end(), rng_);
}

void Pioche::remelanger(std::vector<Carte*>& defausse) {
    if (defausse.empty()) {
        return;
    }
    
    std::cout << "🔄 Remélange de la défausse dans la pioche..." << std::endl;
    std::cout << "   (" << defausse.size() << " cartes)" << std::endl;
    
    // Transférer toutes les cartes de la défausse vers la pioche
    cartes_.insert(cartes_.end(), defausse.begin(), defausse.end());
    defausse.clear();
    
    // Mélanger la nouvelle pioche
    melanger();
}

// ====== Informations ======

size_t Pioche::taille() const {
    return cartes_.size();
}

bool Pioche::estVide() const {
    return cartes_.empty();
}

void Pioche::afficher() const {
    std::cout << "\n📚 Contenu de la Pioche (" << cartes_.size() << " cartes):" << std::endl;
    
    if (cartes_.empty()) {
        std::cout << "   (vide)" << std::endl;
        return;
    }
    
    // Afficher depuis le dessus (fin du vecteur)
    for (auto it = cartes_.rbegin(); it != cartes_.rend(); ++it) {
        std::cout << "   - " << (*it)->getNom() << std::endl;
    }
}

// ====== Accès Direct ======

std::vector<Carte*>& Pioche::cartes() {
    return cartes_;
}

const std::vector<Carte*>& Pioche::cartes() const {
    return cartes_;
}

// ====== Méthodes Privées ======

bool Pioche::verifierEtRemelanger(std::vector<Carte*>& defausse) {
    // Si la pioche n'est pas vide, on peut piocher
    if (!estVide()) {
        return true;
    }
    
    // Si la pioche est vide mais la défausse a des cartes, remélanger
    if (!defausse.empty()) {
        remelanger(defausse);
        return true;
    }
    
    // Pioche ET défausse vides : impossible de piocher
    std::cout << "⚠️  Impossible de piocher : pioche et défausse vides !" << std::endl;
    return false;
}