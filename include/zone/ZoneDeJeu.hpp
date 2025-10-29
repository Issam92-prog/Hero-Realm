#ifndef ZONEDEJEU_HPP
#define ZONEDEJEU_HPP

#include <vector>
#include <string>

class CarteChampion;
class Joueur;

/**
 * @brief Représente la zone de jeu d'un joueur dans Hero Realms
 * 
 * La ZoneDeJeu gère :
 * - Les champions actifs sur la table
 * - Les attaques sur les champions
 * - La préparation des champions pour un nouveau tour
 * - La gestion des champions Garde
 */
class ZoneDeJeu {
public:
    // Constructeur & Destructeur
    ZoneDeJeu();
    ~ZoneDeJeu();

    // Gestion des champions
    /**
     * @brief Ajoute un champion à la zone de jeu
     * @param champion Le champion à ajouter
     */
    void ajouterChampion(CarteChampion* champion);

    /**
     * @brief Retire un champion de la zone de jeu
     * @param champion Le champion à retirer
     * @return bool true si le champion a été trouvé et retiré
     */
    bool retirerChampion(CarteChampion* champion);

    /**
     * @brief Retire un champion par index
     * @param index Index du champion (0-based)
     * @return CarteChampion* Le champion retiré (nullptr si index invalide)
     */
    CarteChampion* retirerChampion(size_t index);

    /**
     * @brief Prépare tous les champions pour un nouveau tour (reset expended)
     */
    void preparerTous();

    /**
     * @brief Retire les champions morts et les met en défausse
     * @param defausse Vector de cartes où mettre les champions morts
     * @return int Nombre de champions retirés
     */
    int retirerMorts(std::vector<class Carte*>& defausse);

    /**
     * @brief Vide la zone de jeu et retourne tous les champions
     * @return std::vector<CarteChampion*> Tous les champions
     */
    std::vector<CarteChampion*> vider();

    // Recherche de champions
    /**
     * @brief Trouve l'index d'un champion
     * @param champion Le champion à chercher
     * @return int L'index (-1 si non trouvé)
     */
    int trouverChampion(CarteChampion* champion) const;

    /**
     * @brief Vérifie si un champion est dans la zone
     * @param champion Le champion à chercher
     * @return bool true si présent
     */
    bool contient(CarteChampion* champion) const;

    /**
     * @brief Récupère un champion par index (lecture seule)
     * @param index Index du champion
     * @return const CarteChampion* Le champion (nullptr si invalide)
     */
    const CarteChampion* getChampion(size_t index) const;

    /**
     * @brief Récupère un champion par index (modifiable)
     * @param index Index du champion
     * @return CarteChampion* Le champion (nullptr si invalide)
     */
    CarteChampion* getChampion(size_t index);

    // Gestion des Gardes
    /**
     * @brief Vérifie si au moins un champion Garde est vivant
     * @return bool true s'il y a au moins un garde vivant
     */
    bool aChampionsGarde() const;

    /**
     * @brief Compte le nombre de champions Garde vivants
     * @return int Nombre de gardes
     */
    int compterGardes() const;

    /**
     * @brief Récupère tous les champions Garde vivants
     * @return std::vector<CarteChampion*> Liste des gardes
     */
    std::vector<CarteChampion*> getChampionsGarde();

    // Statistiques
    /**
     * @brief Compte le nombre de champions d'une faction
     * @param faction La faction à compter
     * @return int Nombre de champions de cette faction
     */
    int compterFaction(int faction) const;

    /**
     * @brief Compte le nombre de champions vivants
     * @return int Nombre de champions vivants
     */
    int compterVivants() const;

    /**
     * @brief Compte le nombre de champions expended
     * @return int Nombre de champions déjà utilisés
     */
    int compterExpended() const;

    /**
     * @brief Calcule la défense totale de tous les champions
     * @return int Défense totale
     */
    int defenseTotal() const;

    // Affichage
    /**
     * @brief Affiche tous les champions en jeu
     * @param afficher_details true pour afficher les détails
     */
    void afficher(bool afficher_details = false) const;

    /**
     * @brief Affiche un champion spécifique
     * @param index Index du champion
     */
    void afficherChampion(size_t index) const;

    // Informations
    /**
     * @brief Nombre de champions en jeu
     * @return size_t Nombre de champions
     */
    size_t taille() const;

    /**
     * @brief Vérifie si la zone est vide
     * @return bool true si vide
     */
    bool estVide() const;

    // Accès direct
    std::vector<CarteChampion*>& champions();
    const std::vector<CarteChampion*>& champions() const;

    // Opérateur [] pour accès direct
    CarteChampion* operator[](size_t index);
    const CarteChampion* operator[](size_t index) const;

private:
    std::vector<CarteChampion*> champions_;

    /**
     * @brief Retourne l'icône correspondant à la faction
     * @param faction La faction
     * @return std::string L'icône unicode
     */
    std::string getIconeFaction(int faction) const;
};

#endif // ZONEDEJEU_HPP