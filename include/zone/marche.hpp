#ifndef MARCHE_HPP
#define MARCHE_HPP

#include <vector>
#include <random>

class Carte;
class CarteItem;

/**
 * @brief Représente le marché partagé dans Hero Realms
 * 
 * Le Marché gère :
 * - Le deck du marché (80 cartes de 4 factions)
 * - Les 5 cartes disponibles à l'achat
 * - Les Gemmes de Feu (pile infinie)
 * - La défausse du marché (cartes détruites)
 */
class Marche {
public:
    // Constructeur & Destructeur
    Marche();
    ~Marche();

    // Initialisation
    /**
     * @brief Initialise le marché avec toutes les cartes
     * Charge les cartes depuis CarteDB, mélange et révèle 5 cartes
     */
    void initialiser();

    /**
     * @brief Nettoie la mémoire du marché
     */
    void nettoyer();

    // Achat de cartes
    /**
     * @brief Achète une carte du marché par index
     * @param index Index de la carte (0-based)
     * @return Carte* La carte achetée (nullptr si index invalide)
     */
    Carte* acheterCarte(size_t index);

    /**
     * @brief Achète une Gemme de Feu (toujours disponible)
     * @return Carte* Une nouvelle Gemme de Feu
     */
    Carte* acheterGemmeDeFeu();

    // Gestion des cartes du marché
    /**
     * @brief Défausse une carte du marché (certains effets)
     * @param index Index de la carte à défausser
     * @return bool true si la carte a été défaussée
     */
    bool defausserCarte(size_t index);

    /**
     * @brief Révèle des cartes jusqu'à avoir 5 disponibles
     */
    void remplirMarche();

    /**
     * @brief Mélange le deck du marché
     */
    void melangerDeck();

    // Affichage
    /**
     * @brief Affiche le marché avec les cartes disponibles
     * @param afficher_details true pour afficher les détails des cartes
     */
    void afficher(bool afficher_details = false) const;

    /**
     * @brief Affiche une carte spécifique du marché
     * @param index Index de la carte
     */
    void afficherCarte(size_t index) const;

    /**
     * @brief Affiche les statistiques du marché
     */
    void afficherStatistiques() const;

    // Informations
    /**
     * @brief Nombre de cartes disponibles à l'achat
     * @return size_t Nombre de cartes (max 5)
     */
    size_t nbCartesDisponibles() const;

    /**
     * @brief Nombre de cartes restantes dans le deck
     * @return size_t Nombre de cartes
     */
    size_t nbCartesDeck() const;

    /**
     * @brief Nombre de cartes dans la défausse du marché
     * @return size_t Nombre de cartes
     */
    size_t nbCartesDefaussees() const;

    /**
     * @brief Vérifie si le deck du marché est vide
     * @return bool true si vide
     */
    bool deckVide() const;

    /**
     * @brief Vérifie si le marché est plein (5 cartes)
     * @return bool true si plein
     */
    bool estPlein() const;

    // Accès aux cartes
    /**
     * @brief Récupère une carte disponible par index (lecture seule)
     * @param index Index de la carte
     * @return const Carte* La carte (nullptr si invalide)
     */
    const Carte* getCarteDisponible(size_t index) const;

    /**
     * @brief Accès direct aux cartes disponibles
     * @return const std::vector<Carte*>& Vector des cartes
     */
    const std::vector<Carte*>& cartesDisponibles() const;

    // Opérateur [] pour accès direct
    const Carte* operator[](size_t index) const;

private:
    std::vector<Carte*> deck_marche_;       // Cartes non révélées
    std::vector<Carte*> cartes_dispo_;      // 5 cartes visibles
    std::vector<Carte*> defausse_marche_;   // Cartes détruites
    CarteItem* gemme_de_feu_template_;      // Template pour créer des gemmes
    std::mt19937 rng_;                      // Générateur aléatoire

    /**
     * @brief Crée le template de Gemme de Feu
     */
    void creerGemmeDeFeu();

    /**
     * @brief Retourne l'icône correspondant à la faction
     * @param faction La faction
     * @return std::string L'icône unicode
     */
    std::string getIconeFaction(int faction) const;

    /**
     * @brief Retourne l'icône correspondant au type de carte
     * @param type Le type de carte
     * @return std::string L'icône unicode
     */
    std::string getIconeType(int type) const;
};

#endif // MARCHE_HPP