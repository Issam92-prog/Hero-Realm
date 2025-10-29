#include "Jeu.hpp"
#include <iostream>
#include <exception>


int main() {
    try {
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                                                        ║" << std::endl;
        std::cout << "║            ⚔️  HERO REALMS ⚔️                         ║" << std::endl;
        std::cout << "║                                                        ║" << std::endl;
        std::cout << "║              Jeu de Cartes de Combat                   ║" << std::endl;
        std::cout << "║                                                        ║" << std::endl;
        std::cout << "║              Développé par: Issam et Alexandre         ║" << std::endl;
        std::cout << "║              Date: 2025-10-29                          ║" << std::endl;
        std::cout << "║                                                        ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

        // Créer et lancer le jeu
        Jeu jeu;
        jeu.lancer();

        std::cout << "\n👋 Merci d'avoir joué à Hero Realms !\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n❌ ERREUR CRITIQUE:" << std::endl;
        std::cerr << "   " << e.what() << std::endl;
        std::cerr << "\nLe programme va se terminer." << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ ERREUR INCONNUE:" << std::endl;
        std::cerr << "   Une erreur inattendue s'est produite." << std::endl;
        std::cerr << "\nLe programme va se terminer." << std::endl;
        return 2;
    }

    return 0;
}