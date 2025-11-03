#include "zone/MainJoueur.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteAction.hpp"
#include "cartes/cartechampion.hpp"
#include "cartes/CarteItem.hpp"
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <algorithm>

// ====== Constructeur & Destructeur ======

MainJoueur::MainJoueur() {
}

MainJoueur::~MainJoueur() {
    // Note: Les cartes ne sont pas supprimées ici
    // C'est le Joueur qui gère la mémoire de toutes ses cartes
}

// ====== Gestion des Cartes ======

void MainJoueur::ajouterCarte(Carte* carte) {
    if (carte) {
        cartes_.push_back(carte);
    }
}

Carte* MainJoueur::retirerCarte(size_t index) {
    if (index >= cartes_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return nullptr;
    }

    Carte* carte = cartes_[index];
    cartes_.erase(cartes_.begin() + index);
    return carte;
}

bool MainJoueur::retirerCarte(Carte* carte) {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        cartes_.erase(it);
        return true;
    }
    return false;
}

std::vector<Carte*> MainJoueur::vider() {
    std::vector<Carte*> cartes_retirees = cartes_;
    cartes_.clear();
    return cartes_retirees;
}

void MainJoueur::defausserTout(std::vector<Carte*>& defausse) {
    defausse.insert(defausse.end(), cartes_.begin(), cartes_.end());
    cartes_.clear();
}

// ====== Recherche de Cartes ======

int MainJoueur::trouverCarte(Carte* carte) const {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        return std::distance(cartes_.begin(), it);
    }
    return -1;
}

int MainJoueur::compterFaction(int faction) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (static_cast<int>(carte->getFaction()) == faction) {
            count++;
        }
    }
    return count;
}

bool MainJoueur::estJouable(size_t index, int or_disponible) const {
    if (index >= cartes_.size()) {
        return false;
    }
    
    const Carte* carte = cartes_[index];
    return carte->getCout() <= or_disponible;
}

// ====== Affichage ======

void MainJoueur::afficher(bool afficher_details) const {
    std::cout << "\n✋ Main (" << cartes_.size() << " cartes):" << std::endl;
    
    if (cartes_.empty()) {
        std::cout << "   (vide)" << std::endl;
        return;
    }

    for (size_t i = 0; i < cartes_.size(); ++i) {
        const Carte* carte = cartes_[i];
        
        // Icônes
        std::string icone_faction = getIconeFaction(static_cast<int>(carte->getFaction()));
        std::string icone_type = getIconeType(static_cast<int>(carte->getType()));
        
        // Affichage compact
        std::cout << "   [" << (i + 1) << "] " 
                  << icone_faction << " " 
                  << icone_type << " "
                  << carte->getNom();
        
        // Coût si > 0
        if (carte->getCout() > 0) {
            std::cout << " (Coût: " << carte->getCout() << ")";
        }
        
        std::cout << std::endl;
        
        // Détails si demandé
        if (afficher_details) {
            std::cout << "       " << carte->getDescription() << std::endl;
        }
    }
}

void MainJoueur::afficherCarte(size_t index) const {
    if (index >= cartes_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return;
    }

    const Carte* carte = cartes_[index];
    std::cout << "\n";
    carte->afficher();
}

std::string MainJoueur::getIconeFaction(int faction) const {
    switch(faction) {
        case static_cast<int>(Faction::IMPERIAL): return "👑";
        case static_cast<int>(Faction::GUILD):    return "🏹";
        case static_cast<int>(Faction::NECROS):   return "💀";
        case static_cast<int>(Faction::WILD):     return "🐺";
        default:                                   return "⚪";
    }
}

std::string MainJoueur::getIconeType(int type) const {
    switch(type) {
        case static_cast<int>(TypeCarte::ACTION):   return "⚡";
        case static_cast<int>(TypeCarte::CHAMPION): return "👤";
        case static_cast<int>(TypeCarte::ITEM):     return "🔨";
        default:                                     return "❓";
    }
}

// ====== Informations ======

size_t MainJoueur::taille() const {
    return cartes_.size();
}

bool MainJoueur::estVide() const {
    return cartes_.empty();
}

const Carte* MainJoueur::getCarte(size_t index) const {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

Carte* MainJoueur::getCarte(size_t index) {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

// ====== Accès Direct ======

std::vector<Carte*>& MainJoueur::cartes() {
    return cartes_;
}

const std::vector<Carte*>& MainJoueur::cartes() const {
    return cartes_;
}

// ====== Opérateurs ======

Carte* MainJoueur::operator[](size_t index) {
    return getCarte(index);
}

const Carte* MainJoueur::operator[](size_t index) const {
    return getCarte(index);
}