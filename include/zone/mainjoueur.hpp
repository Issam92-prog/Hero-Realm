#ifndef MAINJOUEUR_HPP
#define MAINJOUEUR_HPP

#include <vector>
#include <string>

class Carte;
class CarteAction;
class CarteChampion;
class CarteItem;

/**
 * @brief Représente la main d'un joueur dans Hero Realms
 * 
 * La MainJoueur gère :
 * - L'ajout et le retrait de cartes
 * - L'affichage des cartes disponibles
 * - Le tri et la recherche de cartes
 */
class MainJoueur {
public:
    // Constructeur & Destructeur
    MainJoueur();
    ~MainJoueur();

    // Gestion des cartes
    /**
     * @brief Ajoute une carte à la main
     * @param carte La carte à ajouter
     */
    void ajouterCarte(Carte* carte);

    /**
     * @brief Retire une carte de la main par index
     * @param index L'index de la carte (0-based)
     * @return Carte* La carte retirée (nullptr si index invalide)
     */
    Carte* retirerCarte(size_t index);

    /**
     * @brief Retire une carte spécifique de la main
     * @param carte Pointeur vers la carte à retirer
     * @return bool true si la carte a été trouvée et retirée, false sinon
     */
    bool retirerCarte(Carte* carte);

    /**
     * @brief Vide la main et retourne toutes les cartes
     * @return std::vector<Carte*> Toutes les cartes de la main
     */
    std::vector<Carte*> vider();

    /**
     * @brief Défausse toute la main
     * @param defausse Référence vers la défausse où mettre les cartes
     */
    void defausserTout(std::vector<Carte*>& defausse);

    // Recherche de cartes
    /**
     * @brief Trouve l'index d'une carte dans la main
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
     * @brief Vérifie si une carte est jouable avec l'or disponible
     * @param index Index de la carte
     * @param or_disponible Or disponible
     * @return bool true si la carte est jouable
     */
    bool estJouable(size_t index, int or_disponible) const;

    // Affichage
    /**
     * @brief Affiche la main du joueur
     * @param afficher_details true pour afficher les détails des cartes
     */
    void afficher(bool afficher_details = false) const;

    /**
     * @brief Affiche une carte spécifique de la main
     * @param index Index de la carte à afficher
     */
    void afficherCarte(size_t index) const;

    // Informations
    /**
     * @brief Nombre de cartes dans la main
     * @return size_t Nombre de cartes
     */
    size_t taille() const;

    /**
     * @brief Vérifie si la main est vide
     * @return true si vide, false sinon
     */
    bool estVide() const;

    /**
     * @brief Récupère une carte par index (lecture seule)
     * @param index Index de la carte
     * @return const Carte* Pointeur vers la carte (nullptr si index invalide)
     */
    const Carte* getCarte(size_t index) const;

    /**
     * @brief Récupère une carte par index (modifiable)
     * @param index Index de la carte
     * @return Carte* Pointeur vers la carte (nullptr si index invalide)
     */
    Carte* getCarte(size_t index);

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

#endif // MAINJOUEUR_HPP