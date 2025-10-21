#pragma once
#include <vector>
#include <memory>
#include "cartes/cartes.hpp"

class Marche {
public:
    // Initialise le deck du marché avec les cartes de base
    void initialiser();
    
    // Affiche les cartes disponibles à l'achat
    void afficher() const;
    
    // Achète une carte à l'index donné (0-based)
    Carte* acheterCarte(size_t index);
    
    // Nombre de cartes disponibles
    size_t nbCartes() const { return cartes_dispo_.size(); }
    
    // Accès aux cartes
    const std::vector<Carte*>& cartesDisponibles() const { return cartes_dispo_; }

private:
    std::vector<Carte*> deck_marche_;    // Cartes pas encore révélées
    std::vector<Carte*> cartes_dispo_;   // Cartes disponibles à l'achat
    
    // Révèle des cartes jusqu'à avoir 5 cartes disponibles
    void remplirMarche();
};
