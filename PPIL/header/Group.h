/**
 * @file Groupe.h
 * @brief Classe Groupe : forme composee qui contient d'autres formes (pattern Composite).
 */

#ifndef GROUPE_H
#define GROUPE_H

#include "Forme.h"
#include "VisiteurForme.h"
#include <vector>
#include <string>

/**
 * @class Groupe
 * @brief Regroupe plusieurs formes en une seule entite.
 *
 * Quand on applique une transformation au groupe,
 * elle est propagee a toutes les formes qu'il contient.
 * Le groupe est responsable de la memoire de ses enfants.
 */
class Groupe : public Forme {
private:
    std::vector<Forme*> _formes;

public:
    Groupe(const std::string& couleur) : Forme(couleur) {}

    // On interdit la copie pour eviter les double-delete
    Groupe(const Groupe&) = delete;
    Groupe& operator=(const Groupe&) = delete;

    /** Le destructeur libere toutes les formes contenues. */
    virtual ~Groupe() {
        for (Forme* f : _formes) {
            delete f;
        }
        _formes.clear();
    }

    void ajouter(Forme* f) {
        if (f) _formes.push_back(f);
    }

    /** Chaque transformation est simplement appliquee a chaque enfant. */
    void translation(const Vecteur2D& v) override {
        for (Forme* f : _formes) f->translation(v);
    }

    void homothetie(const Vecteur2D& centre, double rapport) override {
        for (Forme* f : _formes) f->homothetie(centre, rapport);
    }

    void rotation(const Vecteur2D& centre, double angle) override {
        for (Forme* f : _formes) f->rotation(centre, angle);
    }

    /** L'aire d'un groupe = somme des aires de ses formes (elles sont disjointes). */
    double calculerAire() const override {
        double total = 0;
        for (const Forme* f : _formes) total += f->calculerAire();
        return total;
    }

    void accepte(VisiteurForme* v) const override {
        v->visite(*this);
    }

    const std::vector<Forme*>& getFormes() const { return _formes; }

    operator std::string() const override {
        std::string s = "Groupe " + _couleur + " { ";
        for (const auto& f : _formes) s += (std::string)(*f) + " ; ";
        s += "}";
        return s;
    }
};

#endif
