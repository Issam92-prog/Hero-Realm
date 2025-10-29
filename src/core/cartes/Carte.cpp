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