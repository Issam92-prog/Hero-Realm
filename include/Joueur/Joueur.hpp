#pragma once
#include <string>
#include <cstdint>

using namespace std;

class Joueur {
public:
    using Id = uint32_t;

    Joueur(Id id, string nom, int pv_initial = 50);

    // Identité
    Id id() const;
    const string& nom() const;

    // Points de vie
    int  pv() const;
    void soigner(int v);
    void subirDegats(int v);
    bool estMort() const;

    // Cycle de tour
    void debutDeTour();
    void finDeTour();

private:
    Id      id_;
    string  nom_;
    int     pv_;
};
