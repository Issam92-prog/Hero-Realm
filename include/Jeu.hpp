#ifndef JEU_HPP
#define JEU_HPP

#include <string>
#include <vector>
#include "Plateau.hpp"

class Joueur;
class Carte;
class GodMode;  // ← LIGNE AJOUTÉE

/**
 * @brief Représente le jeu Hero Realms complet
 * 
 * Le Jeu gère :
 * - La boucle de jeu principale
 * - Les interactions avec les joueurs
 * - Les phases de jeu (jouer, acheter, attaquer)
 * - Les menus et l'interface utilisateur
 */
class Jeu {
public:
    // Constructeur & Destructeur
    Jeu();
    ~Jeu();

    // Initialisation
    /**
     * @brief Lance le jeu et affiche le menu principal
     */
    void lancer();

    /**
     * @brief Démarre une nouvelle partie
     */
    void nouvellePartie();

    /**
     * @brief Configure les joueurs
     */
    void configurerJoueurs();

    // Boucle de jeu
    /**
     * @brief Exécute la boucle de jeu principale
     */
    void boucleDeJeu();

    /**
     * @brief Exécute le tour d'un joueur
     * @param joueur Le joueur actif
     */
    void executerTour(Joueur* joueur);

    // Phases de jeu
    /**
     * @brief Phase de jeu : jouer des cartes
     * @param joueur Le joueur actif
     */
    void phaseJeu(Joueur* joueur);

    /**
     * @brief Phase d'achat : acheter des cartes au marché
     * @param joueur Le joueur actif
     */
    void phaseAchat(Joueur* joueur);

    /**
     * @brief Phase d'attaque : attaquer les adversaires
     * @param joueur Le joueur actif
     */
    void phaseAttaque(Joueur* joueur);

    /**
     * @brief Phase d'activation des champions : utiliser les capacités Expend
     * @param joueur Le joueur actif
     */
    void phaseChampions(Joueur* joueur);

    // Actions de jeu
    /**
     * @brief Joue une carte de la main
     * @param joueur Le joueur actif
     * @param index Index de la carte dans la main
     * @return bool true si la carte a été jouée
     */
    bool jouerCarte(Joueur* joueur, int index);

    /**
     * @brief Achète une carte au marché
     * @param joueur Le joueur actif
     * @param choix 0 pour Gemme de Feu, 1-5 pour cartes du marché
     * @return bool true si l'achat a réussi
     */
    bool acheterCarte(Joueur* joueur, int choix);

    /**
     * @brief Attaque un adversaire ou un champion
     * @param attaquant Le joueur qui attaque
     * @param cible Le joueur cible
     * @param degats Dégâts à infliger
     */
    void attaquer(Joueur* attaquant, Joueur* cible, int degats);

    /**
     * @brief Attaque un champion spécifique
     * @param attaquant Le joueur qui attaque
     * @param cible Le joueur possédant le champion
     * @param index_champion Index du champion à attaquer
     * @param degats Dégâts à infliger
     */
    void attaquerChampion(Joueur* attaquant, Joueur* cible, int index_champion, int degats);

    // Utilitaires
    /**
     * @brief Affiche le menu principal
     */
    void afficherMenuPrincipal() const;

    /**
     * @brief Affiche le menu du tour
     */
    void afficherMenuTour() const;

    /**
     * @brief Affiche les résultats de fin de partie
     */
    void afficherResultats() const;

    /**
     * @brief Pause et attend une entrée utilisateur
     * @param message Message à afficher
     */
    void pause(const std::string& message = "Appuyez sur Entrée pour continuer...") const;

    /**
     * @brief Nettoie l'écran (simulation)
     */
    void clearScreen() const;

    /**
     * @brief Lit un entier depuis l'entrée utilisateur
     * @param min Valeur minimum
     * @param max Valeur maximum
     * @return int La valeur lue
     */
    int lireEntier(int min, int max) const;

    /**
     * @brief Lit une chaîne depuis l'entrée utilisateur
     * @return std::string La chaîne lue
     */
    std::string lireChaine() const;

    /**
     * @brief Demande une confirmation oui/non
     * @param question La question à poser
     * @return bool true si oui, false si non
     */
    bool confirmer(const std::string& question) const;

    // Règles et aide
    /**
     * @brief Affiche les règles du jeu
     */
    void afficherRegles() const;

    /**
     * @brief Affiche l'aide pendant le jeu
     */
    void afficherAide() const;

private:
    Plateau plateau_;
    bool jeu_en_cours_;
    bool quitter_;

    // Configuration
    int nb_joueurs_;
    std::vector<std::string> noms_joueurs_;
    int pv_initial_;
    
    GodMode* god_mode_;  // ← LIGNE AJOUTÉE - Mode triche

    /**
     * @brief Affiche l'écran de titre
     */
    void afficherTitre() const;

    /**
     * @brief Sélectionne la cible d'une attaque
     * @param attaquant Le joueur qui attaque
     * @return Joueur* La cible sélectionnée (nullptr si annulé)
     */
    Joueur* selectionnerCible(Joueur* attaquant) const;

    /**
     * @brief Joue toutes les cartes de la main du joueur
     * @param joueur Le joueur actif
     */
    void jouerToutesLesCartes(Joueur* joueur);

    /**
     * @brief Permet de quitter la partie en cours avec confirmation
     * @return true si le joueur confirme vouloir quitter, false sinon
     */
    bool quitterPartie();
};

#endif // JEU_HPP