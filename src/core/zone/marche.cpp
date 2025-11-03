#include "zone/Marche.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteItem.hpp"
#include "cartes/CarteAction.hpp"
#include "cartes/CarteChampion.hpp"
#include "cartes/CarteDB.hpp"
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// ====== Constructeur & Destructeur ======

Marche::Marche() : rng_(std::random_device{}()) {
}

Marche::~Marche() {
    nettoyer();
}

// ====== Initialisation ======

void Marche::initialiser() {
    std::cout << "🏪 Initialisation du marché..." << std::endl;

    // Nettoyer si déjà initialisé
    nettoyer();

    // Charger et décompresser les Gemmes de Feu depuis CarteDB
    auto gemmes_templates = CarteDB::getFireGems();
    decompresserCartes(gemmes_templates, gemmes_de_feu_);
    
    std::cout << "   🔥 " << gemmes_de_feu_.size() << " Gemmes de Feu chargées" << std::endl;

    // Charger toutes les cartes du marché depuis CarteDB (méthode unique)
    auto market_templates = CarteDB::getAllMarketCards();
    decompresserCartes(market_templates, deck_marche_);

    std::cout << "   📦 " << deck_marche_.size() << " cartes chargées" << std::endl;

    // Mélanger le deck
    melangerDeck();

    // Révéler les 5 premières cartes
    remplirMarche();

    std::cout << "✅ Marché initialisé !" << std::endl;
}

void Marche::decompresserCartes(std::vector<Carte*>& templates, std::vector<Carte*>& destination) {
    for (auto* template_carte : templates) {
        int quantite = template_carte->getQuantity();
        
        // Créer autant de copies que la quantité indique
        for (int i = 0; i < quantite; i++) {
            Carte* copie = clonerCarte(template_carte);
            if (copie) {
                destination.push_back(copie);
            }
        }
        
        // Libérer le template original
        delete template_carte;
    }
    templates.clear();
}

Carte* Marche::clonerCarte(const Carte* carte) {
    if (!carte) return nullptr;

    // Déterminer le type de carte et créer une copie
    if (const CarteItem* item = dynamic_cast<const CarteItem*>(carte)) {
        CarteItem* copie = new CarteItem(
            1,  // Quantité toujours 1 pour les instances individuelles
            item->getNom(),
            item->getCout(),
            item->getFaction(),
            item->getOr(),
            item->getCombat()
        );
        copie->setDescription(item->getDescription());
        
        // Copier les effets de sacrifice si présents
        if (item->getSacrificeOr() > 0 || item->getSacrificeCombat() > 0) {
            copie->setEffetSacrifice(
                item->getSacrificeOr(),
                item->getSacrificeCombat()
            );
        }
        
        return copie;
    }
    else if (const CarteAction* action = dynamic_cast<const CarteAction*>(carte)) {
        CarteAction* copie = new CarteAction(
            1,
            action->getNom(),
            action->getCout(),
            action->getFaction()
        );
        copie->setDescription(action->getDescription());
        
        // Copier l'effet principal
        copie->setEffetPrincipal(
            action->getOrPrincipal(),
            action->getCombatPrincipal(),
            action->getSoinPrincipal(),
            action->getPiochePrincipal()
        );
        
        // Copier l'effet allié si présent
        if (action->aEffetAllie()) {
            copie->setEffetAllie(
                action->getOrAllie(),
                action->getCombatAllie(),
                action->getSoinAllie(),
                action->getPiocheAllie()
            );
        }
        
        // Copier l'effet sacrifice si présent
        if (action->aEffetSacrifice()) {
            copie->setEffetSacrifice(
                action->getOrSacrifice(),
                action->getCombatSacrifice(),
                action->getSoinSacrifice(),
                action->getPiocheSacrifice()
            );
        }
        
        return copie;
    }
    else if (const CarteChampion* champion = dynamic_cast<const CarteChampion*>(carte)) {
        CarteChampion* copie = new CarteChampion(
            1,
            champion->getNom(),
            champion->getCout(),
            champion->getFaction(),
            champion->getDefense(),
            champion->estGarde()
        );
        copie->setDescription(champion->getDescription());
        
        // Copier l'effet principal si présent
        if (champion->aEffetPrincipal()) {
            copie->setEffetPrincipal(
                champion->getOrPrincipal(),
                champion->getCombatPrincipal(),
                champion->getSoinPrincipal(),
                champion->getPiochePrincipal()
            );
        }
        
        // Copier l'effet Expend si présent
        if (champion->aEffetExpend()) {
            copie->setEffetExpend(
                champion->getOrExpend(),
                champion->getCombatExpend(),
                champion->getSoinExpend(),
                champion->getPiocheExpend()
            );
        }
        
        // Copier l'effet allié si présent
        if (champion->aEffetAllie()) {
            copie->setEffetAllie(
                champion->getOrAllie(),
                champion->getCombatAllie(),
                champion->getSoinAllie(),
                champion->getPiocheAllie()
            );
        }
        
        return copie;
    }
    
    return nullptr;
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

// ====== Achat de Cartes ======

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

// ====== Gestion des Cartes ======

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

// ====== Affichage ======

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

// ====== Informations ======

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

// ====== Accès aux Cartes ======

const Carte* Marche::getCarteDisponible(size_t index) const {
    if (index >= cartes_dispo_.size()) {
        return nullptr;
    }
    return cartes_dispo_[index];
}

const std::vector<Carte*>& Marche::cartesDisponibles() const {
    return cartes_dispo_;
}

// ====== Opérateurs ======

const Carte* Marche::operator[](size_t index) const {
    return getCarteDisponible(index);
}