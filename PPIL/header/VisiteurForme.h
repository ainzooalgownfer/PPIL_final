/**
 * @file VisiteurForme.h
 * @brief Interface abstraite du pattern Visiteur.
 */

#ifndef VISITEUR_FORME_H
#define VISITEUR_FORME_H

// Forward declarations: telling the compiler these classes exist
class Cercle;
class Segment;
class Polygone;
class Groupe;

/**
 * @class VisiteurForme
 * @brief Interface que doivent implementer tous les visiteurs.
 *
 * On a un visiteur pour la sauvegarde fichier (VisiteurSauvegardeTexte)
 * et un pour le dessin reseau (VisiteurDessin).
 * Ca permet d'ajouter des operations sans toucher aux classes de formes.
 */
class VisiteurForme {
public:
    virtual ~VisiteurForme() {}
    virtual void visite(const Cercle& cercle) = 0;
    virtual void visite(const Segment& segment) = 0;
    virtual void visite(const Polygone& polygone) = 0;
    virtual void visite(const Groupe& groupe) = 0;
};

#endif