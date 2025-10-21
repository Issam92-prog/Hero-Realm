#include "zone/marche.hpp"
#include "Joueur/Joueur.hpp"
#include "zone/defausse.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// =====================
// CONSTRUCTEUR / DESTRUCTEUR
// =====================

// ...existing code...
Marche::Marche() : m_defausse(nullptr) {
    // Assure qu'il y a 5 emplacements visibles
    m_cartesVisibles.resize(5);

    // Création des gemmes de feu (si elles sont statiques)
    for (int i = 0; i < 3; ++i) {
        m_gemmesDeFeu.push_back(new CarteActionObjet("Gemme de feu", "Objet", "Neutre", 2, /*autres paramètres*/));
    }

    // Initialise la pioche et remplit les cartes visibles
    initialiser();
}
// ...existing code...
Marche::~Marche() {
    for (auto carte : m_piocheDuMarche)
        delete carte;

    for (auto carte : m_cartesSacrifiees)
        delete carte;

    for (auto gemme : m_gemmesDeFeu)
        delete gemme;

    // Supprime les cartes encore présentes dans les emplacements visibles
    for (auto carte : m_cartesVisibles) {
        if (carte)
            delete carte;
    }
}
// ...existing code...
void Marche::initialiser() {
    // TODO : remplir la pioche du marché avec les cartes disponibles dans le jeu

    // Mélange aléatoire de la pioche
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_piocheDuMarche.begin(), m_piocheDuMarche.end(), g);

    // Tire les 5 premières cartes visibles (m_cartesVisibles est dimensionné)
    for (int i = 0; i < static_cast<int>(m_cartesVisibles.size()) && !m_piocheDuMarche.empty(); ++i) {
        m_cartesVisibles[i] = m_piocheDuMarche.back();
        m_piocheDuMarche.pop_back();
    }
}
// ...existing code...

// =====================
// ACHATS
// =====================

Carte* Marche::acheterCarte(int index, Joueur* joueur) {
    if (index < 0 || index >= static_cast<int>(m_cartesVisibles.size()))
        return nullptr;

    Carte* carte = m_cartesVisibles[index];
    if (!carte)
        return nullptr;

    // Vérifie que le joueur peut acheter la carte
    if (!joueur->peutAcheter(carte)) {
        std::cout << "Vous n'avez pas assez d'or pour acheter cette carte !" << std::endl;
        return nullptr;
    }

    joueur->payer(carte->getCout());
    joueur->ajouterADefausse(carte); // La carte va dans la défausse du joueur
    m_cartesVisibles[index] = nullptr;

    // On remplit la place vide
    remplir();

    return carte;
}

CarteActionObjet* Marche::acheterGemmes(Joueur* joueur) {
    if (m_gemmesDeFeu.empty()) {
        std::cout << "Plus de gemmes disponibles !" << std::endl;
        return nullptr;
    }

    CarteActionObjet* gemme = m_gemmesDeFeu.back();

    if (!joueur->peutAcheter(gemme)) {
        std::cout << "Pas assez d'or pour acheter une gemme !" << std::endl;
        return nullptr;
    }

    joueur->payer(gemme->getCout());
    joueur->ajouterADefausse(gemme);
    m_gemmesDeFeu.pop_back();

    return gemme;
}

// =====================
// REMPLISSAGE / RECYCLAGE
// =====================

void Marche::remplir() {
    for (auto& slot : m_cartesVisibles) {
        if (slot == nullptr && !m_piocheDuMarche.empty()) {
            slot = m_piocheDuMarche.back();
            m_piocheDuMarche.pop_back();
        }
    }
}

void Marche::recyclerDefausse() {
    if (!m_defausse) return;

    auto cartes = m_defausse->recupererCartes(); // à implémenter côté Defausse
    m_piocheDuMarche.insert(m_piocheDuMarche.end(), cartes.begin(), cartes.end());

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_piocheDuMarche.begin(), m_piocheDuMarche.end(), g);
}

// =====================
// SACRIFICE
// =====================

void Marche::sacrifierCarte(Carte* carte) {
    if (!carte) return;
    m_cartesSacrifiees.push_back(carte);
    std::cout << carte->getNom() << " a été sacrifiée !" << std::endl;
}

// =====================
// AFFICHAGE
// =====================

void Marche::afficher() const {
    std::cout << "===== Marché =====" << std::endl;
    for (size_t i = 0; i < m_cartesVisibles.size(); ++i) {
        if (m_cartesVisibles[i])
            std::cout << i + 1 << " - " << m_cartesVisibles[i]->getNom()
                      << " (Coût : " << m_cartesVisibles[i]->getCout() << ")" << std::endl;
        else
            std::cout << i + 1 << " - [vide]" << std::endl;
    }
    std::cout << "Gemmes disponibles : " << m_gemmesDeFeu.size() << std::endl;
}
