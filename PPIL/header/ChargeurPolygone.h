/**
 * @file ChargeurPolygone.h
 * @brief Maillon COR pour charger un Polygone.
 * @author Moham
 */

#ifndef CHARGEURPOLYGONE_H
#define CHARGEURPOLYGONE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "ChargeurFrome.h"
#include "Polygone.h"
#include "vecteur2D.h"

 /**
  * @class ChargeurPolygone
  * @brief Analyseur pour la création d'objets Polygone à partir de sommets.
  */
class ChargeurPolygone : public ChargeurForme {
public:
    /**
     * @brief Constructeur du maillon.
     * @param s Maillon suivant dans la chaîne.
     */
    ChargeurPolygone(ChargeurForme* s) : ChargeurForme(s) {}

    /**
     * @brief Décode une ligne : "Polygone;couleur;(x1,y1);(x2,y2);...".
     * @param ligne Texte à analyser.
     * @param flux Flux de données.
     * @return Forme* Instance de Polygone ou nullptr si échec.
     */
    Forme* charger(const std::string& ligne, std::ifstream& flux) override {
        if (ligne.find("Polygone") == 0) {
            try {
                std::stringstream ss(ligne);
                std::string item;
                std::vector<std::string> frags;

                while (std::getline(ss, item, ';')) {
                    frags.push_back(item);
                }

                if (frags.size() < 2) return nullptr;

                std::string couleur = frags[1];
                std::vector<Vecteur2D> sommets;

                for (size_t i = 2; i < frags.size(); ++i) {
                    if (frags[i].empty()) continue;

                    std::stringstream ss_pt(frags[i]);
                    double x, y;
                    char c1, c2, c3;

                    // Extraction du format (x,y)
                    if (ss_pt >> c1 >> x >> c2 >> y >> c3) {
                        sommets.push_back(Vecteur2D(x, y));
                    }
                }

                if (sommets.empty()) return nullptr;

                return new Polygone(sommets, couleur);
            }
            catch (...) { return nullptr; }
        }

        return (_suivant != nullptr) ? _suivant->charger(ligne, flux) : nullptr;
    }
};

#endif