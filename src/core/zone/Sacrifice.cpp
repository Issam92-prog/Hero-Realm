#include "zone/Sacrifice.hpp"
#include "cartes/Carte.hpp"
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <algorithm>
#include <map>

// ====== Constructeur & Destructeur ======

Sacrifice::Sacrifice() {
}

Sacrifice::~Sacrifice() {
    // Note: Les cartes ne sont pas supprimées ici
    // C'est le Joueur qui gère la mémoire de toutes ses cartes
}

// ====== Gestion des Cartes ======

void Sacrifice::ajouterCarte(Carte* carte) {
    if (carte) {
        cartes_.push_back(carte);
        std::cout << "💀 " << carte->getNom() << " est sacrifié (retiré du jeu définitivement)" << std::endl;
    }
}

void Sacrifice::ajouterCartes(const std::vector<Carte*>& cartes) {
    for (auto* carte : cartes) {
        ajouterCarte(carte);
    }
}

std::vector<Carte*> Sacrifice::vider() {
    std::vector<Carte*> cartes_retirees = cartes_;
    cartes_.clear();
    return cartes_retirees;
}

const Carte* Sacrifice::voirDerniere() const {
    if (cartes_.empty()) {
        return nullptr;
    }
    return cartes_.back();
}

bool Sacrifice::retirerCarte(Carte* carte) {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        cartes_.erase(it);
        return true;
    }
    return false;
}

// ====== Recherche de Cartes ======

bool Sacrifice::contient(Carte* carte) const {
    return std::find(cartes_.begin(), cartes_.end(), carte) != cartes_.end();
}

int Sacrifice::trouverCarte(Carte* carte) const {
    auto it = std::find(cartes_.begin(), cartes_.end(), carte);
    if (it != cartes_.end()) {
        return std::distance(cartes_.begin(), it);
    }
    return -1;
}

int Sacrifice::compterFaction(int faction) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (static_cast<int>(carte->getFaction()) == faction) {
            count++;
        }
    }
    return count;
}

int Sacrifice::compterType(int type) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (static_cast<int>(carte->getType()) == type) {
            count++;
        }
    }
    return count;
}

int Sacrifice::compterCarte(const std::string& nom_carte) const {
    int count = 0;
    for (const auto* carte : cartes_) {
        if (carte->getNom() == nom_carte) {
            count++;
        }
    }
    return count;
}

// ====== Affichage ======

void Sacrifice::afficher(bool afficher_tout) const {
    std::cout << "\n💀 Zone Sacrifice (" << cartes_.size() << " cartes retirées du jeu):" << std::endl;
    
    if (cartes_.empty()) {
        std::cout << "   (aucune carte sacrifiée)" << std::endl;
        return;
    }

    if (!afficher_tout) {
        // Affichage résumé
        afficherResume();
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

void Sacrifice::afficherResume() const {
    if (cartes_.empty()) {
        std::cout << "   (aucune carte sacrifiée)" << std::endl;
        return;
    }

    // Compter par nom de carte
    std::map<std::string, int> compteur;
    for (const auto* carte : cartes_) {
        compteur[carte->getNom()]++;
    }

    std::cout << "   Cartes sacrifiées:" << std::endl;
    for (const auto& [nom, count] : compteur) {
        std::cout << "   - " << nom << " x" << count << std::endl;
    }
}

void Sacrifice::afficherStatistiques() const {
    std::cout << "\n💀 Statistiques de Sacrifice:" << std::endl;
    std::cout << "   Total: " << cartes_.size() << " cartes retirées du jeu" << std::endl;
    
    if (cartes_.empty()) {
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

    // Cartes les plus sacrifiées
    std::map<std::string, int> compteur;
    for (const auto* carte : cartes_) {
        compteur[carte->getNom()]++;
    }

    std::cout << "\n   Cartes les plus sacrifiées:" << std::endl;
    int rank = 1;
    for (const auto& [nom, count] : compteur) {
        std::cout << "   " << rank << ". " << nom << " x" << count << std::endl;
        rank++;
        if (rank > 5) break;  // Top 5
    }
}

std::string Sacrifice::getIconeFaction(int faction) const {
    switch(faction) {
        case static_cast<int>(Faction::IMPERIAL): return "🛡️";
        case static_cast<int>(Faction::GUILD):    return "🏹";
        case static_cast<int>(Faction::NECROS):   return "💀";
        case static_cast<int>(Faction::WILD):     return "🐺";
        default:                                   return "⚪";
    }
}

std::string Sacrifice::getIconeType(int type) const {
    switch(type) {
        case static_cast<int>(TypeCarte::ACTION):   return "⚡";
        case static_cast<int>(TypeCarte::CHAMPION): return "👤";
        case static_cast<int>(TypeCarte::ITEM):     return "🔨";
        default:                                     return "❓";
    }
}

// ====== Informations ======

size_t Sacrifice::taille() const {
    return cartes_.size();
}

bool Sacrifice::estVide() const {
    return cartes_.empty();
}

const Carte* Sacrifice::getCarte(size_t index) const {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

// ====== Accès Direct ======

std::vector<Carte*>& Sacrifice::cartes() {
    return cartes_;
}

const std::vector<Carte*>& Sacrifice::cartes() const {
    return cartes_;
}

// ====== Opérateurs ======

Carte* Sacrifice::operator[](size_t index) {
    if (index >= cartes_.size()) {
        return nullptr;
    }
    return cartes_[index];
}

const Carte* Sacrifice::operator[](size_t index) const {
    return getCarte(index);
}