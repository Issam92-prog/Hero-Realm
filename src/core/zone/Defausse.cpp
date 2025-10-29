#include "zone/Defausse.hpp"
#include "cartes/Carte.hpp"
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <algorithm>
#include <map>

// ====== Constructeur & Destructeur ======

Defausse::Defausse() {
}

Defausse::~Defausse() {
    // Note: Les cartes ne sont pas supprimées ici
    // C'est le Joueur qui gère la mémoire de toutes ses cartes
}

// ====== Gestion des Cartes ======

void Defausse::ajouterCarte(Carte* carte) {
    if (carte) {
        cartes_.push_back(carte);
    }
}

void Defausse::ajouterCartes(const std::vector<Carte*>& cartes) {
    cartes_.insert(cartes_.end(), cartes.begin(), cartes.end());
}

std::vector<Carte*> Defausse::vider() {
    std::vector<Carte*> cartes_retirees = cartes_;
    cartes_.clear();
    return cartes_retirees;
}

const Carte* Defausse::voirDerniere() const {
    if (cartes_.empty()) {
        return nullptr;
    }
    return cartes_.back();
}

const Carte* Defausse::voirDessus() const {
    return voirDerniere();
}

Carte* Defausse::retirerDerniere() {
    if (cartes_.empty()) {
        return nullptr;
    }
    
    Carte* carte = cartes_.back();
    cartes_.pop_back();
    return carte;
}

bool Defausse::retirerCarte(Carte* carte) {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        cartes_.erase(it);
        return true;
    }
    return false;
}

// ====== Recherche de Cartes ======

bool Defausse::contient(Carte* carte) const {
    return std::find(cartes_.begin(), cartes_.end(), carte) != cartes_.end();
}

int Defausse::trouverCarte(Carte* carte) const {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        return std::distance(cartes_.begin(), it);
    }
    return -1;
}

int Defausse::compterFaction(int faction) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (static_cast<int>(carte->getFaction()) == faction) {
            count++;
        }
    }
    return count;
}

int Defausse::compterType(int type) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (static_cast<int>(carte->getType()) == type) {
            count++;
        }
    }
    return count;
}

// ====== Affichage ======

void Defausse::afficher(bool afficher_tout) const {
    std::cout << "\n🗑️  Défausse (" << cartes_.size() << " cartes):" << std::endl;
    
    if (cartes_.empty()) {
        std::cout << "   (vide)" << std::endl;
        return;
    }

    if (!afficher_tout) {
        // Affichage résumé : juste les 3 dernières cartes
        afficherDernieres(3);
        if (cartes_.size() > 3) {
            std::cout << "   ... et " << (cartes_.size() - 3) << " autres cartes" << std::endl;
        }
    } else {
        // Affichage complet de toutes les cartes
        for (size_t i = 0; i < cartes_.size(); ++i) {
            const Carte* carte = cartes_[i];
            
            std::string icone_faction = getIconeFaction(static_cast<int>(carte->getFaction()));
            std::string icone_type = getIconeType(static_cast<int>(carte->getType()));
            
            std::cout << "   [" << (i + 1) << "] " 
                      << icone_faction << " " 
                      << icone_type << " "
                      << carte->getNom() << std::endl;
        }
    }
}

void Defausse::afficherDernieres(int n) const {
    if (cartes_.empty()) {
        std::cout << "   (vide)" << std::endl;
        return;
    }

    int debut = std::max(0, static_cast<int>(cartes_.size()) - n);
    
    std::cout << "   Dernières cartes défaussées:" << std::endl;
    for (int i = debut; i < static_cast<int>(cartes_.size()); ++i) {
        const Carte* carte = cartes_[i];
        
        std::string icone_faction = getIconeFaction(static_cast<int>(carte->getFaction()));
        std::string icone_type = getIconeType(static_cast<int>(carte->getType()));
        
        std::cout << "   - " 
                  << icone_faction << " " 
                  << icone_type << " "
                  << carte->getNom() << std::endl;
    }
}

void Defausse::afficherResume() const {
    std::cout << "\n🗑️  Résumé de la Défausse (" << cartes_.size() << " cartes):" << std::endl;
    
    if (cartes_.empty()) {
        std::cout << "   (vide)" << std::endl;
        return;
    }

    // Compter par faction
    std::map<std::string, int> factions;
    factions["⚪ Sans faction"] = 0;
    factions["🛡️  Imperial"] = 0;
    factions["🏹 Guild"] = 0;
    factions["💀 Necros"] = 0;
    factions["🐺 Wild"] = 0;

    // Compter par type
    std::map<std::string, int> types;
    types["⚡ Actions"] = 0;
    types["👤 Champions"] = 0;
    types["🔨 Items"] = 0;

    for (const auto* carte : cartes_) {
        // Faction
        switch(carte->getFaction()) {
            case Faction::IMPERIAL: factions["🛡️  Imperial"]++; break;
            case Faction::GUILD:    factions["🏹 Guild"]++; break;
            case Faction::NECROS:   factions["💀 Necros"]++; break;
            case Faction::WILD:     factions["🐺 Wild"]++; break;
            default:                factions["⚪ Sans faction"]++; break;
        }

        // Type
        switch(carte->getType()) {
            case TypeCarte::ACTION:   types["⚡ Actions"]++; break;
            case TypeCarte::CHAMPION: types["👤 Champions"]++; break;
            case TypeCarte::ITEM:     types["🔨 Items"]++; break;
        }
    }

    // Afficher les factions
    std::cout << "\n   Par faction:" << std::endl;
    for (const auto& [nom, count] : factions) {
        if (count > 0) {
            std::cout << "   - " << nom << ": " << count << std::endl;
        }
    }

    // Afficher les types
    std::cout << "\n   Par type:" << std::endl;
    for (const auto& [nom, count] : types) {
        if (count > 0) {
            std::cout << "   - " << nom << ": " << count << std::endl;
        }
    }
}

std::string Defausse::getIconeFaction(int faction) const {
    switch(faction) {
        case static_cast<int>(Faction::IMPERIAL): return "🛡️";
        case static_cast<int>(Faction::GUILD):    return "🏹";
        case static_cast<int>(Faction::NECROS):   return "💀";
        case static_cast<int>(Faction::WILD):     return "🐺";
        default:                                   return "⚪";
    }
}

std::string Defausse::getIconeType(int type) const {
    switch(type) {
        case static_cast<int>(TypeCarte::ACTION):   return "⚡";
        case static_cast<int>(TypeCarte::CHAMPION): return "👤";
        case static_cast<int>(TypeCarte::ITEM):     return "🔨";
        default:                                     return "❓";
    }
}

// ====== Informations ======

size_t Defausse::taille() const {
    return cartes_.size();
}

bool Defausse::estVide() const {
    return cartes_.empty();
}

const Carte* Defausse::getCarte(size_t index) const {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

// ====== Accès Direct ======

std::vector<Carte*>& Defausse::cartes() {
    return cartes_;
}

const std::vector<Carte*>& Defausse::cartes() const {
    return cartes_;
}

// ====== Opérateurs ======

Carte* Defausse::operator[](size_t index) {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

const Carte* Defausse::operator[](size_t index) const {
    return getCarte(index);
}