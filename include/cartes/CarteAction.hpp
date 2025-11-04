#ifndef CARTEACTION_HPP
#define CARTEACTION_HPP

#include "cartes/Carte.hpp"
#include <functional>

// Forward declarations
class Joueur;
class Game;

// Type pour les callbacks d'effets spéciaux
using EffetSpecialCallback = std::function<void(Joueur*, Game*)>;

class CarteAction : public Carte {
private:
    // Effets numériques principaux
    int or_principal;
    int combat_principal;
    int soin_principal;
    int pioche_principal;
    
    // Effets alliés
    int or_allie;
    int combat_allie;
    int soin_allie;
    int pioche_allie;
    
    // Effets sacrifice
    int or_sacrifice;
    int combat_sacrifice;
    int soin_sacrifice;
    int pioche_sacrifice;
    bool a_effet_sacrifice;
    
    // Effets spéciaux (lambdas)
    EffetSpecialCallback effet_special_principal_;
    EffetSpecialCallback effet_special_allie_;
    EffetSpecialCallback effet_special_sacrifice_;

public:
    // ════════════════════════════════════════════════════════
    // CONSTRUCTEUR & DESTRUCTEUR
    // ════════════════════════════════════════════════════════
    
    CarteAction(int quantity, const std::string& nom, int cout, Faction faction);
    virtual ~CarteAction();
    
    // ════════════════════════════════════════════════════════
    // SETTERS POUR EFFETS NUMÉRIQUES
    // ════════════════════════════════════════════════════════
    
    void setEffetPrincipal(int or_val, int combat_val, int soin_val, int pioche_val);
    void setEffetAllie(int or_val, int combat_val, int soin_val, int pioche_val);
    void setEffetSacrifice(int or_val, int combat_val, int soin_val, int pioche_val);
    
    // ════════════════════════════════════════════════════════
    // SETTERS POUR EFFETS SPÉCIAUX
    // ════════════════════════════════════════════════════════
    
    void setEffetSpecialPrincipal(EffetSpecialCallback effet);
    void setEffetSpecialAllie(EffetSpecialCallback effet);
    void setEffetSpecialSacrifice(EffetSpecialCallback effet);
    
    // ════════════════════════════════════════════════════════
    // GETTERS POUR EFFETS SPÉCIAUX (pour le clonage)
    // ════════════════════════════════════════════════════════
    
    EffetSpecialCallback getEffetSpecialPrincipal() const;
    EffetSpecialCallback getEffetSpecialAllie() const;
    EffetSpecialCallback getEffetSpecialSacrifice() const;
    
    // ════════════════════════════════════════════════════════
    // MÉTHODE PRINCIPALE
    // ════════════════════════════════════════════════════════
    
    void jouer(Joueur* joueur) override;
    void afficher() const override;
    
    /**
     * @brief Clone cette carte action avec tous ses effets (y compris les lambdas)
     * @return CarteAction* Une nouvelle instance identique
     */
    CarteAction* clone() const;
    
    // ════════════════════════════════════════════════════════
    // ACTIVATION DES EFFETS
    // ════════════════════════════════════════════════════════
    
    void activerAllie(Joueur* joueur);
    void sacrifier(Joueur* joueur);
    
    // ════════════════════════════════════════════════════════
    // GETTERS - VÉRIFICATIONS
    // ════════════════════════════════════════════════════════
    
    bool aEffetAllie() const;
    bool aEffetSacrifice() const;
    bool aEffetSpecialPrincipal() const;
    bool aEffetSpecialAllie() const;
    bool aEffetSpecialSacrifice() const;
    
    // ════════════════════════════════════════════════════════
    // GETTERS - VALEURS NUMÉRIQUES
    // ════════════════════════════════════════════════════════
    
    // Effets principaux
    int getOrPrincipal() const;
    int getCombatPrincipal() const;
    int getSoinPrincipal() const;
    int getPiochePrincipal() const;
    
    // Effets alliés
    int getOrAllie() const;
    int getCombatAllie() const;
    int getSoinAllie() const;
    int getPiocheAllie() const;
    
    // Effets sacrifice
    int getOrSacrifice() const;
    int getCombatSacrifice() const;
    int getSoinSacrifice() const;
    int getPiocheSacrifice() const;
};

#endif // CARTEACTION_HPP