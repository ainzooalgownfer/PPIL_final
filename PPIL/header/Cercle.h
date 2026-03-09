/**
 * @file Cercle.h
 * @brief Classe Cercle : centre + rayon.
 */

#ifndef CERCLE_H
#define CERCLE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Forme.h"
#include "VisiteurForme.h"
#include <stdexcept>
#include <cmath>

/**
 * @class Cercle
 * @brief Un cercle defini par son centre (Vecteur2D) et son rayon.
 */
class Cercle : public Forme {
private:
    Vecteur2D _centre;
    double _rayon;

public:
    /**
     * Le rayon doit etre > 0, sinon on leve une exception.
     */
    Cercle(const Vecteur2D& centre, double rayon, const std::string& couleur)
        : Forme(couleur), _centre(centre), _rayon(rayon) {
        if (rayon <= 0) {
            throw std::invalid_argument("Le rayon doit etre strictement positif");
        }
    }

    virtual ~Cercle() {}

    const Vecteur2D& getCentre() const { return _centre; }
    double getRayon() const { return _rayon; }

    /** On deplace juste le centre. */
    void translation(const Vecteur2D& v) override {
        _centre += v;
    }

    /** Le centre bouge par rapport au point invariant, et le rayon est multiplie par |rapport|. */
    void homothetie(const Vecteur2D& centre, double rapport) override {
        _centre = centre + (_centre - centre) * rapport;
        _rayon *= std::abs(rapport);
    }

    /** On fait tourner le centre autour du point donne, le rayon ne change pas. */
    void rotation(const Vecteur2D& centre, double angle) override {
        double dx = _centre.x - centre.x;
        double dy = _centre.y - centre.y;
        double x = centre.x + dx * cos(angle) - dy * sin(angle);
        double y = centre.y + dx * sin(angle) + dy * cos(angle);
        _centre = Vecteur2D(x, y);
    }

    /** Aire = pi * r^2. */
    double calculerAire() const override {
        return M_PI * _rayon * _rayon;
    }

    void accepte(VisiteurForme* v) const override {
        v->visite(*this);
    }

    operator std::string() const override {
        return "Cercle [C:" + (std::string)_centre + ", R:" + std::to_string(_rayon) + "], " + _couleur;
    }
};

#endif