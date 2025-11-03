#include "Jeu.hpp"
#include <iostream>
#include <exception>


int main() {
    try {
        // Créer et lancer le jeu
        Jeu jeu;
        jeu.lancer();



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