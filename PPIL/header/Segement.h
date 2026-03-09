/**
 * @file Segment.h
 * @brief Classe Segment : deux points dans le plan.
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include "Forme.h"
#include "VisiteurForme.h"
#include "vecteur2D.h"

 /**
  * @class Segment
  * @brief Un segment defini par deux extremites p1 et p2.
  */
class Segment : public Forme {
private:
    Vecteur2D _p1;
    Vecteur2D _p2;

public:
    Segment(const Vecteur2D& p1, const Vecteur2D& p2, const std::string& couleur)
        : Forme(couleur), _p1(p1), _p2(p2) {
    }

    virtual ~Segment() {}

    const Vecteur2D& getP1() const { return _p1; }
    const Vecteur2D& getP2() const { return _p2; }

    /** On deplace les deux extremites du meme vecteur. */
    void translation(const Vecteur2D& v) override {
        _p1 += v;
        _p2 += v;
    }

    /** Chaque point est repositionne par rapport au centre invariant. */
    void homothetie(const Vecteur2D& centre, double rapport) override {
        _p1 = centre + (_p1 - centre) * rapport;
        _p2 = centre + (_p2 - centre) * rapport;
    }

    /** Rotation des deux points autour du centre donne, en radians. */
    void rotation(const Vecteur2D& centre, double angle) override {
        auto rot = [&](const Vecteur2D& p) {
            double dx = p.x - centre.x;
            double dy = p.y - centre.y;
            double x = centre.x + dx * cos(angle) - dy * sin(angle);
            double y = centre.y + dx * sin(angle) + dy * cos(angle);
            return Vecteur2D(x, y);
        };
        _p1 = rot(_p1);
        _p2 = rot(_p2);
    }

    /** Un segment n'a pas de surface, donc aire = 0. */
    double calculerAire() const override { return 0.0; }

    void accepte(VisiteurForme* v) const override { v->visite(*this); }

    operator std::string() const override {
        return "Segment [" + (std::string)_p1 + ", " + (std::string)_p2 + "], " + _couleur;
    }
};

#endif