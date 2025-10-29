#pragma once
#include <string>
#include <cstdint>
#include <vector>

class Carte;

class Joueur {
public:
    using Id = std::uint32_t;

    // Ctor/Dtor
    Joueur(Id id, const std::string& nom, int pv_initial = 50);
    ~Joueur();

    // Identité
    Id id() const;
    const std::string& nom() const;

    // Points de vie
    int  pv() const;
    void soigner(int v);
    void subirDegats(int v);
    bool estMort() const;

    // Ressources du tour
    int  orTour() const;
    int  combatTour() const;
    void ajouterOr(int n);
    void ajouterCombat(int n);
    void resetRessources();

    // Cycle de tour
    void debutDeTour();
    void finDeTour();

    // Pioche / main / défausse
    void piocher(int n = 1);
    void initialiserDeckDeBase();

    // Accesseurs non-const (pour modifier)
    std::vector<Carte*>& main();
    std::vector<Carte*>& deck();
    std::vector<Carte*>& defausse();

    // Accesseurs const (pour lecture seule)
    const std::vector<Carte*>& main() const;
    const std::vector<Carte*>& deck() const;
    const std::vector<Carte*>& defausse() const;

private:
    Id          id_;
    std::string nom_;
    int         pv_;

    int or_tour_{0};
    int combat_tour_{0};

    std::vector<Carte*> main_;
    std::vector<Carte*> deck_;
    std::vector<Carte*> defausse_;
};
