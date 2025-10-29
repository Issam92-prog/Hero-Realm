#include "zone/marche.hpp"
#include "cartes/CarteItem.hpp"
#include "enum/Faction.hpp"
#include <iostream>
#include <algorithm>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 g{ std::random_device{}() };
    return g;
}

void Marche::initialiser() {
    // Créer les cartes du marché
    // Cartes basiques : Épée (2 combat, coût 2), Bourse (2 or, coût 3)
    for (int i = 0; i < 4; ++i) {
        deck_marche_.push_back(new CarteItem(1, "Épée", 2, Faction::NONE, 0, 2));
        deck_marche_.push_back(new CarteItem(1, "Bourse", 3, Faction::NONE, 2, 0));
    }
    
    // Mélanger le deck
    std::shuffle(deck_marche_.begin(), deck_marche_.end(), rng());
    
    // Remplir le marché initial
    remplirMarche();
}

void Marche::afficher() const {
    std::cout << "\n=== Marché ===\n";
    for (size_t i = 0; i < cartes_dispo_.size(); ++i) {
        std::cout << "[" << (i+1) << "] ";
        cartes_dispo_[i]->afficher();
        std::cout << "\n";
    }
    std::cout << "\n";
}

Carte* Marche::acheterCarte(size_t index) {
    if (index >= cartes_dispo_.size()) return nullptr;
    
    Carte* carte = cartes_dispo_[index];
    cartes_dispo_.erase(cartes_dispo_.begin() + index);
    
    // Remplir le marché
    remplirMarche();
    
    return carte;
}

void Marche::remplirMarche() {
    while (!deck_marche_.empty() && cartes_dispo_.size() < 5) {
        cartes_dispo_.push_back(deck_marche_.back());
        deck_marche_.pop_back();
    }
}