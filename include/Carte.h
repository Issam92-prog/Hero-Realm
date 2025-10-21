#pragma once
#include <string>

class Carte {
public:
    Carte(const std::string& nom = "Carte", int cout = 0) : m_nom(nom), m_cout(cout) {}
    virtual ~Carte() {}

    const std::string& getNom() const { return m_nom; }
    int getCout() const { return m_cout; }

private:
    std::string m_nom;
    int m_cout;
};
