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
    
    // ════════════════════════════════════════════════════════
    // NOUVEAUX EFFETS POUR LES CHAMPIONS MAL IMPLÉMENTÉS
    // ════════════════════════════════════════════════════════
    
    /**
     * @brief Darian, War Mage - Choix entre 3 combat OU 4 santé
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void darianWarMageExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Street Thug / Bandit des Rues - Choix entre 1 or OU 2 combat
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void streetThugExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Krythos, Master Vampire - Sacrifice optionnel pour +3 combat
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void krythosMasterVampireExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Lys, the Unseen - Sacrifice optionnel pour +2 combat
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void lysTheUnseenExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Broelyn, Loreweaver - L'adversaire défausse une carte (Ally)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void broelynLoreweaverAlly(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Torgen Rocksplitter - L'adversaire défausse une carte (Expend)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void torgenRocksplitterExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Rake, Master Assassin - Assommer un champion optionnel
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void rakeMasterAssassinExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Grak, Storm Giant - Piocher puis défausser optionnel (Expend)
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void grakStormGiantExpend(Joueur* joueur, Jeu* jeu);
    
    /**
     * @brief Varrick, the Necromancer - Récupérer un champion de la défausse
     * @param joueur Le joueur propriétaire du champion
     * @param jeu Référence au jeu
     */
    static void varrickNecromancerExpend(Joueur* joueur, Jeu* jeu);
};

#endif // EFFETCHAMPION_HPP