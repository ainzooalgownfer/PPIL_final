/**
 * @file ChargeurSegment.h
 * @brief Maillon de la COR pour charger un Segment.
 * @author Moham
 */

#ifndef CHARGEURSEGMENT_H
#define CHARGEURSEGMENT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "ChargeurFrome.h"
#include "Segement.h"
#include "vecteur2D.h"

 /**
  * @class ChargeurSegment
  * @brief Analyseur pour la création d'objets Segment (deux points).
  */
class ChargeurSegment : public ChargeurForme {
public:
    /**
     * @brief Constructeur du maillon.
     * @param s Maillon suivant dans la chaîne.
     */
    ChargeurSegment(ChargeurForme* s) : ChargeurForme(s) {}

    /**
     * @brief Décode une ligne : "Segment;couleur;(x1,y1);(x2,y2)".
     * @param ligne Texte à analyser.
     * @param flux Flux de données.
     * @return Forme* Instance de Segment ou nullptr si échec.
     */
    Forme* charger(const std::string& ligne, std::ifstream& flux) override {
        if (ligne.find("Segment") == 0) {
            try {
                std::stringstream ss(ligne);
                std::string item;
                std::vector<std::string> frags;
                while (std::getline(ss, item, ';')) frags.push_back(item);

                if (frags.size() < 4) return nullptr;

                /**
                 * @brief Lambda interne pour extraire un Vecteur2D depuis "(x,y)".
                 */
                auto parsePoint = [](const std::string& s) {
                    std::stringstream ss_pt(s);
                    double x, y; char c;
                    if (ss_pt >> c >> x >> c >> y >> c) return Vecteur2D(x, y);
                    return Vecteur2D(0, 0);
                    };

                Vecteur2D p1 = parsePoint(frags[2]);
                Vecteur2D p2 = parsePoint(frags[3]);

                return new Segment(p1, p2, frags[1]);
            }
            catch (...) { return nullptr; }
        }
        return (_suivant != nullptr) ? _suivant->charger(ligne, flux) : nullptr;
    }
};

#endif