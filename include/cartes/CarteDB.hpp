#ifndef CARTEDB_HPP
#define CARTEDB_HPP

#include "Carte.hpp"
#include "CarteAction.hpp"
#include "CarteChampion.hpp"
#include "CarteItem.hpp"
#include <vector>

class CarteDB {
public:
    // Retourne des pointeurs vers les cartes
    static std::vector<Carte*> getStartingCards();
    static std::vector<Carte*> getFireGems();
    static std::vector<Carte*> getImperialCards();
    static std::vector<Carte*> getGuildCards();
    static std::vector<Carte*> getNecrosCards();
    static std::vector<Carte*> getWildCards();
    static std::vector<Carte*> getAllMarketCards();
    
    static int getTotalCardCount();
    
    // Méthode pour libérer la mémoire
    static void deleteCards(std::vector<Carte*>& cards);
};

#endif