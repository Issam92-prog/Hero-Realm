#pragma once
#include <memory>
#include <vector>

// Déclaration anticipée de Joueur (évite les inclusions circulaires)
class Joueur;

using namespace std;

class Plateau {
public:
    Plateau() = default;

    // Gestion des joueurs
    Joueur* ajouterJoueur(unique_ptr<Joueur> j);
    size_t nbJoueurs() const { return joueurs_.size(); }

    Joueur* joueurCourant();
    const Joueur* joueurCourant() const;

    Joueur* adversaire();
    const Joueur* adversaire() const;

    // Gestion du cycle de partie
    void demarrer();
    void finDeTour();
    void changerTour();

    bool estDemarree() const { return demarree_; }
    bool estTerminee() const { return terminee_; }

private:
    vector<unique_ptr<Joueur>> joueurs_;
    int  idx_      = 0;
    bool demarree_ = false;
    bool terminee_ = false;
};
