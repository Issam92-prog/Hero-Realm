#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <vector>
#include <memory>
#include "zone/Marche.hpp"

class Joueur;
class Carte;

/**
 * @brief Représente le plateau de jeu dans Hero Realms
 * 
 * Le Plateau gère :
 * - Le marché partagé entre tous les joueurs
 * - La liste des joueurs
 * - L'ordre des tours
 * - L'état général de la partie
 */
class Plateau {
public:
    // Constructeur & Destructeur
    Plateau();
    ~Plateau();

    // Initialisation
    /**
     * @brief Initialise le plateau avec les joueurs
     * @param noms_joueurs Vector des noms des joueurs
     * @param pv_initial Points de vie initiaux (50 par défaut)
     */
    void initialiser(const std::vector<std::string>& noms_joueurs, int pv_initial = 50);

    /**
     * @brief Ajoute un joueur au plateau
     * @param nom Nom du joueur
     * @param pv_initial Points de vie initiaux
     * @return Joueur* Pointeur vers le joueur créé
     */
    Joueur* ajouterJoueur(const std::string& nom, int pv_initial = 50);

    /**
     * @brief Nettoie la mémoire du plateau
     */
    void nettoyer();

    // Gestion des tours
    /**
     * @brief Démarre la partie
     */
    void demarrerPartie();

    /**
     * @brief Passe au joueur suivant
     */
    void joueurSuivant();

    /**
     * @brief Récupère le joueur actif
     * @return Joueur* Le joueur dont c'est le tour
     */
    Joueur* joueurActif();

    /**
     * @brief Récupère le joueur actif (const)
     * @return const Joueur* Le joueur dont c'est le tour
     */
    const Joueur* joueurActif() const;

    /**
     * @brief Récupère le numéro du tour actuel
     * @return int Numéro du tour (commence à 1)
     */
    int numeroTour() const;

    /**
     * @brief Récupère l'index du joueur actif
     * @return int Index du joueur actif
     */
    int indexJoueurActif() const;

    // Gestion de la partie
    /**
     * @brief Vérifie si la partie est terminée
     * @return bool true si au moins un joueur est mort
     */
    bool partieTerminee() const;

    /**
     * @brief Récupère le(s) gagnant(s)
     * @return std::vector<Joueur*> Liste des joueurs vivants
     */
    std::vector<Joueur*> gagnants() const;

    /**
     * @brief Compte le nombre de joueurs vivants
     * @return int Nombre de joueurs vivants
     */
    int nbJoueursVivants() const;

    /**
     * @brief Récupère tous les adversaires du joueur actif
     * @return std::vector<Joueur*> Liste des adversaires
     */
    std::vector<Joueur*> adversaires() const;

    /**
     * @brief Récupère tous les adversaires d'un joueur spécifique
     * @param joueur Le joueur
     * @return std::vector<Joueur*> Liste des adversaires
     */
    std::vector<Joueur*> adversairesDe(const Joueur* joueur) const;

    // Accès au marché
    /**
     * @brief Récupère le marché
     * @return Marche& Référence vers le marché
     */
    Marche& marche();

    /**
     * @brief Récupère le marché (const)
     * @return const Marche& Référence vers le marché
     */
    const Marche& marche() const;

    // Accès aux joueurs
    /**
     * @brief Récupère un joueur par index
     * @param index Index du joueur
     * @return Joueur* Pointeur vers le joueur (nullptr si invalide)
     */
    Joueur* getJoueur(size_t index);

    /**
     * @brief Récupère un joueur par index (const)
     * @param index Index du joueur
     * @return const Joueur* Pointeur vers le joueur (nullptr si invalide)
     */
    const Joueur* getJoueur(size_t index) const;

    /**
     * @brief Récupère un joueur par ID
     * @param id ID du joueur
     * @return Joueur* Pointeur vers le joueur (nullptr si non trouvé)
     */
    Joueur* getJoueurParId(Joueur::Id id);

    /**
     * @brief Nombre de joueurs
     * @return size_t Nombre total de joueurs
     */
    size_t nbJoueurs() const;

    /**
     * @brief Récupère tous les joueurs
     * @return const std::vector<Joueur*>& Liste des joueurs
     */
    const std::vector<Joueur*>& joueurs() const;

    // Affichage
    /**
     * @brief Affiche l'état complet du plateau
     */
    void afficher() const;

    /**
     * @brief Affiche l'état de tous les joueurs
     */
    void afficherJoueurs() const;

    /**
     * @brief Affiche le marché
     * @param afficher_details true pour afficher les détails
     */
    void afficherMarche(bool afficher_details = false) const;

    /**
     * @brief Affiche les statistiques de la partie
     */
    void afficherStatistiques() const;

    /**
     * @brief Affiche le classement des joueurs
     */
    void afficherClassement() const;

    // Opérateur [] pour accès direct aux joueurs
    Joueur* operator[](size_t index);
    const Joueur* operator[](size_t index) const;

private:
    Marche marche_;                      // Le marché partagé
    std::vector<Joueur*> joueurs_;       // Liste des joueurs
    int joueur_actif_index_;             // Index du joueur actif
    int numero_tour_;                    // Numéro du tour actuel
    bool partie_demarree_;               // État de la partie

    /**
     * @brief Génère un ID unique pour un joueur
     * @return Joueur::Id Un ID unique
     */
    Joueur::Id genererIdJoueur();

    /**
     * @brief Prochain ID disponible
     */
    Joueur::Id prochain_id_;
};

#endif // PLATEAU_HPP