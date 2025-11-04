#include "zone/marche.hpp"
#include "cartes/CarteDB.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteChampion.hpp"
#include "cartes/CarteAction.hpp"
#include "cartes/CarteItem.hpp"
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// ════════════════════════════════════════════════════════
// CONSTRUCTEUR & DESTRUCTEUR
// ════════════════════════════════════════════════════════

Marche::Marche() : rng_(std::random_device{}()) {
}

Marche::~Marche() {
    nettoyer();
}

void Marche::initialiser() {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  🏪 INITIALISATION DU MARCHÉ                           ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    // Nettoyer si déjà initialisé
    nettoyer();

    // Charger et décompresser les Gemmes de Feu depuis CarteDB
    auto gemmes_templates = CarteDB::getFireGems();
    
    for (auto* template_carte : gemmes_templates) {
        int quantite = template_carte->getQuantity();
        
        // Créer autant de copies que la quantité indique en utilisant clone()
        for (int i = 0; i < quantite; i++) {
            if (CarteItem* item = dynamic_cast<CarteItem*>(template_carte)) {
                gemmes_de_feu_.push_back(item->clone());
            }
        }
        
        // Libérer le template original
        delete template_carte;
    }
    
    std::cout << "   🔥 " << gemmes_de_feu_.size() << " Gemmes de Feu chargées" << std::endl;

    // Charger toutes les cartes du marché depuis CarteDB
    auto market_templates = CarteDB::getAllMarketCards();
    
    for (auto* template_carte : market_templates) {
        int quantite = template_carte->getQuantity();
        
        // Créer autant de copies que la quantité indique en utilisant clone()
        for (int i = 0; i < quantite; i++) {
            Carte* copie = nullptr;
            
            // Utiliser les méthodes clone() polymorphes
            if (CarteChampion* champion = dynamic_cast<CarteChampion*>(template_carte)) {
                copie = champion->clone();
            } else if (CarteAction* action = dynamic_cast<CarteAction*>(template_carte)) {
                copie = action->clone();
            } else if (CarteItem* item = dynamic_cast<CarteItem*>(template_carte)) {
                copie = item->clone();
            }
            
            if (copie) {
                deck_marche_.push_back(copie);
            }
        }
        
        // Libérer le template original
        delete template_carte;
    }

    std::cout << "   📦 " << deck_marche_.size() << " cartes chargées" << std::endl;

    // Mélanger le deck
    melangerDeck();

    // Révéler les 5 premières cartes
    remplirMarche();

    std::cout << "✅ Marché initialisé !" << std::endl;
}

void Marche::nettoyer() {
    // Supprimer toutes les cartes du deck
    for (auto* carte : deck_marche_) {
        delete carte;
    }
    deck_marche_.clear();

    // Supprimer les cartes disponibles
    for (auto* carte : cartes_dispo_) {
        delete carte;
    }
    cartes_dispo_.clear();

    // Supprimer les cartes défaussées
    for (auto* carte : defausse_marche_) {
        delete carte;
    }
    defausse_marche_.clear();

    // Supprimer les gemmes de feu
    for (auto* gemme : gemmes_de_feu_) {
        delete gemme;
    }
    gemmes_de_feu_.clear();
}

// ════════════════════════════════════════════════════════
// ACHAT DE CARTES
// ════════════════════════════════════════════════════════

Carte* Marche::acheterCarte(size_t index) {
    if (index >= cartes_dispo_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return nullptr;
    }

    // Récupérer la carte
    Carte* carte = cartes_dispo_[index];
    cartes_dispo_.erase(cartes_dispo_.begin() + index);

    std::cout << "🛒 Carte achetée : " << carte->getNom() << std::endl;

    // Remplir le marché
    remplirMarche();

    return carte;
}

Carte* Marche::acheterGemmeDeFeu() {
    if (gemmes_de_feu_.empty()) {
        std::cout << "⚠️  Plus de Gemmes de Feu disponibles !" << std::endl;
        return nullptr;
    }

    // Retirer une gemme de la pile
    Carte* gemme = gemmes_de_feu_.back();
    gemmes_de_feu_.pop_back();

    std::cout << "🛒 Gemme de Feu achetée (" << gemmes_de_feu_.size() << " restantes)" << std::endl;

    return gemme;
}

// ════════════════════════════════════════════════════════
// GESTION DES CARTES
// ════════════════════════════════════════════════════════

bool Marche::defausserCarte(size_t index) {
    if (index >= cartes_dispo_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return false;
    }

    // Défausser la carte (retirée du jeu)
    Carte* carte = cartes_dispo_[index];
    cartes_dispo_.erase(cartes_dispo_.begin() + index);
    defausse_marche_.push_back(carte);

    std::cout << "💀 " << carte->getNom() << " est défaussée du marché" << std::endl;

    // Remplir le marché
    remplirMarche();

    return true;
}

void Marche::remplirMarche() {
    while (!deck_marche_.empty() && cartes_dispo_.size() < 5) {
        cartes_dispo_.push_back(deck_marche_.back());
        deck_marche_.pop_back();
    }

    if (cartes_dispo_.size() < 5 && deck_marche_.empty()) {
        std::cout << "⚠️  Le deck du marché est vide ! (" << cartes_dispo_.size() << " cartes disponibles)" << std::endl;
    }
}

void Marche::melangerDeck() {
    std::shuffle(deck_marche_.begin(), deck_marche_.end(), rng_);
    std::cout << "🔀 Deck du marché mélangé" << std::endl;
}

// ════════════════════════════════════════════════════════
// AFFICHAGE
// ════════════════════════════════════════════════════════

void Marche::afficher(bool afficher_details) const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🏪 MARCHÉ - Hero Realms                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    // Afficher le nombre de Gemmes de Feu restantes
    std::cout << "\n[🔥] Gemme de Feu (Coût: 2 or) - 📦 " << gemmes_de_feu_.size() << " restantes" << std::endl;
    if (gemmes_de_feu_.empty()) {
        std::cout << "     ⚠️  ÉPUISÉES !" << std::endl;
    } else {
        std::cout << "     💰 Gain 2 or | 💀 Sacrifice: Gain 3 combat" << std::endl;
    }

    // Cartes disponibles
    std::cout << "\n--- Cartes Disponibles à l'Achat ---" << std::endl;

    if (cartes_dispo_.empty()) {
        std::cout << "   (aucune carte disponible)" << std::endl;
    } else {
        for (size_t i = 0; i < cartes_dispo_.size(); ++i) {
            const Carte* carte = cartes_dispo_[i];

            // Icônes
            std::string icone_faction = getIconeFaction(static_cast<int>(carte->getFaction()));
            std::string icone_type = getIconeType(static_cast<int>(carte->getType()));

            // Affichage compact
            std::cout << "[" << (i + 1) << "] " 
                      << icone_faction << " " 
                      << icone_type << " "
                      << carte->getNom() 
                      << " (Coût: " << carte->getCout() << " or)";

            std::cout << std::endl;

            // Détails si demandé
            if (afficher_details) {
                std::cout << "    " << carte->getDescription() << std::endl;
            }
        }
    }

    // Statistiques
    std::cout << "\n--- Statistiques ---" << std::endl;
    std::cout << "🔥 Gemmes de Feu: " << gemmes_de_feu_.size() << std::endl;
    std::cout << "📦 Cartes dans le deck: " << deck_marche_.size() << std::endl;
    std::cout << "🗑️  Cartes défaussées: " << defausse_marche_.size() << std::endl;
}

void Marche::afficherCarte(size_t index) const {
    if (index >= cartes_dispo_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return;
    }

    const Carte* carte = cartes_dispo_[index];
    std::cout << "\n";
    carte->afficher();
}

void Marche::afficherStatistiques() const {
    std::cout << "\n📊 Statistiques du Marché:" << std::endl;
    std::cout << "   Gemmes de Feu: " << gemmes_de_feu_.size() << std::endl;
    std::cout << "   Cartes disponibles: " << cartes_dispo_.size() << "/5" << std::endl;
    std::cout << "   Cartes dans le deck: " << deck_marche_.size() << std::endl;
    std::cout << "   Cartes défaussées: " << defausse_marche_.size() << std::endl;

    if (!cartes_dispo_.empty()) {
        // Compter par faction
        int imperial = 0, guild = 0, necros = 0, wild = 0, none = 0;
        for (const auto* carte : cartes_dispo_) {
            switch(carte->getFaction()) {
                case Faction::IMPERIAL: imperial++; break;
                case Faction::GUILD:    guild++; break;
                case Faction::NECROS:   necros++; break;
                case Faction::WILD:     wild++; break;
                default:                none++; break;
            }
        }

        std::cout << "\n   Factions disponibles:" << std::endl;
        if (imperial > 0) std::cout << "   - 👑 Imperial: " << imperial << std::endl;
        if (guild > 0)    std::cout << "   - 🏹 Guild: " << guild << std::endl;
        if (necros > 0)   std::cout << "   - 💀 Necros: " << necros << std::endl;
        if (wild > 0)     std::cout << "   - 🐺 Wild: " << wild << std::endl;
    }
}

std::string Marche::getIconeFaction(int faction) const {
    switch(faction) {
        case static_cast<int>(Faction::IMPERIAL): return "👑";
        case static_cast<int>(Faction::GUILD):    return "🏹";
        case static_cast<int>(Faction::NECROS):   return "💀";
        case static_cast<int>(Faction::WILD):     return "🐺";
        default:                                   return "⚪";
    }
}

std::string Marche::getIconeType(int type) const {
    switch(type) {
        case static_cast<int>(TypeCarte::ACTION):   return "⚡";
        case static_cast<int>(TypeCarte::CHAMPION): return "👤";
        case static_cast<int>(TypeCarte::ITEM):     return "🔨";
        default:                                     return "❓";
    }
}

// ════════════════════════════════════════════════════════
// INFORMATIONS
// ════════════════════════════════════════════════════════

size_t Marche::nbCartesDisponibles() const {
    return cartes_dispo_.size();
}

size_t Marche::nbCartesDeck() const {
    return deck_marche_.size();
}

size_t Marche::nbCartesDefaussees() const {
    return defausse_marche_.size();
}

size_t Marche::nbGemmesDeFeu() const {
    return gemmes_de_feu_.size();
}

bool Marche::deckVide() const {
    return deck_marche_.empty();
}

bool Marche::estPlein() const {
    return cartes_dispo_.size() >= 5;
}

// ════════════════════════════════════════════════════════
// ACCÈS AUX CARTES
// ════════════════════════════════════════════════════════

const Carte* Marche::getCarteDisponible(size_t index) const {
    if (index >= cartes_dispo_.size()) {
        return nullptr;
    }
    return cartes_dispo_[index];
}

const std::vector<Carte*>& Marche::cartesDisponibles() const {
    return cartes_dispo_;
}

// ════════════════════════════════════════════════════════
// OPÉRATEURS
// ════════════════════════════════════════════════════════

const Carte* Marche::operator[](size_t index) const {
    return getCarteDisponible(index);
}

// ════════════════════════════════════════════════════════
// MÉTHODES GOD MODE
// ════════════════════════════════════════════════════════

const std::vector<Carte*>& Marche::getDeckCartes() const {
    return deck_marche_;
}

Carte* Marche::acheterCarteDuDeck(size_t index) {
    if (index >= deck_marche_.size()) {
        std::cout << "⚠️  Index invalide : " << index << std::endl;
        return nullptr;
    }

    // Retirer la carte du deck
    Carte* carte = deck_marche_[index];
    deck_marche_.erase(deck_marche_.begin() + index);

    std::cout << "⚡ GOD MODE : " << carte->getNom() << " retirée du deck !" << std::endl;

    return carte;
}
