#include "cartes/CarteDB.hpp"
#include "effets/EffetAction.hpp"
#include "effets/EffetChampion.hpp"
#include "Joueur/Joueur.hpp"

std::vector<Carte*> CarteDB::getFireGems() {
    std::vector<Carte*> cards;
    
    // Gemme de Feu (16 exemplaires)
    CarteItem* gemme = new CarteItem(16, "Gemme de Feu", 2, NONE, 2, 0);
    gemme->setDescription("Gain 2 gold\nSacrifice: Gain 3 combat");
    gemme->setEffetSacrifice(0, 3);
    cards.push_back(gemme);
    
    return cards;
}

std::vector<Carte*> CarteDB::getImperialCards() {
    std::vector<Carte*> cards;
    
    // Arkus, Dragon Impérial (1 exemplaire)
    CarteChampion* arkus = new CarteChampion(1, "Arkus, Dragon Impérial", 8, IMPERIAL, 6, true);
    arkus->setDescription("Expend: Gain 5 combat. Draw a card.\nAlly: Gain 6 health");
    arkus->setEffetExpend(0, 5, 0, 1);
    arkus->setEffetAllie(0, 0, 6, 0);
    cards.push_back(arkus);
    
    // ════════════════════════════════════════════════════════
    // Serrer les Rangs (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* serrer = new CarteAction(1, "Serrer les Rangs", 3, IMPERIAL);
    serrer->setDescription("Gain 5 combat. +2 combat for each champion you have in play.\nAlly: Gain 6 health");
    serrer->setEffetPrincipal(0, 5, 0, 0);
    serrer->setEffetAllie(0, 0, 6, 0);
    // ← EFFET SPÉCIAL : +2 combat par champion
    serrer->setEffetSpecialPrincipal([](Joueur* j, Game* /*g*/) {
        EffetAction::bonusCombatParChampion(j, 2);
    });
    cards.push_back(serrer);
    
    // Commandement (1 exemplaire)
    CarteAction* commandement = new CarteAction(1, "Commandement", 5, IMPERIAL);
    commandement->setDescription("Gain 2 gold, 3 combat, 4 health. Draw a card.");
    commandement->setEffetPrincipal(2, 3, 4, 1);
    cards.push_back(commandement);
    
    // ════════════════════════════════════════════════════════
    // Darian, Mage de Guerre (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* darian = new CarteChampion(1, "Darian, Mage de Guerre", 4, IMPERIAL, 5, false);
    darian->setDescription("Expend: Gain 3 combat or 4 health");
    darian->setEffetExpend(0, 0, 0, 0); // Pas d'effets automatiques
    darian->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::darianWarMageExpend(j, g);
    });
    cards.push_back(darian);
    
    // ════════════════════════════════════════════════════════
    // Domination (1 exemplaire) - EFFET SPÉCIAL ALLIÉ
    // ════════════════════════════════════════════════════════
    CarteAction* domination = new CarteAction(1, "Domination", 7, IMPERIAL);
    domination->setDescription("Gain 6 combat, 6 health. Draw a card.\nAlly: Prepare a champion");
    domination->setEffetPrincipal(0, 6, 6, 1);
    // ← EFFET SPÉCIAL ALLIÉ : Préparer un champion
    domination->setEffetSpecialAllie([](Joueur* j, Game* g) {
        EffetAction::preparerChampion(j, g);
    });
    cards.push_back(domination);
    
    // Cristov, le Juste (1 exemplaire)
    CarteChampion* cristov = new CarteChampion(1, "Cristov, le Juste", 5, IMPERIAL, 5, true);
    cristov->setDescription("Expend: Gain 2 combat, 3 health\nAlly: Draw a card");
    cristov->setEffetExpend(0, 2, 3, 0);
    cristov->setEffetAllie(0, 0, 0, 1);
    cards.push_back(cristov);
    
    // ════════════════════════════════════════════════════════
    // Kraka, Grand Prêtre (1 exemplaire)
    // ════════════════════════════════════════════════════════
    CarteChampion* kraka = new CarteChampion(1, "Kraka, Grand Prêtre", 6, IMPERIAL, 6, false);
    kraka->setDescription("Expend: Gain 2 health. Draw a card.\nAlly: Draw a card");
    kraka->setEffetExpend(0, 0, 2, 1);
    kraka->setEffetAllie(0, 0, 0, 1); // Pioche 1 carte
    cards.push_back(kraka);
    
    // Homme d'Armes (2 exemplaires)
    CarteChampion* homme = new CarteChampion(2, "Homme d'Armes", 3, IMPERIAL, 4, true);
    homme->setDescription("Expend: Gain 2 combat. +1 combat for each other guard you have in play");
    homme->setEffetExpend(0, 2, 0, 0);
    // TODO: Effet bonus combat par garde
    cards.push_back(homme);
    
    // Maître Weyan (1 exemplaire)
    CarteChampion* weyan = new CarteChampion(1, "Maître Weyan", 4, IMPERIAL, 4, true);
    weyan->setDescription("Expend: Gain 3 combat. +1 combat for each other champion you have in play");
    weyan->setEffetExpend(0, 3, 0, 0);
    // TODO: Effet bonus combat par champion (dans expend champion)
    cards.push_back(weyan);
    
    // ════════════════════════════════════════════════════════
    // Ralliement des Troupes (1 exemplaire) - EFFET SPÉCIAL ALLIÉ
    // ════════════════════════════════════════════════════════
    CarteAction* ralliement = new CarteAction(1, "Ralliement des Troupes", 4, IMPERIAL);
    ralliement->setDescription("Gain 5 combat, 5 health\nAlly: Prepare a champion");
    ralliement->setEffetPrincipal(0, 5, 5, 0);
    // ← EFFET SPÉCIAL ALLIÉ : Préparer un champion
    ralliement->setEffetSpecialAllie([](Joueur* j, Game* g) {
        EffetAction::preparerChampion(j, g);
    });
    cards.push_back(ralliement);
    
    // ════════════════════════════════════════════════════════
    // Recrutement (3 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* recrutement = new CarteAction(3, "Recrutement", 2, IMPERIAL);
    recrutement->setDescription("Gain 2 gold, 3 health. +1 health for each champion you have in play\nAlly: Gain 1 gold");
    recrutement->setEffetPrincipal(2, 0, 3, 0);
    recrutement->setEffetAllie(1, 0, 0, 0);

    // ← EFFET SPÉCIAL : +1 santé par champion EN JEU
    recrutement->setEffetSpecialPrincipal([](Joueur* j, Game* /*g*/) {
         int nb_champions = j->compterChampionsEnJeu();
         if (nb_champions > 0) {
             std::cout << "   ✨ Bonus : +" << nb_champions << " santé (" 
                       << nb_champions << " champion(s) × 1)" << std::endl;
             j->soigner(nb_champions);
         }
    });
    cards.push_back(recrutement);
    
    // Percepteur de Dîme (2 exemplaires)
    CarteChampion* percepteur = new CarteChampion(2, "Percepteur de Dîme", 2, IMPERIAL, 3, false);
    percepteur->setDescription("Expend: Gain 1 gold or gain 1 health for each champion you have in play");
    percepteur->setEffetExpend(1, 0, 0, 0);
    // TODO: Choix or ou santé × champions
    cards.push_back(percepteur);
    
    // Taxation (3 exemplaires)
    CarteAction* taxation = new CarteAction(3, "Taxation", 1, IMPERIAL);
    taxation->setDescription("Gain 2 gold\nAlly: Gain 6 health");
    taxation->setEffetPrincipal(2, 0, 0, 0);
    taxation->setEffetAllie(0, 0, 6, 0);
    cards.push_back(taxation);
    
    // Parole de Puissance (1 exemplaire)
    CarteAction* parole = new CarteAction(1, "Parole de Puissance", 6, IMPERIAL);
    parole->setDescription("Draw two cards\nAlly: Gain 5 health\nSacrifice: Gain 5 combat");
    parole->setEffetPrincipal(0, 0, 0, 2);
    parole->setEffetAllie(0, 0, 5, 0);
    parole->setEffetSacrifice(0, 5, 0, 0);
    cards.push_back(parole);
    
    return cards;
}

std::vector<Carte*> CarteDB::getGuildCards() {
    std::vector<Carte*> cards;
    
    // Borg, Mercenaire Ogre (1 exemplaire)
    CarteChampion* borg = new CarteChampion(1, "Borg, Mercenaire Ogre", 6, GUILD, 6, true);
    borg->setDescription("Expend: Gain 4 combat");
    borg->setEffetExpend(0, 4, 0, 0);
    cards.push_back(borg);
    
    // Pot-de-Vin (3 exemplaires)
    CarteAction* pot = new CarteAction(3, "Pot-de-Vin", 3, GUILD);
    pot->setDescription("Gain 3 gold\nAlly: Put the next action you acquire this turn on top of your deck");
    pot->setEffetPrincipal(3, 0, 0, 0);
    // ← EFFET SPÉCIAL ALLIÉ : Prochaine action sur deck
    pot->setEffetSpecialAllie([](Joueur* j, Game* /*g*/) {
        EffetAction::prochaineActionSurDeck(j);
    });
    cards.push_back(pot);
    
    // Menace de Mort (1 exemplaire)
    CarteAction* menace = new CarteAction(1, "Menace de Mort", 3, GUILD);
    menace->setDescription("Gain 1 combat. Draw a card.\nAlly: Stun target champion");
    menace->setEffetPrincipal(0, 1, 0, 1);
    // ← EFFET SPÉCIAL ALLIÉ : Assommer champion
    menace->setEffetSpecialAllie([](Joueur* j, Game* g) {
        EffetAction::assommerChampion(j, g);
    });
    cards.push_back(menace);
    
    // Fourberie (1 exemplaire)
    CarteAction* fourberie = new CarteAction(1, "Fourberie", 5, GUILD);
    fourberie->setDescription("Gain 2 gold. Draw a card.\nAlly: Put the next card you acquire this turn into your hand");
    fourberie->setEffetPrincipal(2, 0, 0, 1);
    // ← EFFET SPÉCIAL ALLIÉ : Prochaine carte en main
    fourberie->setEffetSpecialAllie([](Joueur* j, Game* /*g*/) {
        EffetAction::prochaineCarteEnMain(j);
    });
    cards.push_back(fourberie);
    
    // Bombe Incendiaire (1 exemplaire)
    CarteAction* bombe = new CarteAction(1, "Bombe Incendiaire", 8, GUILD);
    bombe->setDescription("Gain 8 combat. Stun target champion. Draw a card.\nSacrifice: Gain 5 combat");
    bombe->setEffetPrincipal(0, 8, 0, 1);
    bombe->setEffetSacrifice(0, 5, 0, 0);
    // ← EFFET SPÉCIAL PRINCIPAL : Assommer champion
    bombe->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::assommerChampion(j, g);
    });
    cards.push_back(bombe);
    
    // Mise à Prix (1 exemplaire)
    CarteAction* mise = new CarteAction(1, "Mise à Prix", 4, GUILD);
    mise->setDescription("Gain 7 combat\nAlly: Stun target champion");
    mise->setEffetPrincipal(0, 7, 0, 0);
    // ← EFFET SPÉCIAL ALLIÉ : Assommer champion
    mise->setEffetSpecialAllie([](Joueur* j, Game* g) {
        EffetAction::assommerChampion(j, g);
    });
    cards.push_back(mise);
    
    // Intimidation (2 exemplaires)
    CarteAction* intimidation = new CarteAction(2, "Intimidation", 2, GUILD);
    intimidation->setDescription("Gain 5 combat\nAlly: Gain 2 gold");
    intimidation->setEffetPrincipal(0, 5, 0, 0);
    intimidation->setEffetAllie(2, 0, 0, 0);
    cards.push_back(intimidation);
    
    // Myros, Mage de la Guilde (1 exemplaire)
    CarteChampion* myros = new CarteChampion(1, "Myros, Mage de la Guilde", 5, GUILD, 3, true);
    myros->setDescription("Expend: Gain 3 gold\nAlly: Gain 4 combat");
    myros->setEffetExpend(3, 0, 0, 0);
    myros->setEffetAllie(0, 4, 0, 0);
    cards.push_back(myros);
    
    // Parov, l'Exécuteur (1 exemplaire)
    CarteChampion* parov = new CarteChampion(1, "Parov, l'Exécuteur", 5, GUILD, 5, true);
    parov->setDescription("Expend: Gain 3 combat\nAlly: Draw a card");
    parov->setEffetExpend(0, 3, 0, 0);
    parov->setEffetAllie(0, 0, 0, 1);
    cards.push_back(parov);
    
    // Bénéfice (3 exemplaires)
    CarteAction* benefice = new CarteAction(3, "Bénéfice", 1, GUILD);
    benefice->setDescription("Gain 2 gold\nAlly: Gain 4 combat");
    benefice->setEffetPrincipal(2, 0, 0, 0);
    benefice->setEffetAllie(0, 4, 0, 0);
    cards.push_back(benefice);
    
    // ════════════════════════════════════════════════════════
    // Rake, Maître Assassin (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* rake = new CarteChampion(1, "Rake, Maître Assassin", 7, GUILD, 7, false);
    rake->setDescription("Expend: Gain 4 combat. You may stun target champion");
    rake->setEffetExpend(0, 4, 0, 0);
    rake->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::rakeMasterAssassinExpend(j, g);
    });
    cards.push_back(rake);
    
    // Rasmus, le Contrebandier (1 exemplaire)
    CarteChampion* rasmus = new CarteChampion(1, "Rasmus, le Contrebandier", 4, GUILD, 5, false);
    rasmus->setDescription("Expend: Gain 2 gold\nAlly: Put the next card you acquire this turn on top of your deck");
    rasmus->setEffetExpend(2, 0, 0, 0);
    // TODO: Effet allié prochaine carte sur deck (champion)
    cards.push_back(rasmus);
    
    // ════════════════════════════════════════════════════════
    // Casser et Piller (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* casser = new CarteAction(1, "Casser et Piller", 6, GUILD);
    casser->setDescription("Gain 6 combat. You may put a card from your discard pile on top of your deck");
    casser->setEffetPrincipal(0, 6, 0, 0);
    // ← EFFET SPÉCIAL : Défausse → Deck
    casser->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::defausseSurDeck(j, g);
    });
    cards.push_back(casser);
    
    // ════════════════════════════════════════════════════════
    // Bandit des Rues (2 exemplaires) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* bandit = new CarteChampion(2, "Bandit des Rues", 3, GUILD, 4, false);
    bandit->setDescription("Expend: Gain 1 gold or 2 combat");
    bandit->setEffetExpend(0, 0, 0, 0); // Pas d'effets automatiques
    bandit->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::streetThugExpend(j, g);
    });
    cards.push_back(bandit);
    
    return cards;
}

std::vector<Carte*> CarteDB::getNecrosCards() {
    std::vector<Carte*> cards;
    
    // Prêtre du Culte (2 exemplaires)
    CarteChampion* pretre = new CarteChampion(2, "Prêtre du Culte", 3, NECROS, 4, false);
    pretre->setDescription("Expend: Gain 1 gold or 1 combat\nAlly: Gain 4 combat");
    pretre->setEffetExpend(1, 0, 0, 0);
    pretre->setEffetAllie(0, 4, 0, 0);
    // TODO: Choix or ou combat
    cards.push_back(pretre);
    
    // Énergie Sombre (1 exemplaire)
    CarteAction* energie = new CarteAction(1, "Énergie Sombre", 4, NECROS);
    energie->setDescription("Gain 7 combat\nAlly: Draw a card");
    energie->setEffetPrincipal(0, 7, 0, 0);
    energie->setEffetAllie(0, 0, 0, 1);
    cards.push_back(energie);
    
    // ════════════════════════════════════════════════════════
    // Sombre Récompense (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* recompense = new CarteAction(1, "Sombre Récompense", 5, NECROS);
    recompense->setDescription("Gain 3 gold. You may sacrifice a card in your hand or discard pile\nAlly: Gain 6 combat");
    recompense->setEffetPrincipal(3, 0, 0, 0);
    recompense->setEffetAllie(0, 6, 0, 0);
    // ← EFFET SPÉCIAL : Sacrifier autre carte
    recompense->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::sacrifierAutreCarte(j, g);
    });
    cards.push_back(recompense);
    
    // Cultiste de la Mort (2 exemplaires)
    CarteChampion* cultiste = new CarteChampion(2, "Cultiste de la Mort", 2, NECROS, 3, true);
    cultiste->setDescription("Expend: Gain 2 combat");
    cultiste->setEffetExpend(0, 2, 0, 0);
    cards.push_back(cultiste);
    
    // ════════════════════════════════════════════════════════
    // Contact Mortel (3 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* contact = new CarteAction(3, "Contact Mortel", 1, NECROS);
    contact->setDescription("Gain 2 combat. You may sacrifice a card in your hand or discard pile\nAlly: Gain 2 combat");
    contact->setEffetPrincipal(0, 2, 0, 0);
    contact->setEffetAllie(0, 2, 0, 0);
    // ← EFFET SPÉCIAL : Sacrifier autre carte
    contact->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::sacrifierAutreCarte(j, g);
    });
    cards.push_back(contact);
    
    // Rayla, Tisseuse de Fins (1 exemplaire)
    CarteChampion* rayla = new CarteChampion(1, "Rayla, Tisseuse de Fins", 4, NECROS, 4, false);
    rayla->setDescription("Expend: Gain 3 combat\nAlly: Draw a card");
    rayla->setEffetExpend(0, 3, 0, 0);
    rayla->setEffetAllie(0, 0, 0, 1);
    cards.push_back(rayla);
    
    // Influence (3 exemplaires)
    CarteAction* influence = new CarteAction(3, "Influence", 2, NECROS);
    influence->setDescription("Gain 3 gold\nSacrifice: Gain 3 combat");
    influence->setEffetPrincipal(3, 0, 0, 0);
    influence->setEffetSacrifice(0, 3, 0, 0);
    cards.push_back(influence);
    
    // ════════════════════════════════════════════════════════
    // Krythos, Maître Vampire (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* krythos = new CarteChampion(1, "Krythos, Maître Vampire", 7, NECROS, 6, false);
    krythos->setDescription("Expend: Gain 3 combat. You may sacrifice a card in your hand or discard pile. If you do, gain an additional 3 combat");
    krythos->setEffetExpend(0, 3, 0, 0);
    krythos->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::krythosMasterVampireExpend(j, g);
    });
    cards.push_back(krythos);
    
    // ════════════════════════════════════════════════════════
    // Drain de Vie (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* drain = new CarteAction(1, "Drain de Vie", 6, NECROS);
    drain->setDescription("Gain 8 combat. You may sacrifice a card in your hand or discard pile\nAlly: Draw a card");
    drain->setEffetPrincipal(0, 8, 0, 0);
    drain->setEffetAllie(0, 0, 0, 1);
    // ← EFFET SPÉCIAL : Sacrifier autre carte
    drain->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::sacrifierAutreCarte(j, g);
    });
    cards.push_back(drain);
    
    // ════════════════════════════════════════════════════════
    // La Putréfaction (2 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* putrefaction = new CarteAction(2, "La Putréfaction", 3, NECROS);
    putrefaction->setDescription("Gain 4 combat. You may sacrifice a card in your hand or discard pile\nAlly: Gain 3 combat");
    putrefaction->setEffetPrincipal(0, 4, 0, 0);
    putrefaction->setEffetAllie(0, 3, 0, 0);
    // ← EFFET SPÉCIAL : Sacrifier autre carte
    putrefaction->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::sacrifierAutreCarte(j, g);
    });
    cards.push_back(putrefaction);
    
    // Tyrannor, le Dévoreur (1 exemplaire)
    CarteChampion* tyrannor = new CarteChampion(1, "Tyrannor, le Dévoreur", 8, NECROS, 6, true);
    tyrannor->setDescription("Expend: Gain 4 combat. You may sacrifice up to two cards in your hand and/or discard pile\nAlly: Draw a card");
    tyrannor->setEffetExpend(0, 4, 0, 0);
    tyrannor->setEffetAllie(0, 0, 0, 1);
    // TODO: Effet expend sacrifier jusqu'à 2 cartes
    cards.push_back(tyrannor);
    
    // ════════════════════════════════════════════════════════
    // Lys, l'Inapparent (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* lys = new CarteChampion(1, "Lys, l'Inapparent", 6, NECROS, 5, true);
    lys->setDescription("Expend: Gain 2 combat. You may sacrifice a card in your hand or discard pile. If you do, gain an additional 2 combat\nAlly: Draw a card");
    lys->setEffetExpend(0, 2, 0, 0);
    lys->setEffetAllie(0, 0, 0, 1);
    lys->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::lysTheUnseenExpend(j, g);
    });
    cards.push_back(lys);
    
    // ════════════════════════════════════════════════════════
    // Varrick, le Nécromancien (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* varrick = new CarteChampion(1, "Varrick, le Nécromancien", 5, NECROS, 3, false);
    varrick->setDescription("Expend: Take a champion from your discard pile and put it on top of your deck\nAlly: Draw a card");
    varrick->setEffetExpend(0, 0, 0, 0);
    varrick->setEffetAllie(0, 0, 0, 1);
    varrick->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::varrickNecromancerExpend(j, g);
    });
    cards.push_back(varrick);
    
    return cards;
}

std::vector<Carte*> CarteDB::getWildCards() {
    std::vector<Carte*> cards;
    
    // ════════════════════════════════════════════════════════
    // Broelyn, Tisseuse de Savoirs (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* broelyn = new CarteChampion(1, "Broelyn, Tisseuse de Savoirs", 4, WILD, 6, false);
    broelyn->setDescription("Expend: Gain 2 gold\nAlly: Target opponent discards a card");
    broelyn->setEffetExpend(2, 0, 0, 0);
    broelyn->setEffetSpecialAllie([](Joueur* j, Jeu* g) {
        EffetChampion::broelynLoreweaverAlly(j, g);
    });
    cards.push_back(broelyn);
    
    // ════════════════════════════════════════════════════════
    // Cron, le Berserker (1 exemplaire)
    // ════════════════════════════════════════════════════════
    CarteChampion* cron = new CarteChampion(1, "Cron, le Berserker", 6, WILD, 6, false);
    cron->setDescription("Expend: Gain 5 combat\nAlly: Draw a card");
    cron->setEffetExpend(0, 5, 0, 0);
    cron->setEffetAllie(0, 0, 0, 1); // Pioche 1 carte
    cards.push_back(cron);
    
    // Loup Terrifiant (1 exemplaire)
    CarteChampion* loup = new CarteChampion(1, "Loup Terrifiant", 5, WILD, 5, true);
    loup->setDescription("Expend: Gain 3 combat\nAlly: Gain 4 combat");
    loup->setEffetExpend(0, 3, 0, 0);
    loup->setEffetAllie(0, 4, 0, 0);
    cards.push_back(loup);
    
    // ════════════════════════════════════════════════════════
    // Malédiction Elfique (2 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* malediction = new CarteAction(2, "Malédiction Elfique", 3, WILD);
    malediction->setDescription("Gain 6 combat. Target opponent discards a card\nAlly: Gain 3 combat");
    malediction->setEffetPrincipal(0, 6, 0, 0);
    malediction->setEffetAllie(0, 3, 0, 0);
    // ← EFFET SPÉCIAL : Défausser carte adverse
    malediction->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::defausserCarteAdverse(j, g);
    });
    cards.push_back(malediction);
    
    // ════════════════════════════════════════════════════════
    // Don Elfique (3 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* don_elf = new CarteAction(3, "Don Elfique", 2, WILD);
    don_elf->setDescription("Gain 2 gold. You may draw a card. If you do, discard a card\nAlly: Gain 4 combat");
    don_elf->setEffetPrincipal(2, 0, 0, 0);
    don_elf->setEffetAllie(0, 4, 0, 0);
    // ← EFFET SPÉCIAL : Piocher puis défausser
    don_elf->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::piocherPuisDefausser(j, g);
    });
    cards.push_back(don_elf);
    
    // ════════════════════════════════════════════════════════
    // Grak, Géant de la Tempête (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* grak = new CarteChampion(1, "Grak, Géant de la Tempête", 8, WILD, 7, true);
    grak->setDescription("Expend: Gain 6 combat. You may draw a card. If you do, discard a card\nAlly: Draw a card, then discard a card");
    grak->setEffetExpend(0, 6, 0, 0);
    grak->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::grakStormGiantExpend(j, g);
    });
    grak->setEffetSpecialAllie([](Joueur* j, Jeu* g) {
        EffetChampion::grakStormGiantAlly(j, g);
    });
    cards.push_back(grak);
    
    // Don de la Nature (1 exemplaire)
    CarteAction* don_nature = new CarteAction(1, "Don de la Nature", 4, WILD);
    don_nature->setDescription("Gain 4 gold\nAlly: Target opponent discards a card\nSacrifice: Gain 4 combat");
    don_nature->setEffetPrincipal(4, 0, 0, 0);
    don_nature->setEffetSacrifice(0, 4, 0, 0);
    // ← EFFET SPÉCIAL ALLIÉ : Défausser carte adverse
    don_nature->setEffetSpecialAllie([](Joueur* j, Game* g) {
        EffetAction::defausserCarteAdverse(j, g);
    });
    cards.push_back(don_nature);
    
    // Grognard Orque (2 exemplaires)
    CarteChampion* grognard = new CarteChampion(2, "Grognard Orque", 3, WILD, 3, true);
    grognard->setDescription("Expend: Gain 2 combat\nAlly: Draw a card");
    grognard->setEffetExpend(0, 2, 0, 0);
    grognard->setEffetAllie(0, 0, 0, 1);
    cards.push_back(grognard);
    
    // ════════════════════════════════════════════════════════
    // Sauvagerie (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* sauvagerie = new CarteAction(1, "Sauvagerie", 6, WILD);
    sauvagerie->setDescription("Gain 6 combat. You may draw up to two cards, then discard that many cards");
    sauvagerie->setEffetPrincipal(0, 6, 0, 0);
    // ← EFFET SPÉCIAL : Piocher 0-2 puis défausser autant
    sauvagerie->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::piocherEtDefausserVariable(j, 2, g);
    });
    cards.push_back(sauvagerie);
    
    // ════════════════════════════════════════════════════════
    // Torgen Brise-Pierre (1 exemplaire) - CORRIGÉ
    // ════════════════════════════════════════════════════════
    CarteChampion* torgen = new CarteChampion(1, "Torgen Brise-Pierre", 7, WILD, 7, true);
    torgen->setDescription("Expend: Gain 4 combat. Target opponent discards a card");
    torgen->setEffetExpend(0, 4, 0, 0);
    torgen->setEffetSpecialExpend([](Joueur* j, Jeu* g) {
        EffetChampion::torgenRocksplitterExpend(j, g);
    });
    cards.push_back(torgen);
    
    // ════════════════════════════════════════════════════════
    // Étincelle (3 exemplaires) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* etincelle = new CarteAction(3, "Étincelle", 1, WILD);
    etincelle->setDescription("Gain 3 combat. Target opponent discards a card\nAlly: Gain 2 combat");
    etincelle->setEffetPrincipal(0, 3, 0, 0);
    etincelle->setEffetAllie(0, 2, 0, 0);
    // ← EFFET SPÉCIAL : Défausser carte adverse
    etincelle->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::defausserCarteAdverse(j, g);
    });
    cards.push_back(etincelle);
    
    // ════════════════════════════════════════════════════════
    // Forme de Loup (1 exemplaire) - EFFET SPÉCIAL
    // ════════════════════════════════════════════════════════
    CarteAction* forme = new CarteAction(1, "Forme de Loup", 5, WILD);
    forme->setDescription("Gain 8 combat. Target opponent discards a card\nSacrifice: Target opponent discards a card");
    forme->setEffetPrincipal(0, 8, 0, 0);
    // ← EFFET SPÉCIAL PRINCIPAL : Défausser carte adverse
    forme->setEffetSpecialPrincipal([](Joueur* j, Game* g) {
        EffetAction::defausserCarteAdverse(j, g);
    });
    // ← EFFET SPÉCIAL SACRIFICE : Défausser carte adverse
    forme->setEffetSpecialSacrifice([](Joueur* j, Game* g) {
        EffetAction::defausserCarteAdverse(j, g);
    });
    cards.push_back(forme);
    
    // Shamane des Loups (2 exemplaires)
    CarteChampion* shamane = new CarteChampion(2, "Shamane des Loups", 2, WILD, 4, false);
    shamane->setDescription("Expend: Gain 2 combat. +1 combat for each other Wild card you have in play");
    shamane->setEffetExpend(0, 2, 0, 0);
    // TODO: Effet expend bonus combat par Wild
    cards.push_back(shamane);
    
    return cards;
}

std::vector<Carte*> CarteDB::getAllMarketCards() {
    std::vector<Carte*> market;
    
    auto imperial = getImperialCards();
    auto guild = getGuildCards();
    auto necros = getNecrosCards();
    auto wild = getWildCards();
    
    market.insert(market.end(), imperial.begin(), imperial.end());
    market.insert(market.end(), guild.begin(), guild.end());
    market.insert(market.end(), necros.begin(), necros.end());
    market.insert(market.end(), wild.begin(), wild.end());
    
    return market;
}

void CarteDB::deleteCards(std::vector<Carte*>& cards) {
    for (auto card : cards) {
        delete card;
    }
    cards.clear();
}