/**
 * @file ChargeurCercle.h
 * @brief Maillon COR pour charger un Cercle.
 * @author Moham
 */

#ifndef CHARGEURCERCLE_H
#define CHARGEURCERCLE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "ChargeurFrome.h"
#include "Cercle.h"
#include "vecteur2D.h"

 /**
  * @class ChargeurCercle
  * @brief Analyseur de texte pour la création d'objets Cercle.
  */
class ChargeurCercle : public ChargeurForme {
public:
    /**
     * @brief Constructeur du maillon.
     * @param s Maillon suivant dans la chaîne.
     */
    ChargeurCercle(ChargeurForme* s) : ChargeurForme(s) {}

    /**
     * @brief Décode une ligne : "Cercle;couleur;(x,y);rayon".
     * @param ligne Texte à analyser.
     * @param flux Flux de données (non utilisé directement).
     * @return Forme* Instance de Cercle ou nullptr si échec.
     */
    Forme* charger(const std::string& ligne, std::ifstream& flux) override {
        if (ligne.find("Cercle") == 0) {
            try {
                std::stringstream ss(ligne);
                std::string item;
                std::vector<std::string> frags;
                while (std::getline(ss, item, ';')) frags.push_back(item);

                if (frags.size() < 4) return nullptr;

                // Extraction du format (x,y)
                std::stringstream ss_pt(frags[2]);
                double x, y;
                char c1, c2, c3;
                if (!(ss_pt >> c1 >> x >> c2 >> y >> c3)) return nullptr;

                double r = std::stod(frags[3]);

                return new Cercle(Vecteur2D(x, y), r, frags[1]);
            }
            catch (...) { return nullptr; }
        }
        return (_suivant != nullptr) ? _suivant->charger(ligne, flux) : nullptr;
    }
};

#endif