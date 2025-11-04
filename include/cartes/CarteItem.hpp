#ifndef CARTEITEM_HPP
#define CARTEITEM_HPP

#include "Carte.hpp"

class CarteItem : public Carte {
protected:
    // Effets principaux (quand l'item est joué)
    int or_genere;
    int combat_genere;
    
    // Effets de sacrifice (seulement or et combat)
    int sacrifice_or;
    int sacrifice_combat;

public:
    CarteItem(int quantity, const std::string& nom, int cout, Faction faction, 
              int or_val = 0, int combat_val = 0);
    
    virtual ~CarteItem();
    
    // Setters pour les effets
    void setEffets(int or_val, int combat_val);
    void setEffetSacrifice(int or_val, int combat_val);
    
    // Override de Carte
    void jouer(Joueur* joueur) override;
    void afficher() const override;
    
    /**
     * @brief Clone cette carte item avec tous ses effets
     * @return CarteItem* Une nouvelle instance identique
     */
    CarteItem* clone() const;
    
    // Méthode de sacrifice
    void sacrifier(Joueur* joueur);
    
    // Getters
    int getOr() const;
    int getCombat() const;
    bool aEffetSacrifice() const;
    int getSacrificeOr() const;
    int getSacrificeCombat() const;
};

#endif