#ifndef CARTEITEM_HPP
#define CARTEITEM_HPP

#include "Carte.hpp"

class CarteItem : public Carte {
protected:
    // Effets principaux (quand l'item est joué)
    int or_genere;
    int combat_genere;
    // Effets de sacrifice
    int sacrifice_or;
    int sacrifice_combat;
    int sacrifice_sante;
    int sacrifice_pioche;

public:
    CarteItem(int quantity, const std::string& nom, int cout, Faction faction, 
              int or_val = 0, int combat_val = 0);
    
    virtual ~CarteItem();
    
    // Setters pour les effets
    void setEffets(int or_val, int combat_val);
    void setEffetSacrifice(int or_val, int combat_val, int sante_val = 0, int pioche_val = 0);
    
    // Override de Carte
    void jouer(Joueur* joueur) override;
    void afficher() const override;
    
    // Méthode de sacrifice
    void sacrifier(Joueur* joueur);
    
    // Getters
    int getOr() const;
    int getCombat() const;
    bool aEffetSacrifice() const;
    int getSacrificeOr() const;
    int getSacrificeCombat() const;
    int getSacrificeSante() const;
    int getSacrificePioche() const;
};

#endif
