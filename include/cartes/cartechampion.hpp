#ifndef CARTECHAMPION_HPP
#define CARTECHAMPION_HPP

#include "Carte.hpp"

class CarteChampion : public Carte {
protected:
    int defense;
    int defense_actuelle;
    bool est_garde;
    bool est_expended; // Si le champion a déjà été utilisé ce tour
    
    // Effets principaux (quand le champion est posé)
    int or_principal;
    int combat_principal;
    int soin_principal;
    int pioche_principal;
    
    // Effets d'activation (Expend)
    int or_expend;
    int combat_expend;
    int soin_expend;
    int pioche_expend;
    
    // Effet allié (si une autre carte de même faction est jouée)
    int or_allie;
    int combat_allie;
    int soin_allie;
    int pioche_allie;

public:
    CarteChampion(int quantity, const std::string& nom, int cout, 
                  Faction faction, int defense, bool garde = false);
    
    virtual ~CarteChampion();
    
    // Setters pour les effets principaux
    void setEffetPrincipal(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Setters pour les effets d'activation (Expend)
    void setEffetExpend(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Setters pour les effets alliés
    void setEffetAllie(int or_val, int combat_val, int soin_val = 0, int pioche_val = 0);
    
    // Override de Carte
    void jouer(Joueur* joueur) override;
    void afficher() const override;
    
    // Méthodes spécifiques aux champions
    void utiliserExpend(Joueur* joueur);
    void activerAllie(Joueur* joueur);
    
    /**
     * @brief Vérifie et active les effets alliés si conditions remplies
     * À appeler chaque fois qu'une nouvelle carte est jouée pendant le tour
     * @param joueur Le joueur qui possède ce champion
     */
    void verifierEtActiverAllie(Joueur* joueur);
    
    void subirDegats(int degats);
    void preparerPourNouveauTour(); // Reset expended
    void reparer(); // Restaure la défense au maximum
    
    // Getters
    int getDefense() const;
    int getDefenseActuelle() const;
    bool estGarde() const;
    bool estExpended() const;
    bool estVivant() const;
    bool aEffetExpend() const;
    bool aEffetAllie() const;
    bool aEffetPrincipal() const;
    
    int getOrPrincipal() const;
    int getCombatPrincipal() const;
    int getSoinPrincipal() const;
    int getPiochePrincipal() const;
    
    int getOrExpend() const;
    int getCombatExpend() const;
    int getSoinExpend() const;
    int getPiocheExpend() const;
    
    int getOrAllie() const;
    int getCombatAllie() const;
    int getSoinAllie() const;
    int getPiocheAllie() const;
};

#endif