#pragma once
#include <string>
#include <cstdint>
#include "zone/Pioche.hpp"
#include "zone/MainJoueur.hpp"
#include "zone/ZoneDeJeu.hpp"
#include "zone/Defausse.hpp"
#include "zone/Sacrifice.hpp"

class Carte;
class CarteChampion;

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

    // Pioche
    void piocher(int n = 1);
    void initialiserDeckDeBase();

    // Gestion des champions
    void jouerChampion(CarteChampion* champion);
    void preparerChampions();
    void defausserChampionsMorts();
    bool aChampionsGarde() const;

    // Gestion du sacrifice
    void sacrifierCarte(Carte* carte);

    // Affichage
    void afficherZones() const;
    void afficherMain() const;
    void afficherChampions() const;
    void afficherStatistiques() const;

    // Accesseurs des zones (non-const)
    Pioche& pioche();
    MainJoueur& main();
    ZoneDeJeu& zoneDeJeu();
    Defausse& defausse();
    Sacrifice& sacrifice();

    // Accesseurs des zones (const)
    const Pioche& pioche() const;
    const MainJoueur& main() const;
    const ZoneDeJeu& zoneDeJeu() const;
    const Defausse& defausse() const;
    const Sacrifice& sacrifice() const;

private:
    Id          id_;
    std::string nom_;
    int         pv_;

    int or_tour_{0};
    int combat_tour_{0};

    // ===== ZONES DU JOUEUR =====
    Pioche pioche_;           // Cartes à piocher
    MainJoueur main_;         // Cartes en main
    ZoneDeJeu zone_de_jeu_;   // Champions actifs
    Defausse defausse_;       // Cartes défaussées (remélangent)
    Sacrifice sacrifice_;     // Cartes sacrifiées (ne remélangent PAS)
};