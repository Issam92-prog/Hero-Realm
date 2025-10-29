#include "Regle.hpp"
#include <iostream>
#include <limits>

// ====== Constructeur ======

Regle::Regle() {
}

// ====== Utilitaires Privés ======

void Regle::afficherSeparateur() {
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
}

void Regle::afficherTitre(const std::string& titre) {
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  " << titre;
    // Calculer les espaces pour centrer
    int espaces = 54 - titre.length();
    for (int i = 0; i < espaces; ++i) {
        std::cout << " ";
    }
    std::cout << "║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
}

void Regle::afficherSection(const std::string& titre, const std::string& icone) {
    std::cout << "\n" << icone << " " << titre << ":" << std::endl;
}

// ====== Affichage Principal ======

void Regle::afficherMenuRegles() {
    std::cout << "\n";
    afficherTitre("📖 RÈGLES DE HERO REALMS 📖");

    std::cout << "\n  [1] 📜 Règles Générales" << std::endl;
    std::cout << "  [2] ⚔️  Mode: Chacun pour soi" << std::endl;
    std::cout << "  [3] 🎴 Règles de Base (Types de cartes, Phases)" << std::endl;
    std::cout << "  [0] 🔙 Retour" << std::endl;

    std::cout << "\nChoix: ";
    int choix;
    std::cin >> choix;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choix) {
        case 1:
            afficherReglesGenerales();
            break;
        case 2:
            afficherModeChacunPourSoi();
            break;
        case 3:
            afficherReglesBase();
            break;
        default:
            break;
    }

    if (choix != 0) {
        std::cout << "\nAppuyez sur Entrée pour continuer...";
        std::cin.get();
    }
}

void Regle::afficherReglesGenerales() {
    std::cout << "\n";
    afficherTitre("📜 RÈGLES GÉNÉRALES 📜");

    afficherSection("🎯 OBJECTIF", "🎯");
    std::cout << "   Réduire les points de vie (PV) de tous vos adversaires à 0.\n";
    std::cout << "   Le dernier joueur en vie remporte la partie !\n";

    afficherSection("⚙️  MISE EN PLACE", "⚙️");
    std::cout << "   • Chaque joueur commence avec 50 PV\n";
    std::cout << "   • Chaque joueur a un deck de départ identique :\n";
    std::cout << "     → 7 cartes Or (génèrent 1 💰 or)\n";
    std::cout << "     → 3 cartes Dague (génèrent 1 ⚔️  combat)\n";
    std::cout << "   • Mélangez votre deck et piochez selon votre position\n";
    std::cout << "   • Placez 5 cartes face visible sur le marché\n";
    std::cout << "   • Les Gemmes de Feu sont toujours disponibles (2 💰)\n";

    afficherSection("🎴 DÉROULEMENT D'UN TOUR", "🎴");
    std::cout << "   1️⃣  PHASE DE JEU\n";
    std::cout << "      • Jouez autant de cartes de votre main que vous voulez\n";
    std::cout << "      • Les cartes génèrent de l'Or 💰 et du Combat ⚔️\n";
    std::cout << "      • Les Champions 👤 restent en jeu\n";
    std::cout << "      • Les Actions ⚡ et Items 🔨 vont en défausse\n";

    std::cout << "\n   2️⃣  PHASE D'ACHAT\n";
    std::cout << "      • Utilisez votre Or 💰 pour acheter des cartes au marché\n";
    std::cout << "      • Les cartes achetées vont dans votre défausse\n";
    std::cout << "      • Vous pouvez acheter plusieurs cartes\n";

    std::cout << "\n   3️⃣  PHASE D'ATTAQUE\n";
    std::cout << "      • Utilisez votre Combat ⚔️  pour attaquer\n";
    std::cout << "      • Attaquez les champions adverses ou les joueurs\n";
    std::cout << "      • Les champions Garde 🛡️  doivent être vaincus en premier\n";

    std::cout << "\n   4️⃣  FIN DE TOUR\n";
    std::cout << "      • Défaussez toute votre main\n";
    std::cout << "      • Votre Or 💰 et Combat ⚔️  non utilisés sont perdus\n";
    std::cout << "      • Piochez 5 nouvelles cartes\n";

    afficherSeparateur();
}

void Regle::afficherModeChacunPourSoi() {
    std::cout << "\n";
    afficherTitre("⚔️  MODE: CHACUN POUR SOI ⚔️");

    afficherSection("📊 INFORMATIONS", "📊");
    std::cout << "   • Joueurs: 2 et plus\n";
    std::cout << "   • Durée: 20-40 minutes\n";
    std::cout << "   • Type: Free-for-all (Chacun contre tous)\n";

    afficherSection("📜 RÈGLES", "📜");
    std::cout << "   Ceci est le mode de jeu par défaut de Hero Realms.\n";

    afficherSection("🎲 MISE EN PLACE", "🎲");
    std::cout << "   • Déterminez au hasard qui commencera\n";
    std::cout << "   • Jouez chacun dans le sens des aiguilles d'une montre\n";

    afficherSection("✋ MAIN DE DÉPART", "✋");
    std::cout << "   📌 PARTIE À 2 JOUEURS:\n";
    std::cout << "      • Les 2 joueurs commencent avec 5 cartes\n\n";

    std::cout << "   📌 PARTIE À 3 JOUEURS ET PLUS:\n";
    std::cout << "      • 1er joueur : 3 cartes 🎴🎴🎴\n";
    std::cout << "      • 2ème joueur : 4 cartes 🎴🎴🎴🎴\n";
    std::cout << "      • Autres joueurs : 5 cartes 🎴🎴🎴🎴🎴\n\n";

    std::cout << "   💡 Pourquoi cette différence ?\n";
    std::cout << "      Le premier joueur a un avantage tactique en jouant en premier.\n";
    std::cout << "      Commencer avec moins de cartes compense cet avantage.\n";

    afficherSection("⚔️  RÈGLES DE COMBAT", "⚔️");
    std::cout << "   • Vous pouvez attaquer TOUS les autres joueurs\n";
    std::cout << "   • Vous choisissez qui attaquer à chaque utilisation de Combat\n";
    std::cout << "   • Vous pouvez répartir vos attaques entre plusieurs cibles\n";
    std::cout << "   • Exemple: Avec 6 ⚔️  Combat, vous pouvez:\n";
    std::cout << "      → Attaquer le Joueur A pour 3 dégâts\n";
    std::cout << "      → Attaquer le Joueur B pour 2 dégâts\n";
    std::cout << "      → Attaquer un champion du Joueur C pour 1 dégât\n";

    afficherSection("🛡️  CHAMPIONS GARDE", "🛡️");
    std::cout << "   • Si un joueur a des champions Garde 🛡️  en jeu\n";
    std::cout << "   • Vous DEVEZ d'abord attaquer ces champions\n";
    std::cout << "   • Vous ne pouvez pas attaquer le joueur directement\n";
    std::cout << "   • Une fois tous les Gardes vaincus, vous pouvez attaquer le joueur\n";

    afficherSection("🏆 CONDITION DE VICTOIRE", "🏆");
    std::cout << "   • Le dernier joueur en vie remporte la partie !\n";
    std::cout << "   • Si vous êtes éliminé (0 PV), vous êtes hors jeu\n";
    std::cout << "   • Vos cartes et champions restent visibles mais ne sont plus actifs\n";

    afficherSeparateur();
}

void Regle::afficherReglesBase() {
    std::cout << "\n";
    afficherTitre("🎴 RÈGLES DE BASE 🎴");

    afficherSection("⚔️  TYPES DE CARTES", "⚔️");
    std::cout << "   👤 CHAMPIONS:\n";
    std::cout << "      • Restent en jeu après avoir été joués\n";
    std::cout << "      • Peuvent être attaqués par les adversaires\n";
    std::cout << "      • Ont des points de défense (DEF)\n";
    std::cout << "      • Vont en défausse quand vaincus (0 DEF)\n";
    std::cout << "      • Peuvent avoir des capacités Expend (⏸️)\n\n";

    std::cout << "   ⚡ ACTIONS:\n";
    std::cout << "      • Effet immédiat quand jouées\n";
    std::cout << "      • Vont directement en défausse après utilisation\n";
    std::cout << "      • Génèrent souvent Or, Combat, ou effets spéciaux\n\n";

    std::cout << "   🔨 ITEMS:\n";
    std::cout << "      • Similaires aux Actions\n";
    std::cout << "      • Effet immédiat, vont en défausse\n";
    std::cout << "      • Peuvent souvent être sacrifiées pour un effet bonus\n";

    afficherSection("🌟 FACTIONS", "🌟");
    std::cout << "   🛡️  IMPERIAL (Bleu): Défense et vie\n";
    std::cout << "   🏹 GUILD (Jaune): Or et acquisitions\n";
    std::cout << "   💀 NECROS (Vert): Sacrifice et pioche\n";
    std::cout << "   🐺 WILD (Rouge): Combat et agressivité\n";
    std::cout << "   ⚪ NONE (Gris): Cartes de base neutres\n";

    afficherSection("🤝 EFFETS ALLIÉS", "🤝");
    std::cout << "   • Activés quand vous jouez une autre carte de la même faction\n";
    std::cout << "   • Exemple: \"Allié: Gagnez +2 💰 or\"\n";
    std::cout << "   • Vous pouvez activer plusieurs effets Alliés dans un tour\n";

    afficherSection("💀 SACRIFICE", "💀");
    std::cout << "   • Certaines cartes peuvent être sacrifiées\n";
    std::cout << "   • La carte est retirée du jeu DÉFINITIVEMENT\n";
    std::cout << "   • Vous obtenez un effet puissant en échange\n";
    std::cout << "   • Utilisez-le pour éliminer les cartes faibles de votre deck\n";

    afficherSection("⏸️  EXPEND (Champions)", "⏸️");
    std::cout << "   • Capacité spéciale d'un champion\n";
    std::cout << "   • Peut être utilisée UNE FOIS par tour\n";
    std::cout << "   • Le champion devient \"épuisé\" (expended)\n";
    std::cout << "   • Se réinitialise au début de votre prochain tour\n";

    afficherSection("🛡️  GARDE", "🛡️");
    std::cout << "   • Champion avec la capacité Garde\n";
    std::cout << "   • Protège son propriétaire\n";
    std::cout << "   • DOIT être vaincu avant de pouvoir attaquer le joueur\n";
    std::cout << "   • Très important pour la défense !\n";

    afficherSeparateur();
}

// ====== Utilitaires ======

int Regle::getCartesDepart(int position_joueur, int nb_joueurs_total) {
    // Partie à 2 joueurs : tous commencent avec 5 cartes
    if (nb_joueurs_total == 2) {
        return 5;
    }

    // Partie à 3+ joueurs :
    // Premier joueur : 3 cartes
    // Deuxième joueur : 4 cartes
    // Autres : 5 cartes
    if (position_joueur == 1) {
        return 3;
    } else if (position_joueur == 2) {
        return 4;
    } else {
        return 5;
    }
}