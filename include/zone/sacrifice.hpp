#ifndef SACRIFICE_HPP
#define SACRIFICE_HPP

#include <vector>
#include <string>

class Carte;

/**
 * @brief Représente la zone de sacrifice d'un joueur dans Hero Realms
 * 
 * Le Sacrifice gère :
 * - Les cartes retirées définitivement du jeu
 * - Ces cartes ne remélangent JAMAIS dans la pioche
 * - Visualisation des cartes sacrifiées
 */
class Sacrifice {
public:
    // Constructeur & Destructeur
    Sacrifice();
    ~Sacrifice();

    // Gestion des cartes
    /**
     * @brief Ajoute une carte sacrifiée (retirée du jeu)
     * @param carte La carte à sacrifier
     */
    void ajouterCarte(Carte* carte);

    /**
     * @brief Ajoute plusieurs cartes sacrifiées
     * @param cartes Vector de cartes à sacrifier
     */
    void ajouterCartes(const std::vector<Carte*>& cartes);

    /**
     * @brief Retire toutes les cartes et les retourne (pour fin de partie)
     * @return std::vector<Carte*> Toutes les cartes sacrifiées
     */
    std::vector<Carte*> vider();

    /**
     * @brief Regarde la dernière carte sacrifiée (sans la retirer)
     * @return const Carte* La dernière carte (nullptr si vide)
     */
    const Carte* voirDerniere() const;

    /**
     * @brief Retire une carte spécifique (rare, pour effets spéciaux)
     * @param carte Pointeur vers la carte à retirer
     * @return bool true si la carte a été trouvée et retirée
     */
    bool retirerCarte(Carte* carte);

    // Recherche de cartes
    /**
     * @brief Vérifie si une carte est dans la zone sacrifice
     * @param carte Pointeur vers la carte à chercher
     * @return bool true si la carte est présente
     */
    bool contient(Carte* carte) const;

    /**
     * @brief Trouve l'index d'une carte dans la zone
     * @param carte Pointeur vers la carte à trouver
     * @return int L'index de la carte (-1 si non trouvée)
     */
    int trouverCarte(Carte* carte) const;

    /**
     * @brief Compte le nombre de cartes d'une faction
     * @param faction La faction à compter
     * @return int Nombre de cartes de cette faction
     */
    int compterFaction(int faction) const;

    /**
     * @brief Compte le nombre de cartes d'un type
     * @param type Le type à compter
     * @return int Nombre de cartes de ce type
     */
    int compterType(int type) const;

    /**
     * @brief Compte le nombre de fois qu'une carte a été sacrifiée
     * @param nom_carte Nom de la carte à compter
     * @return int Nombre d'exemplaires sacrifiés
     */
    int compterCarte(const std::string& nom_carte) const;

    // Affichage
    /**
     * @brief Affiche toutes les cartes sacrifiées
     * @param afficher_tout true pour tout afficher, false pour un résumé
     */
    void afficher(bool afficher_tout = true) const;

    /**
     * @brief Affiche un résumé des cartes sacrifiées (par nom)
     */
    void afficherResume() const;

    /**
     * @brief Affiche les statistiques de sacrifice
     */
    void afficherStatistiques() const;

    // Informations
    /**
     * @brief Nombre de cartes sacrifiées
     * @return size_t Nombre total de cartes
     */
    size_t taille() const;

    /**
     * @brief Vérifie si aucune carte n'a été sacrifiée
     * @return true si vide, false sinon
     */
    bool estVide() const;

    /**
     * @brief Récupère une carte par index (lecture seule)
     * @param index Index de la carte
     * @return const Carte* Pointeur vers la carte (nullptr si index invalide)
     */
    const Carte* getCarte(size_t index) const;

    // Accès direct
    std::vector<Carte*>& cartes();
    const std::vector<Carte*>& cartes() const;

    // Opérateur [] pour accès direct
    Carte* operator[](size_t index);
    const Carte* operator[](size_t index) const;

private:
    std::vector<Carte*> cartes_;

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

#endif // SACRIFICE_HPP