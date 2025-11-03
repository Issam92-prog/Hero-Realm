#ifndef GODMODE_HPP
#define GODMODE_HPP

#include <string>
#include <vector>

class Plateau;
class Joueur;
class Carte;

/**
 * @brief Classe gérant le mode God (triche) pour Hero Realms
 * 
 * Le God Mode permet de :
 * - Activer/désactiver le mode pendant une partie
 * - Mettre les joueurs à 1 PV
 * - Acheter n'importe quelle carte du deck du marché (pas seulement les 5 visibles)
 * - Recevoir les cartes achetées directement dans la main (au lieu de la défausse)
 * 
 * Ce mode est utile pour :
 * - Tester des stratégies
 * - Débugger le jeu
 * - S'amuser avec des combinaisons impossibles
 */
class GodMode {
public:
    // ════════════════════════════════════════════════════════
    // CONSTRUCTEUR & DESTRUCTEUR
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Constructeur du God Mode
     * @param plateau Référence vers le plateau de jeu
     */
    explicit GodMode(Plateau& plateau);
    
    ~GodMode();

    // ════════════════════════════════════════════════════════
    // ACTIVATION / DÉSACTIVATION
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Active le God Mode
     */
    void activer();
    
    /**
     * @brief Désactive le God Mode
     */
    void desactiver();
    
    /**
     * @brief Bascule l'état du God Mode (toggle)
     */
    void basculer();
    
    /**
     * @brief Vérifie si le God Mode est actif
     * @return bool true si activé
     */
    bool estActif() const;

    // ════════════════════════════════════════════════════════
    // MENU INTERACTIF
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Affiche le menu du God Mode et gère les interactions
     * 
     * Menu proposant :
     * - Activer/Désactiver le mode
     * - Modifier les PV des joueurs
     * - Acheter depuis tout le deck du marché
     * - Afficher l'état du God Mode
     */
    void afficherMenu();

    // ════════════════════════════════════════════════════════
    // FONCTIONNALITÉS GOD MODE
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Met tous les joueurs à 1 PV
     * 
     * Utile pour tester les fins de partie ou les combos mortelles.
     */
    void mettreJoueursA1PV();
    
    /**
     * @brief Met un joueur spécifique à 1 PV
     * @param joueur Pointeur vers le joueur
     */
    void mettreJoueurA1PV(Joueur* joueur);
    
    /**
     * @brief Définit les PV d'un joueur
     * @param joueur Pointeur vers le joueur
     * @param pv Nouveaux points de vie
     */
    void definirPVJoueur(Joueur* joueur, int pv);
    
    /**
     * @brief Achète une carte depuis tout le deck du marché (pas seulement les 5 visibles)
     * 
     * Affiche toutes les cartes du deck, permet de choisir,
     * et place la carte directement dans la main du joueur actif.
     * 
     * @return bool true si une carte a été achetée
     */
    bool acheterDepuisDeckComplet();
    
    /**
     * @brief Achète une carte spécifique du deck et la place dans la main
     * @param index_deck Index de la carte dans le deck du marché
     * @param joueur Joueur qui reçoit la carte
     * @return bool true si l'achat a réussi
     */
    bool acheterCarteDeck(size_t index_deck, Joueur* joueur);

    // ════════════════════════════════════════════════════════
    // AFFICHAGE
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Affiche l'état actuel du God Mode
     */
    void afficherEtat() const;
    
    /**
     * @brief Affiche toutes les cartes du deck du marché
     * @param afficher_details true pour afficher les descriptions
     */
    void afficherDeckComplet(bool afficher_details = false) const;

private:
    // ════════════════════════════════════════════════════════
    // ATTRIBUTS
    // ════════════════════════════════════════════════════════
    
    Plateau& plateau_;        ///< Référence vers le plateau de jeu
    bool actif_;              ///< État du God Mode (activé/désactivé)
    
    // ════════════════════════════════════════════════════════
    // MÉTHODES PRIVÉES UTILITAIRES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Affiche un menu de sélection de joueur
     * @return Joueur* Pointeur vers le joueur sélectionné (nullptr si annulé)
     */
    Joueur* selectionnerJoueur();
    
    /**
     * @brief Lit un entier depuis l'entrée utilisateur
     * @param min Valeur minimum
     * @param max Valeur maximum
     * @return int La valeur lue
     */
    int lireEntier(int min, int max) const;
    
    /**
     * @brief Pause et attend une entrée utilisateur
     */
    void pause(const std::string& message = "Appuyez sur Entrée pour continuer...") const;
};

#endif // GODMODE_HPP