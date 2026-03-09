/**
 * @file VisiteurSauvegardeTexte.cpp
 * @brief Implementation de la sauvegarde des formes en fichier texte.
 */

#include "../header/VisiteurSauvegardeTexte.h"
#include "../header/Cercle.h"
#include "../header/Segement.h" 
#include "../header/Polygone.h"
#include "../header/Group.h"

 /**
  * @brief Constructeur : Ouvre le fichier en mode écriture seule (trunc).
  */
VisiteurSauvegardeTexte::VisiteurSauvegardeTexte(const std::string& nomFichier)
    : _nomFichier(nomFichier) {

    _flux.open(_nomFichier, std::ios::out | std::ios::trunc);

    if (!_flux.is_open()) {
        throw std::runtime_error("Erreur : Impossible de creer le fichier " + nomFichier);
    }

    // Force le vidage du buffer apres chaque ecriture
    _flux << std::unitbuf;
}

VisiteurSauvegardeTexte::~VisiteurSauvegardeTexte() {
    if (_flux.is_open()) {
        _flux.close();
    }
}

// Format : Cercle;couleur;(cx,cy);rayon
void VisiteurSauvegardeTexte::visite(const Cercle& cercle) {
    _flux << "Cercle;" << cercle.getCouleur() << ";"
        << (std::string)cercle.getCentre() << ";"
        << cercle.getRayon() << std::endl;
}

// Format : Segment;couleur;(x1,y1);(x2,y2)
void VisiteurSauvegardeTexte::visite(const Segment& segment) {
    _flux << "Segment;" << segment.getCouleur() << ";"
        << (std::string)segment.getP1() << ";"
        << (std::string)segment.getP2() << std::endl;
}

// Format : Polygone;couleur;(x1,y1);(x2,y2);...
void VisiteurSauvegardeTexte::visite(const Polygone& polygone) {
    _flux << "Polygone;" << polygone.getCouleur();
    for (const auto& s : polygone.getSommets()) {
        _flux << ";" << (std::string)s;
    }
    _flux << std::endl;
}

// Un groupe est encadre par des balises Debut/Fin
// Les formes a l'interieur sont ecrites recursivement
void VisiteurSauvegardeTexte::visite(const Groupe& groupe) {
    _flux << "Groupe;Debut;" << groupe.getCouleur() << std::endl;

    for (const Forme* f : groupe.getFormes()) {
        f->accepte(this);
    }

    _flux << "Groupe;Fin" << std::endl;
}