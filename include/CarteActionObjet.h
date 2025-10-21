#pragma once
#include "Carte.h"

class CarteActionObjet : public Carte {
public:
    CarteActionObjet(const std::string& nom = "Objet", const std::string& type = "", const std::string& faction = "", int cout = 0)
    : Carte(nom, cout), m_type(type), m_faction(faction) {}
    ~CarteActionObjet() override {}

    const std::string& getType() const { return m_type; }
    const std::string& getFaction() const { return m_faction; }

private:
    std::string m_type;
    std::string m_faction;
};
