#ifndef EFFETCHAMPION_HPP
#define EFFETCHAMPION_HPP

class Joueur;
class Jeu;

/**
 * @brief Classe utilitaire pour les effets spéciaux des champions
 * 
 * Cette classe contient les effets spécifiques aux champions qui nécessitent
 * une logique particulière (pioche conditionnelle, effets d'allié personnalisés, etc.)
 */
class EffetChampion {
public:
    // ════════════════════════════════════════════════════════
    // EFFETS DE PIOCHE CONDITIONNELS (ALLY)
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Effet de pioche pour Cron, the Berserker (Wild Ally : Draw a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void cronBerserkerAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Effet pour Grak, Storm Giant (Draw a card, then discard a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void grakStormGiantAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Effet de pioche pour Orc Grunt (Wild Ally : Draw a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void orcGruntAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Effet de pioche pour Lys, the Unseen (Necros Ally : Draw a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void lysUnseenAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Effet de pioche pour Varrick, the Necromancer (Necros Ally : Draw a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void varrickNecromancerAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Effet de pioche pour Kraka, High Priest (Imperial Ally : Draw a card)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void krakaHighPriestAlly(Joueur* joueur, Jeu* jeu);
};

#endif // EFFETCHAMPION_HPP
