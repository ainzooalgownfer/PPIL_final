/**
 * @file ChargeurGroupe.h
 * @brief Maillon COR pour charger un Groupe (Composite).
 * @author Moham
 */

#ifndef CHARGEURGROUPE_H
#define CHARGEURGROUPE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "ChargeurFrome.h"
#include "Group.h"

 /**
  * @class ChargeurGroupe
  * @brief Gestionnaire de lecture récursive pour les groupes de formes.
  */
class ChargeurGroupe : public ChargeurForme {
private:
    ChargeurForme* _teteDeChaine; ///< Pointeur vers le début de la COR pour la récursivité.

public:
    /**
     * @brief Constructeur.
     * @param s Prochain maillon.
     * @param tete Premier maillon de la chaîne globale.
     */
    ChargeurGroupe(ChargeurForme* s, ChargeurForme* tete)
        : ChargeurForme(s), _teteDeChaine(tete) {
    }

    /**
     * @brief Définit la tête de la chaîne pour la récursivité.
     * @param tete Le premier maillon de la COR.
     */
    void setTete(ChargeurForme* tete) {
        _teteDeChaine = tete;
    }

    /**
     * @brief Charge un groupe et ses enfants (lecture multi-lignes).
     * @param ligne Ligne actuelle ("Groupe;Debut").
     * @param flux Flux de lecture ouvert.
     * @return Forme* Objet Groupe ou nullptr.
     */
    Forme* charger(const std::string& ligne, std::ifstream& flux) override {
        if (ligne.find("Groupe;Debut") == 0) {

            // Extraction de la couleur
            size_t lastSemi = ligne.find_last_of(';');
            std::string couleur = (lastSemi != std::string::npos) ? ligne.substr(lastSemi + 1) : "noir";

            Groupe* g = new Groupe(couleur);
            std::string sousLigne;

            // Lecture jusqu'à la balise de fin
            while (std::getline(flux, sousLigne) && sousLigne.find("Groupe;Fin") == std::string::npos) {
                if (sousLigne.empty()) continue;

                // Sécurité : On vérifie que la tête n'est pas nulle avant l'appel
                if (_teteDeChaine) {
                    Forme* enfant = _teteDeChaine->charger(sousLigne, flux);
                    if (enfant) g->ajouter(enfant);
                }
            }
            return g;
        }

        // Délégation au maillon suivant
        return (_suivant) ? _suivant->charger(ligne, flux) : nullptr;
    }
};

#endif