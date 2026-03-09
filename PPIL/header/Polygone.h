/**
 * @file Polygone.h
 * @brief Classe Polygone : liste de sommets formant un polygone ferme.
 */

#ifndef POLYGONE_H
#define POLYGONE_H

#include "Forme.h"
#include "VisiteurForme.h"
#include <vector>
#include <cmath>

 /**
  * @class Polygone
  * @brief Représente un polygone quelconque fermé.
  *  Gère une liste de sommets et implémente les algorithmes géométriques vectoriels.
  */
class Polygone : public Forme {
protected:
    std::vector<Vecteur2D> _sommets;

public:
    Polygone(const std::vector<Vecteur2D>& sommets, const std::string& couleur)
        : Forme(couleur), _sommets(sommets) {
    }

    virtual ~Polygone() {}

    const std::vector<Vecteur2D>& getSommets() const { return _sommets; }

    /** On ajoute le vecteur v a chaque sommet. */
    void translation(const Vecteur2D& v) override {
        for (auto& s : _sommets) s += v;
    }

    /** Chaque sommet est eloigne ou rapproche du centre selon le rapport. */
    void homothetie(const Vecteur2D& centre, double rapport) override {
        for (auto& s : _sommets) s = centre + (s - centre) * rapport;
    }

    /** On applique la formule de rotation a chaque sommet. */
    void rotation(const Vecteur2D& centre, double angle) override {
        for (auto& s : _sommets) {
            double dx = s.x - centre.x;
            double dy = s.y - centre.y;
            double x = centre.x + dx * cos(angle) - dy * sin(angle);
            double y = centre.y + dx * sin(angle) + dy * cos(angle);
            s = Vecteur2D(x, y);
        }
    }

    /**
     * Aire calculee avec la formule du lacet (Shoelace) :
     * on somme les determinants entre chaque sommet et le suivant,
     * puis on divise par 2.
     */
    double calculerAire() const override {
        double aire = 0;
        size_t n = _sommets.size();
        if (n < 3) return 0;

        for (size_t i = 0; i < n; ++i) {
            aire += _sommets[i].determinant(_sommets[(i + 1) % n]);
        }
        return std::abs(aire) / 2.0;
    }

    void accepte(VisiteurForme* v) const override { v->visite(*this); }

    operator std::string() const override {
        std::string s = "Polygone [";
        for (const auto& v : _sommets) s += (std::string)v + " ";
        return s + "], " + _couleur;
    }
};

#endif