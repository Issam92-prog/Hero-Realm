#include "zone/ZoneDeJeu.hpp"
#include "cartes/cartechampion.hpp"
#include "cartes/Carte.hpp"
#include "enum/Faction.hpp"
#include <iostream>
#include <algorithm>

// ====== Constructeur & Destructeur ======

ZoneDeJeu::ZoneDeJeu() {
}

ZoneDeJeu::~ZoneDeJeu() {
    // Note: Les cartes ne sont pas supprimées ici
    // C'est le Joueur qui gère la mémoire de toutes ses cartes
}

// ====== Gestion des Champions ======

void ZoneDeJeu::ajouterChampion(CarteChampion* champion) {
    if (champion) {
        champions_.push_back(champion);
    }
}

bool ZoneDeJeu::retirerChampion(CarteChampion* champion) {
    auto it = std::find(champions_.begin(), champions_.end(), champion);
    if (it != champions_.end()) {
        champions_.erase(it);
        return true;
    }
    return false;
}

CarteChampion* ZoneDeJeu::retirerChampion(size_t index) {
    if (index >= champions_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return nullptr;
    }

    CarteChampion* champion = champions_[index];
    champions_.erase(champions_.begin() + index);
    return champion;
}

void ZoneDeJeu::preparerTous() {
    for (auto* champion : champions_) {
        champion->preparerPourNouveauTour();
    }
}

int ZoneDeJeu::retirerMorts(std::vector<Carte*>& defausse) {
    int count = 0;
    auto it = champions_.begin();
    
    while (it != champions_.end()) {
        if (!(*it)->estVivant()) {
            std::cout << "💀 " << (*it)->getNom() << " est vaincu et va à la défausse." << std::endl;
            defausse.push_back(*it);
            it = champions_.erase(it);
            count++;
        } else {
            ++it;
        }
    }
    
    return count;
}

std::vector<CarteChampion*> ZoneDeJeu::vider() {
    std::vector<CarteChampion*> champions_retires = champions_;
    champions_.clear();
    return champions_retires;
}

// ====== Recherche de Champions ======

int ZoneDeJeu::trouverChampion(CarteChampion* champion) const {
    auto it = std::find(champions_.begin(), champions_.end(), champion);
    if (it != champions_.end()) {
        return std::distance(champions_.begin(), it);
    }
    return -1;
}

bool ZoneDeJeu::contient(CarteChampion* champion) const {
    return std::find(champions_.begin(), champions_.end(), champion) != champions_.end();
}

const CarteChampion* ZoneDeJeu::getChampion(size_t index) const {
    if (index >= champions_.size()) {
        return nullptr;
    }
    return champions_[index];
}

CarteChampion* ZoneDeJeu::getChampion(size_t index) {
    if (index >= champions_.size()) {
        return nullptr;
    }
    return champions_[index];
}

// ====== Gestion des Gardes ======

bool ZoneDeJeu::aChampionsGarde() const {
    for (const auto* champion : champions_) {
        if (champion->estGarde() && champion->estVivant()) {
            return true;
        }
    }
    return false;
}

int ZoneDeJeu::compterGardes() const {
    int count = 0;
    for (const auto* champion : champions_) {
        if (champion->estGarde() && champion->estVivant()) {
            count++;
        }
    }
    return count;
}

std::vector<CarteChampion*> ZoneDeJeu::getChampionsGarde() {
    std::vector<CarteChampion*> gardes;
    for (auto* champion : champions_) {
        if (champion->estGarde() && champion->estVivant()) {
            gardes.push_back(champion);
        }
    }
    return gardes;
}

// ====== Statistiques ======

int ZoneDeJeu::compterFaction(int faction) const {
    int count = 0;
    for (const auto* champion : champions_) {
        if (static_cast<int>(champion->getFaction()) == faction) {
            count++;
        }
    }
    return count;
}

int ZoneDeJeu::compterVivants() const {
    int count = 0;
    for (const auto* champion : champions_) {
        if (champion->estVivant()) {
            count++;
        }
    }
    return count;
}

int ZoneDeJeu::compterExpended() const {
    int count = 0;
    for (const auto* champion : champions_) {
        if (champion->estExpended()) {
            count++;
        }
    }
    return count;
}

int ZoneDeJeu::defenseTotal() const {
    int total = 0;
    for (const auto* champion : champions_) {
        total += champion->getDefenseActuelle();
    }
    return total;
}

// ====== Affichage ======

void ZoneDeJeu::afficher(bool afficher_details) const {
    std::cout << "\n⚔️  Zone de Jeu (" << champions_.size() << " champions):" << std::endl;
    
    if (champions_.empty()) {
        std::cout << "   (aucun champion)" << std::endl;
        return;
    }

    for (size_t i = 0; i < champions_.size(); ++i) {
        const CarteChampion* champion = champions_[i];
        
        // Icône de faction
        std::string icone_faction = getIconeFaction(static_cast<int>(champion->getFaction()));
        
        // Affichage de base
        std::cout << "   [" << (i + 1) << "] " 
                  << icone_faction << " "
                  << champion->getNom() 
                  << " [" << champion->getDefenseActuelle() 
                  << "/" << champion->getDefense() << " DEF]";
        
        // Badges
        if (champion->estGarde()) {
            std::cout << " 🛡️ GARDE";
        }
        if (champion->estExpended()) {
            std::cout << " 💤";
        }
        if (!champion->estVivant()) {
            std::cout << " 💀 VAINCU";
        }
        
        std::cout << std::endl;
        
        // Détails si demandé
        if (afficher_details) {
            std::cout << "       " << champion->getDescription() << std::endl;
        }
    }
    
    // Résumé
    std::cout << "\n   Statistiques:" << std::endl;
    std::cout << "   - Champions vivants: " << compterVivants() << "/" << champions_.size() << std::endl;
    
    int nb_gardes = compterGardes();
    if (nb_gardes > 0) {
        std::cout << "   - Champions Garde: " << nb_gardes << " 🛡️" << std::endl;
    }
    
    int nb_expended = compterExpended();
    if (nb_expended > 0) {
        std::cout << "   - Champions utilisés: " << nb_expended << " 💤" << std::endl;
    }
    
    std::cout << "   - Défense totale: " << defenseTotal() << std::endl;
}

void ZoneDeJeu::afficherChampion(size_t index) const {
    if (index >= champions_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return;
    }

    const CarteChampion* champion = champions_[index];
    std::cout << "\n";
    champion->afficher();
}

std::string ZoneDeJeu::getIconeFaction(int faction) const {
    switch(faction) {
        case static_cast<int>(Faction::IMPERIAL): return "👑";
        case static_cast<int>(Faction::GUILD):    return "🏹";
        case static_cast<int>(Faction::NECROS):   return "💀";
        case static_cast<int>(Faction::WILD):     return "🐺";
        default:                                   return "⚪";
    }
}

// ====== Informations ======

size_t ZoneDeJeu::taille() const {
    return champions_.size();
}

bool ZoneDeJeu::estVide() const {
    return champions_.empty();
}

// ====== Accès Direct ======

std::vector<CarteChampion*>& ZoneDeJeu::champions() {
    return champions_;
}

const std::vector<CarteChampion*>& ZoneDeJeu::champions() const {
    return champions_;
}

// ====== Opérateurs ======

CarteChampion* ZoneDeJeu::operator[](size_t index) {
    return getChampion(index);
}

const CarteChampion* ZoneDeJeu::operator[](size_t index) const {
    return getChampion(index);
}