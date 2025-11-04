#ifndef EFFETACTION_HPP
#define EFFETACTION_HPP

class Joueur;
class Game;

/**
 * @brief Classe utilitaire pour les effets spéciaux des cartes
 * 
 * Cette classe contient tous les effets qui ne peuvent pas être
 * représentés par de simples valeurs numériques (or/combat/santé/pioche).
 */
class EffetAction {
public:
    // ════════════════════════════════════════════════════════
    // CALCULS DYNAMIQUES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Gain X combat par champion en jeu
     * @param joueur Le joueur bénéficiaire
     * @param multiplicateur Le bonus par champion (ex: 2 pour Close Ranks)
     */
    static void bonusCombatParChampion(Joueur* joueur, int multiplicateur);
    
    /**
     * @brief Gain X santé par champion en jeu
     * @param joueur Le joueur bénéficiaire
     * @param multiplicateur Le bonus par champion (ex: 1 pour Recruit)
     */
    static void bonusSanteParChampion(Joueur* joueur, int multiplicateur);
    
    /**
     * @brief Gain X or par champion en jeu
     * @param joueur Le joueur bénéficiaire
     * @param multiplicateur Le bonus par champion (ex: 1 pour Devotion)
     */
    static void bonusOrParChampion(Joueur* joueur, int multiplicateur);
    
    // ════════════════════════════════════════════════════════
    // ACTIONS SPÉCIALES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Prépare un champion (le rend réutilisable)
     * @param joueur Le joueur propriétaire
     * @param game Référence au jeu (pour interface)
     */
    static void preparerChampion(Joueur* joueur, Game* game);
    
    /**
     * @brief Assomme un champion adverse
     * @param attaquant Le joueur qui cible
     * @param game Référence au jeu
     */
    static void assommerChampion(Joueur* attaquant, Game* game);
    
    /**
     * @brief Défausse une carte de la main adverse
     * @param attaquant Le joueur qui force la défausse
     * @param game Référence au jeu
     */
    static void defausserCarteAdverse(Joueur* attaquant, Game* game);
    
    /**
     * @brief Sacrifice une carte de la main ou défausse du joueur
     * @param joueur Le joueur qui sacrifie
     * @param game Référence au jeu
     */
    static void sacrifierAutreCarte(Joueur* joueur, Game* game);
    
    // ════════════════════════════════════════════════════════
    // MANIPULATION DE PILES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Place une carte de la défausse sur le dessus du deck
     * @param joueur Le joueur bénéficiaire
     * @param game Référence au jeu
     */
    static void defausseSurDeck(Joueur* joueur, Game* game);
    
    // ════════════════════════════════════════════════════════
    // FLAGS TEMPORAIRES
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Active le flag "prochaine action sur le deck"
     * @param joueur Le joueur bénéficiaire
     */
    static void prochaineActionSurDeck(Joueur* joueur);
    
    /**
     * @brief Active le flag "prochaine carte en main"
     * @param joueur Le joueur bénéficiaire
     */
    static void prochaineCarteEnMain(Joueur* joueur);
    
    /**
     * @brief Active le flag "prochain champion sur le deck"
     * @param joueur Le joueur bénéficiaire
     */
    static void prochainChampionSurDeck(Joueur* joueur);
    
    // ════════════════════════════════════════════════════════
    // CHOIX CONDITIONNELS
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Piocher une carte puis défausser une carte (choix)
     * @param joueur Le joueur bénéficiaire
     * @param game Référence au jeu
     */
    static void piocherPuisDefausser(Joueur* joueur, Game* game);
    
    /**
     * @brief Piocher jusqu'à N cartes, puis défausser autant
     * @param joueur Le joueur bénéficiaire
     * @param max Nombre maximum de cartes à piocher
     * @param game Référence au jeu
     */
    static void piocherEtDefausserVariable(Joueur* joueur, int max, Game* game);
    
    // ════════════════════════════════════════════════════════
    // EFFETS DE ZONE (AOE)
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Inflige des dégâts au joueur et à tous ses champions
     * @param attaquant Le joueur qui inflige les dégâts
     * @param degats Montant des dégâts
     * @param game Référence au jeu
     */
    static void degatsDeZone(Joueur* attaquant, int degats, Game* game);
};

#endif // EFFETACTION_HPP