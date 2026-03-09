
/**
 * @file VisiteurDessin.h
 * @brief Visiteur qui envoie les formes au serveur Java pour le dessin.
 */

#ifndef VISITEUR_DESSIN_H
#define VISITEUR_DESSIN_H

#include "VisiteurForme.h"
#include "Connexion_m.h"
#include "Cercle.h"
#include "Segement.h"
#include "Polygone.h"
#include "Group.h"
#include <string>
#include <sstream>

/**
 * @class VisiteurDessin
 * @brief Construit les messages texte et les envoie au serveur via TCP/IP.
 *
 * Le format des messages est le meme que pour la sauvegarde fichier,
 * comme ca le serveur Java peut parser les donnees facilement.
 * Quand on dessine un groupe, sa couleur remplace celle de chaque enfant
 * (c'est ce que demande le sujet).
 */
class VisiteurDessin : public VisiteurForme {
private:
    std::string _couleurGroupe;  // couleur du groupe parent en cours, vide sinon

    void envoyer(const std::string& message) {
        ConnexionManager::getInstance()->envoyer(message);
    }

public:
    VisiteurDessin() : _couleurGroupe("") {}

    // On utilise la couleur du groupe si on est dans un groupe, sinon la couleur propre
    void visite(const Cercle& cercle) override {
        std::string couleur = _couleurGroupe.empty() ? cercle.getCouleur() : _couleurGroupe;

        std::ostringstream msg;
        msg << "Cercle;" << couleur << ";"
            << (std::string)cercle.getCentre() << ";"
            << cercle.getRayon();

        envoyer(msg.str());
    }

    void visite(const Segment& segment) override {
        std::string couleur = _couleurGroupe.empty() ? segment.getCouleur() : _couleurGroupe;

        std::ostringstream msg;
        msg << "Segment;" << couleur << ";"
            << (std::string)segment.getP1() << ";"
            << (std::string)segment.getP2();

        envoyer(msg.str());
    }

    void visite(const Polygone& polygone) override {
        std::string couleur = _couleurGroupe.empty() ? polygone.getCouleur() : _couleurGroupe;

        std::ostringstream msg;
        msg << "Polygone;" << couleur;
        for (const auto& s : polygone.getSommets()) {
            msg << ";" << (std::string)s;
        }

        envoyer(msg.str());
    }

    /**
     * Pour un groupe : on applique sa couleur a tous les enfants.
     * On sauvegarde l'ancienne couleur au cas ou il y a des groupes imbriques.
     */
    void visite(const Groupe& groupe) override {
        std::string ancienneCouleur = _couleurGroupe;
        _couleurGroupe = groupe.getCouleur();

        for (const Forme* f : groupe.getFormes()) {
            f->accepte(this);
        }

        _couleurGroupe = ancienneCouleur;
    }
};

#endif