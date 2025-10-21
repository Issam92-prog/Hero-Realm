#pragma once
#include <string>
#include <iostream>

class Joueur;  // Forward declaration

class Carte {
public:
    Carte(const std::string& nom, int orValeur, int combatValeur, int cout = 0)
        : nom_(nom), or_(orValeur), combat_(combatValeur), cout_(cout) {}
    
    virtual ~Carte() = default;

    // Accesseurs
    const std::string& nom() const { return nom_; }
    int orValeur() const { return or_; }
    int combatValeur() const { return combat_; }
    int cout() const { return cout_; }

    // Jouer la carte
    virtual void jouer(Joueur* joueur);

    // Affichage
    virtual void afficher(std::ostream& out = std::cout) const {
        out << nom_;
        if (or_ > 0 || combat_ > 0) {
            out << " (+";
            if (or_ > 0) out << or_ << "💰";  // symbole pièce pour l'or
            if (or_ > 0 && combat_ > 0) out << ", ";
            if (combat_ > 0) out << combat_ << "⚔️";  // symbole épée pour le combat
            out << ")";
        }
        if (cout_ > 0) out << " [Coût:" << cout_ << "]";
    }

private:
    std::string nom_;
    int or_;
    int combat_;
    int cout_;  // Coût d'achat de la carte
};

// Surcharge de l'opérateur << pour l'affichage
inline std::ostream& operator<<(std::ostream& out, const Carte& carte) {
    carte.afficher(out);
    return out;
}
