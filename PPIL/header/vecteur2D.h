/**
 * @file Vecteur2D.h
 * @brief Classe Vecteur2D - represente un point ou un vecteur 2D.
 */

#ifndef VECTEUR_2D_H
#define VECTEUR_2D_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio> // Pour sscanf

 /**
  * @class Vecteur2D
 * @brief Un couple (x, y) de coordonnees reelles.
 *
 * Sert a la fois de point et de vecteur dans le plan.
 * On s'en sert partout dans les formes geometriques.
 */
class Vecteur2D {
public:
    double x, y;

    /**
    /** Constructeur avec valeurs par defaut a 0. */
    explicit Vecteur2D(const double& x = 0, const double& y = 0) : x(x), y(y) {}

    /**
     * Constructeur depuis une chaine "(x,y)".
     * Utile quand on recharge des formes depuis un fichier texte.
     */
    Vecteur2D(const char* s) {
        if (sscanf(s, "(%lf,%lf)", &x, &y) != 2) {
            x = 0; y = 0;
        }
    }

    /** Renvoie le vecteur sous forme de chaine "(x,y)". */
    operator std::string() const {
        std::ostringstream os;
        os << "(" << x << "," << y << ")";
        return os.str();
    }

    // -- Operations sur les vecteurs --

    const Vecteur2D operator+(const Vecteur2D& u) const {
        return Vecteur2D(x + u.x, y + u.y);
    }

    const Vecteur2D operator*(const double& a) const {
        return Vecteur2D(x * a, y * a);
    }

    const Vecteur2D& operator+=(const Vecteur2D& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    /** Soustraction : on reutilise l'addition avec l'oppose. */
    inline const Vecteur2D operator-(const Vecteur2D& u) const {
        return *this + (-u);
    }

    /** Oppose du vecteur (-x, -y). */
    const Vecteur2D operator-() const {
        return Vecteur2D(-x, -y);
    }

    /**
     * Determinant de deux vecteurs : x*v.y - y*v.x
     * On en a besoin pour calculer l'aire des polygones (formule du lacet).
     */
    double determinant(const Vecteur2D& v) const {
        return x * v.y - y * v.x;
    }
};

/** Pour ecrire a * vecteur au lieu de vecteur * a. */
inline Vecteur2D operator*(const double a, const Vecteur2D& v) {
    return v * a;
}

/** Pour pouvoir faire cout << monVecteur. */
inline std::ostream& operator<<(std::ostream& os, const Vecteur2D& u) {
    os << (std::string)u;
    return os;
}

#endif