// Effets spéciaux d'allié (lambdas)
EffetSpecialChampionCallback effet_special_allie_;
    
// Effets spéciaux d'expend (lambdas)
EffetSpecialChampionCallback effet_special_expend_;

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
    
    // Setter pour effet spécial d'allié
    void setEffetSpecialAllie(EffetSpecialChampionCallback effet);
    
    // Setter pour effet spécial d'expend
    void setEffetSpecialExpend(EffetSpecialChampionCallback effet);