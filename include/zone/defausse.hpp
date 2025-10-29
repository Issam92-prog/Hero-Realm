#ifndef DEFAUSSE_HPP
#define DEFAUSSE_HPP

#include <vector>
#include <string>

class Carte;

/**
 * @brief Représente la défausse d'un joueur dans Hero Realms
 * 
 * La Défausse gère :
 * - L'ajout de cartes défaussées
 * - La visualisation des cartes défaussées
 * - Le transfert des cartes vers la pioche (remélange)
 */
class Defausse {
public:
    // Constructeur & Destructeur
    Defausse();
    ~Defausse();

    // Gestion des cartes
    /**
     * @brief Ajoute une carte à la défausse
     * @param carte La carte à défausser
     */
    void ajouterCarte(Carte* carte);

    /**
     * @brief Ajoute plusieurs cartes à la défausse
     * @param cartes Vector de cartes à défausser
     */
    void ajouterCartes(const std::vector<Carte*>& cartes);

    /**
     * @brief Retire toutes les cartes de la défausse et les retourne
     * @return std::vector<Carte*> Toutes les cartes de la défausse
     */
    std::vector<Carte*> vider();

    /**
     * @brief Regarde la dernière carte défaussée (sans la retirer)
     * @return const Carte* La dernière carte (nullptr si vide)
     */
    const Carte* voirDerniere() const;

    /**
     * @brief Regarde la carte du dessus (sans la retirer)
     * @return const Carte* La carte du dessus (nullptr si vide)
     */
    const Carte* voirDessus() const;

    /**
     * @brief Retire et retourne la dernière carte défaussée
     * @return Carte* La dernière carte (nullptr si vide)
     */
    Carte* retirerDerniere();

    /**
     * @brief Retire une carte spécifique de la défausse
     * @param carte Pointeur vers la carte à retirer
     * @return bool true si la carte a été trouvée et retirée, false sinon
     */
    bool retirerCarte(Carte* carte);

    // Recherche de cartes
    /**
     * @brief Vérifie si une carte est dans la défausse
     * @param carte Pointeur vers la carte à chercher
     * @return bool true si la carte est présente
     */
    bool contient(Carte* carte) const;

    /**
     * @brief Trouve l'index d'une carte dans la défausse
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

    // Affichage
    /**
     * @brief Affiche la défausse du joueur
     * @param afficher_tout true pour afficher toutes les cartes, false pour un résumé
     */
    void afficher(bool afficher_tout = false) const;

    /**
     * @brief Affiche les dernières cartes défaussées
     * @param n Nombre de cartes à afficher
     */
    void afficherDernieres(int n = 3) const;

    /**
     * @brief Affiche un résumé de la défausse (nombre par faction/type)
     */
    void afficherResume() const;

    // Informations
    /**
     * @brief Nombre de cartes dans la défausse
     * @return size_t Nombre de cartes
     */
    size_t taille() const;

    /**
     * @brief Vérifie si la défausse est vide
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

#endif // DEFAUSSE_HPP