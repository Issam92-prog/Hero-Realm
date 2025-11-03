#ifndef MARCHE_HPP
#define MARCHE_HPP

#include <vector>
#include <random>
#include <string>  // ← AJOUT pour std::string

class Carte;
class CarteItem;
class CarteAction;
class CarteChampion;

/**
 * @brief Représente le marché partagé dans Hero Realms
 * 
 * Le Marché gère :
 * - Le deck du marché (~80 cartes de 4 factions)
 * - Les 5 cartes disponibles à l'achat
 * - Les Gemmes de Feu (pile limitée de 16)
 * - La défausse du marché (cartes détruites)
 * 
 * Le marché utilise un système de "templates" depuis CarteDB :
 * - Les cartes avec quantité > 1 sont décompressées en instances individuelles
 * - Chaque carte achetée est une instance unique
 */
class Marche {
public:
    // ════════════════════════════════════════════════════════
    // CONSTRUCTEUR & DESTRUCTEUR
    // ════════════════════════════════════════════════════════
    
    Marche();
    ~Marche();

    // ════════════════════════════════════════════════════════
    // INITIALISATION
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Initialise le marché avec toutes les cartes
     * 
     * Charge les cartes depuis CarteDB, les décompresse,
     * mélange le deck et révèle les 5 premières cartes.
     * Les Gemmes de Feu sont chargées séparément (16 exemplaires).
     */
    void initialiser();

    /**
     * @brief Nettoie la mémoire du marché
     * 
     * Libère toutes les cartes allouées dynamiquement :
     * - Deck du marché
     * - Cartes disponibles
     * - Cartes défaussées
     * - Gemmes de Feu
     */
    void nettoyer();

    // ════════════════════════════════════════════════════════
    // ACHAT DE CARTES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Achète une carte du marché par index
     * @param index Index de la carte (0-4 pour les 5 cartes disponibles)
     * @return Carte* La carte achetée (nullptr si index invalide)
     * 
     * Note: Le marché est automatiquement rempli après l'achat
     */
    Carte* acheterCarte(size_t index);

    /**
     * @brief Achète une Gemme de Feu de la pile
     * @return Carte* Une Gemme de Feu (nullptr si pile vide)
     * 
     * Coût: 2 or
     * Effet: +2 or, Sacrifice: +3 combat
     * Pile limitée: 16 gemmes maximum
     */
    Carte* acheterGemmeDeFeu();

    // ════════════════════════════════════════════════════════
    // GESTION DES CARTES DU MARCHÉ
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Défausse une carte du marché (effet de certaines cartes)
     * @param index Index de la carte à défausser (0-4)
     * @return bool true si la carte a été défaussée avec succès
     * 
     * La carte défaussée est retirée définitivement du jeu.
     * Le marché est automatiquement rempli après.
     */
    bool defausserCarte(size_t index);

    /**
     * @brief Révèle des cartes jusqu'à avoir 5 disponibles
     * 
     * Pioche du dessus du deck jusqu'à avoir 5 cartes visibles.
     * Si le deck est vide, affiche un avertissement.
     */
    void remplirMarche();

    /**
     * @brief Mélange le deck du marché
     * 
     * Utilise std::shuffle avec un générateur aléatoire Mersenne Twister.
     */
    void melangerDeck();

    // ════════════════════════════════════════════════════════
    // AFFICHAGE
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Affiche le marché avec les cartes disponibles
     * @param afficher_details true pour afficher les descriptions complètes
     * 
     * Affiche :
     * - Le nombre de Gemmes de Feu restantes
     * - Les 5 cartes disponibles avec icônes de faction et type
     * - Les statistiques du marché (deck, défausse)
     */
    void afficher(bool afficher_details = false) const;

    /**
     * @brief Affiche une carte spécifique du marché en détail
     * @param index Index de la carte (0-4)
     */
    void afficherCarte(size_t index) const;

    /**
     * @brief Affiche les statistiques détaillées du marché
     * 
     * Affiche :
     * - Nombre de Gemmes de Feu
     * - Nombre de cartes disponibles / dans le deck / défaussées
     * - Répartition des factions disponibles
     */
    void afficherStatistiques() const;

    // ════════════════════════════════════════════════════════
    // INFORMATIONS
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Nombre de cartes disponibles à l'achat
     * @return size_t Nombre de cartes (0-5)
     */
    size_t nbCartesDisponibles() const;

    /**
     * @brief Nombre de cartes restantes dans le deck
     * @return size_t Nombre de cartes non révélées
     */
    size_t nbCartesDeck() const;

    /**
     * @brief Nombre de cartes dans la défausse du marché
     * @return size_t Nombre de cartes définitivement retirées
     */
    size_t nbCartesDefaussees() const;

    /**
     * @brief Nombre de Gemmes de Feu restantes
     * @return size_t Nombre de gemmes (0-16)
     */
    size_t nbGemmesDeFeu() const;

    /**
     * @brief Vérifie si le deck du marché est vide
     * @return bool true si aucune carte non révélée ne reste
     */
    bool deckVide() const;

    /**
     * @brief Vérifie si le marché est plein (5 cartes)
     * @return bool true si 5 cartes sont disponibles
     */
    bool estPlein() const;

    // ════════════════════════════════════════════════════════
    // ACCÈS AUX CARTES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Récupère une carte disponible par index (lecture seule)
     * @param index Index de la carte (0-4)
     * @return const Carte* La carte (nullptr si index invalide)
     */
    const Carte* getCarteDisponible(size_t index) const;

    /**
     * @brief Accès direct aux cartes disponibles (lecture seule)
     * @return const std::vector<Carte*>& Référence au vector des cartes
     */
    const std::vector<Carte*>& cartesDisponibles() const;

    /**
     * @brief Opérateur [] pour accès direct à une carte
     * @param index Index de la carte (0-4)
     * @return const Carte* La carte (nullptr si index invalide)
     */
    const Carte* operator[](size_t index) const;

private:
    // ════════════════════════════════════════════════════════
    // ATTRIBUTS
    // ════════════════════════════════════════════════════════
    
    std::vector<Carte*> deck_marche_;       ///< Cartes non révélées (~75 cartes)
    std::vector<Carte*> cartes_dispo_;      ///< 5 cartes visibles à l'achat
    std::vector<Carte*> defausse_marche_;   ///< Cartes détruites/défaussées
    std::vector<Carte*> gemmes_de_feu_;     ///< Pile de Gemmes de Feu (max 16)
    std::mt19937 rng_;                      ///< Générateur aléatoire Mersenne Twister

    // ════════════════════════════════════════════════════════
    // MÉTHODES PRIVÉES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Décompresse les cartes avec quantité > 1 en instances individuelles
     * @param templates Vecteur de templates depuis CarteDB (avec quantity > 1)
     * @param destination Vecteur de destination pour les instances uniques
     * 
     * Exemple : Une carte avec quantity=3 devient 3 cartes indépendantes.
     * Les templates sont supprimés après décompression.
     */
    void decompresserCartes(std::vector<Carte*>& templates, std::vector<Carte*>& destination);

    /**
     * @brief Clone une carte (crée une copie indépendante)
     * @param carte La carte template à cloner
     * @return Carte* Une nouvelle instance avec quantity=1
     * 
     * Gère les 3 types de cartes : Item, Action, Champion.
     * Copie tous les effets (principal, allié, sacrifice, expend).
     */
    Carte* clonerCarte(const Carte* carte);

    /**
     * @brief Retourne l'icône Unicode correspondant à la faction
     * @param faction La faction (enum casté en int)
     * @return std::string L'icône (👑 Imperial, 🏹 Guild, 💀 Necros, 🐺 Wild, ⚪ None)
     */
    std::string getIconeFaction(int faction) const;

    /**
     * @brief Retourne l'icône Unicode correspondant au type de carte
     * @param type Le type de carte (enum casté en int)
     * @return std::string L'icône (⚡ Action, 👤 Champion, 🔨 Item, ❓ Unknown)
     */
    std::string getIconeType(int type) const;
};

#endif // MARCHE_HPP