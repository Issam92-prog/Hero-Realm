#include "Joueur/Joueur.hpp"
#include <utility>  // std::move

using namespace std;

Joueur::Joueur(Id id, string nom, int pv_initial)
    : id_(id), nom_(move(nom)), pv_(pv_initial) {}

Joueur::Id Joueur::id() const { return id_; }

const string& Joueur::nom() const { return nom_; }

int Joueur::pv() const { return pv_; }

void Joueur::soigner(int v) {
    if (v > 0) pv_ += v;
}

void Joueur::subirDegats(int v) {
    if (v > 0) pv_ = (pv_ - v < 0 ? 0 : pv_ - v);
}

bool Joueur::estMort() const {
    return pv_ <= 0;
}

void Joueur::debutDeTour() {
    // logique future
}

void Joueur::finDeTour() {
    // logique future
}
