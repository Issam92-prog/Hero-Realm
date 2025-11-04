#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "zone/Pioche.hpp"
#include "zone/MainJoueur.hpp"
#include "zone/ZoneDeJeu.hpp"
#include "zone/Defausse.hpp"
#include "zone/Sacrifice.hpp"
#include "enum/Faction.hpp"
#include "cartes/Carte.hpp"
#include "cartes/CarteChampion.hpp"


class Joueur {
public:
    using Id = std::uint32_t;

    // ====== Constructeur & Destructeur ======
    Joueur(Id id, const std::string& nom, int pv_initial = 50);
    ~Joueur();

    // ====== Identité ======
    Id id() const;
    const std::string& nom() const;

    // ====== Points de Vie ======
    int pv() const;
    void soigner(int valeur);
    void subirDegats(int valeur);
    bool estMort() const;

    // ====== Ressources (Or & Combat) ======
    int orTour() const;
    int combatTour() const;
    void ajouterOr(int n);
    void ajouterCombat(int n);
    void resetRessources();

    // ====== Cycle de Jeu ======
    void debutDeTour();
    void finDeTour();

    // ====== Pioche ======
    void piocher(int n = 1);
    void initialiserDeckDeBase(int nb_cartes_initiales = 5);

    // ====== Gestion des Champions ======
    void jouerChampion(CarteChampion* champion);
    void preparerChampions();
    void defausserChampionsMorts();
    bool aChampionsGarde() const;

    // ====== Gestion du Sacrifice ======
    void sacrifierCarte(Carte* carte);

    // ════════════════════════════════════════════════════════
    // ====== GESTION DES EFFETS ALLIÉS (NOUVEAU) ======
    // ════════════════════════════════════════════════════════

    /**
     * @brief Vérifie si le joueur a joué une carte de la faction donnée ce tour
     * @param faction La faction à vérifier
     * @return bool true si une carte de cette faction a été jouée
     */
    bool aJoueFaction(Faction faction) const;

    /**
     * @brief Enregistre qu'une carte d'une faction a été jouée
     * @param faction La faction jouée
     */
    void enregistrerFactionJouee(Faction faction);

    /**
     * @brief Réinitialise le suivi des factions jouées (début de tour)
     */
    void reinitialiserFactionsJouees();

     // ════════════════════════════════════════════════════════
    // COMPTAGE DES CHAMPIONS (pour effets conditionnels)
    // ════════════════════════════════════════════════════════
    
    int compterChampionsEnJeu() const;
    int compterChampionsVivants() const;
    int compterChampionsFaction(Faction faction) const;
    int compterChampionsGarde() const;

    // ====== Affichage ======
    void afficherZones() const;
    void afficherMain() const;
    void afficherChampions() const;
    void afficherStatistiques() const;

    // ====== Accesseurs des Zones ======
    Pioche& pioche();
    MainJoueur& main();
    ZoneDeJeu& zoneDeJeu();
    Defausse& defausse();
    Sacrifice& sacrifice();

    const Pioche& pioche() const;
    const MainJoueur& main() const;
    const ZoneDeJeu& zoneDeJeu() const;
    const Defausse& defausse() const;
    const Sacrifice& sacrifice() const;

    int compterCartesJoueesFaction(Faction faction) const;
    int compterChampionsEnJeuFaction(Faction faction) const;
    
    

private:
    // Identité
    Id id_;
    std::string nom_;

    // État
    int pv_;
    int or_tour_ = 0;
    int combat_tour_ = 0;

    // Zones
    Pioche pioche_;
    MainJoueur main_;
    ZoneDeJeu zone_de_jeu_;
    Defausse defausse_;
    Sacrifice sacrifice_;

    // ════════════════════════════════════════════════════════
    // Suivi des factions jouées ce tour (pour effets alliés)
    // ════════════════════════════════════════════════════════
    std::vector<Faction> factions_jouees_ce_tour_;


};

#endif // JOUEUR_HPP