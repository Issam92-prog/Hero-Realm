#ifndef PIOCHE_HPP
#define PIOCHE_HPP

#include <vector>
#include <random>

class Carte;

/**
 * @brief Représente la pioche d'un joueur dans Hero Realms
 * 
 * La Pioche gère :
 * - La pioche de cartes
 * - Le mélange automatique quand la pioche est vide
 * - L'interaction avec la défausse
 */
class Pioche {
public:
    // Constructeur & Destructeur
    Pioche();
    ~Pioche();

    // Pioche de cartes
    /**
     * @brief Pioche n cartes de la pioche
     * @param n Nombre de cartes à piocher
     * @param defausse Référence vers la défausse (pour remélanger si besoin)
     * @return std::vector<Carte*> Les cartes piochées
     */
    std::vector<Carte*> piocher(int n, std::vector<Carte*>& defausse);

    /**
     * @brief Pioche une seule carte
     * @param defausse Référence vers la défausse
     * @return Carte* La carte piochée (nullptr si impossible)
     */
    Carte* piocherUne(std::vector<Carte*>& defausse);

    // Gestion de la pioche
    /**
     * @brief Ajoute une carte au dessus de la pioche
     * @param carte La carte à ajouter
     */
    void ajouterDessus(Carte* carte);

    /**
     * @brief Ajoute une carte en dessous de la pioche
     * @param carte La carte à ajouter
     */
    void ajouterDessous(Carte* carte);

    /**
     * @brief Mélange la pioche
     */
    void melanger();

    /**
     * @brief Remélange la défausse dans la pioche
     * @param defausse Référence vers la défausse à remélanger
     */
    void remelanger(std::vector<Carte*>& defausse);

    // Informations
    /**
     * @brief Nombre de cartes dans la pioche
     * @return size_t Nombre de cartes
     */
    size_t taille() const;

    /**
     * @brief Vérifie si la pioche est vide
     * @return true si vide, false sinon
     */
    bool estVide() const;

    /**
     * @brief Affiche le contenu de la pioche (debug)
     */
    void afficher() const;

    // Accès direct (pour initialisation, etc.)
    std::vector<Carte*>& cartes();
    const std::vector<Carte*>& cartes() const;

private:
    std::vector<Carte*> cartes_;
    std::mt19937 rng_;  // Générateur aléatoire pour le mélange

    /**
     * @brief Vérifie si on peut piocher, remélange si besoin
     * @param defausse Référence vers la défausse
     * @return true si on peut piocher, false sinon
     */
    bool verifierEtRemelanger(std::vector<Carte*>& defausse);
};

#endif // PIOCHE_HPP