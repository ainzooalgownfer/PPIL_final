/**
 * @file Forme.h
 * @brief Classe de base abstraite pour toutes les formes du projet.
 */

#ifndef FORME_H
#define FORME_H

#include <string>
#include <vector>
#include "Vecteur2D.h"

class VisiteurForme;

/**
 * @class Forme
 * @brief Classe mere dont heritent Cercle, Segment, Polygone et Groupe.
 *
 * Elle definit les methodes que toute forme doit avoir :
 * les 3 transformations, le calcul d'aire, la conversion en string
 * et le mecanisme du Visiteur.
 */
class Forme {
protected:
    std::string _couleur;

public:
    // Les 6 couleurs autorisees par le sujet
    static const std::string BLACK;
    static const std::string BLUE;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string CYAN;

    Forme(const std::string& couleur = "black") : _couleur(couleur) {}

    virtual ~Forme() {}

    virtual const std::string& getCouleur() const { return _couleur; }
    virtual void setCouleur(const std::string& c) { _couleur = c; }

    // Les 3 transformations geometriques (virtuelles pures)
    virtual void translation(const Vecteur2D& vecteur) = 0;
    virtual void homothetie(const Vecteur2D& centre, double rapport) = 0;
    virtual void rotation(const Vecteur2D& centre, double angleRadians) = 0;

    virtual double calculerAire() const = 0;
    virtual operator std::string() const = 0;

    // Pour le pattern Visiteur : chaque forme sait se faire visiter
    virtual void accepte(VisiteurForme* visiteur) const = 0;
};

#endif