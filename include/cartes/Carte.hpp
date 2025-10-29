#ifndef CARTE_HPP
#define CARTE_HPP

#include <string>
#include "enum/Faction.hpp"
#include "enum/TypeCarte.hpp"

class Joueur;

class Carte {
protected:
    int quantity;
    std::string nom;
    std::string description;
    TypeCarte type;
    Faction faction;
    int cout;

public:
    Carte(int quantity, const std::string& nom, int cout, Faction faction, TypeCarte type);
    virtual ~Carte();
    
    // Getters
    int getQuantity() const;
    std::string getNom() const;
    std::string getDescription() const;
    int getCout() const;
    Faction getFaction() const;
    TypeCarte getType() const;

    // Setters
    void setQuantity(int q);
    void setDescription(const std::string& desc);

    // Méthode virtuelle pure pour jouer la carte
    virtual void jouer(Joueur* joueur) = 0;

    // Affichage
    virtual void afficher() const;
};

#endif
