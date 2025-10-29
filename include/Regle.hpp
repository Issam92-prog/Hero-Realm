#ifndef REGLE_HPP
#define REGLE_HPP

#include <string>

/**
 * @brief Représente les règles de Hero Realms
 * 
 * La classe Regle gère :
 * - L'affichage des règles générales
 * - Le mode de jeu "Chacun pour soi"
 */
class Regle {
public:
    // Constructeur
    Regle();

    // Affichage des règles
    /**
     * @brief Affiche le menu des règles
     */
    static void afficherMenuRegles();

    /**
     * @brief Affiche les règles générales du jeu
     */
    static void afficherReglesGenerales();

    /**
     * @brief Affiche les règles du mode "Chacun pour soi"
     */
    static void afficherModeChacunPourSoi();

    /**
     * @brief Affiche les règles de base (types de cartes, phases, etc.)
     */
    static void afficherReglesBase();

    /**
     * @brief Calcule le nombre de cartes de départ selon la position
     * @param position_joueur Position du joueur (1 = premier, 2 = deuxième, etc.)
     * @param nb_joueurs_total Nombre total de joueurs
     * @return int Nombre de cartes à piocher au départ
     */
    static int getCartesDepart(int position_joueur, int nb_joueurs_total);

private:
    /**
     * @brief Affiche un séparateur décoratif
     */
    static void afficherSeparateur();

    /**
     * @brief Affiche un titre encadré
     * @param titre Le titre à afficher
     */
    static void afficherTitre(const std::string& titre);

    /**
     * @brief Affiche une section
     * @param titre Titre de la section
     * @param icone Icône de la section
     */
    static void afficherSection(const std::string& titre, const std::string& icone = "📌");
};

#endif // REGLE_HPP