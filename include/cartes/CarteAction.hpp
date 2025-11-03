#ifndef CARTEACTION_HPP
#define CARTEACTION_HPP

#include "Carte.hpp"

class CarteAction : public Carte {
protected:
    // Effets principaux (quand la carte est jouée)
    int or_principal;
    int combat_principal;
    int soin_principal;
    int pioche_principal;
    
    // Effet allié (si une autre carte de même faction est jouée)
    int or_allie;
    int combat_allie;
    int soin_allie;
    int pioche_allie;
    
    // Effet de sacrifice (optionnel)
    int or_sacrifice;
    int combat_sacrifice;
    int soin_sacrifice;
    int pioche_sacrifice;
    bool a_effet_sacrifice;

public:
    CarteAction(int quantity, const std::string& nom, int cout, Faction faction);
    
    virtual ~CarteAction();
    
    // Setters pour les effets principaux
    void setEffetPrincipal(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Setters pour les effets alliés
    void setEffetAllie(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Setters pour les effets de sacrifice
    void setEffetSacrifice(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Override de Carte
    void jouer(Joueur* joueur) override;
    void afficher() const override;
    
    // Méthodes spécifiques aux actions
    void activerAllie(Joueur* joueur);
    void sacrifier(Joueur* joueur);
    
    // Getters
    bool aEffetAllie() const;
    bool aEffetSacrifice() const;
    int getOrPrincipal() const;
    int getCombatPrincipal() const;
    int getSoinPrincipal() const;
    int getPiochePrincipal() const;
    
    int getOrAllie() const;
    int getCombatAllie() const;
    int getSoinAllie() const;
    int getPiocheAllie() const;
    
    int getOrSacrifice() const;
    int getCombatSacrifice() const;
    int getSoinSacrifice() const;
    int getPiocheSacrifice() const;
};

#endif