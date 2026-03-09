/**
 * @file VisiteurSauvegardeTexte.h
 * @brief Visiteur qui ecrit les formes dans un fichier texte.
 */

#ifndef VISITEUR_SAUVEGARDE_TEXTE_H
#define VISITEUR_SAUVEGARDE_TEXTE_H

#include "VisiteurForme.h"
#include <string>
#include <fstream>
#include <stdexcept>

/**
 * @class VisiteurSauvegardeTexte
 * @brief Ecrit chaque forme dans un fichier texte selon un format precis.
 *
 * Par exemple un cercle donne la ligne : "Cercle;red;(10,10);5"
 * Un groupe est encadre par "Groupe;Debut;couleur" et "Groupe;Fin".
 */
class VisiteurSauvegardeTexte : public VisiteurForme {
private:
    std::string _nomFichier;
    std::ofstream _flux;

public:
    VisiteurSauvegardeTexte(const std::string& nomFichier);
    ~VisiteurSauvegardeTexte();

    void visite(const Cercle& cercle) override;
    void visite(const Segment& segment) override;
    void visite(const Polygone& polygone) override;
    void visite(const Groupe& groupe) override;
};

#endif