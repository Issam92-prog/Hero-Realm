#include "cartes/Carte.hpp"
#include <iostream>

Carte::Carte(int quantity, const std::string& nom, int cout, Faction faction, TypeCarte type)
    : quantity(quantity), nom(nom), description(""), type(type), faction(faction), cout(cout) {
}

Carte::~Carte() {
}

int Carte::getQuantity() const {
    return quantity;
}

std::string Carte::getNom() const {
    return nom;
}

std::string Carte::getDescription() const {
    return description;
}

int Carte::getCout() const {
    return cout;
}

Faction Carte::getFaction() const {
    return faction;
}

TypeCarte Carte::getType() const {
    return type;
}

void Carte::setQuantity(int q) {
    quantity = q;
}

void Carte::setDescription(const std::string& desc) {
    description = desc;
}

std::string Carte::getFactionIcon() const {
    switch(faction) {
        case Faction::IMPERIAL: return "🛡️";
        case Faction::GUILD:    return "🏹";
        case Faction::NECROS:   return "💀";
        case Faction::WILD:     return "🐺";
        case Faction::NONE:     return "⚪";
        default:                return "❓";
    }
}

std::string Carte::getFactionNom() const {
    switch(faction) {
        case Faction::IMPERIAL: return "IMPERIAL";
        case Faction::GUILD:    return "GUILD";
        case Faction::NECROS:   return "NECROS";
        case Faction::WILD:     return "WILD";
        case Faction::NONE:     return "NONE";
        default:                return "INCONNU";
    }
}

void Carte::afficher() const {
    std::cout << "=== " << nom << " ===" << std::endl;
    std::cout << "Coût: " << cout << std::endl;
    std::cout << "Faction: ";
    
    switch(faction) {
        case IMPERIAL: std::cout << "Imperial"; break;
        case GUILD: std::cout << "Guild"; break;
        case NECROS: std::cout << "Necros"; break;
        case WILD: std::cout << "Wild"; break;
        case NONE: std::cout << "Aucune"; break;
    }
    
    std::cout << std::endl;
    std::cout << "Type: ";
    
    switch(type) {
        case ACTION: std::cout << "Action"; break;
        case CHAMPION: std::cout << "Champion"; break;
        case ITEM: std::cout << "Item"; break;
    }
    
    std::cout << std::endl;
    std::cout << "Description: " << description << std::endl;
}