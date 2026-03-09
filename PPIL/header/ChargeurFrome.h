/**
 * @file ChargeurForme.h
 * @brief Classe de base pour la Chaîne de Responsabilité (COR).
 * @author Moham
 */

#ifndef CHARGEURFORME_H
#define CHARGEURFORME_H

#include <string>
#include <fstream>
#include "Forme.h"

 /**
  * @class ChargeurForme
  * @brief Interface abstraite pour les maillons de chargement de formes.
  */
class ChargeurForme {
protected:
    /** @brief Pointeur vers le maillon suivant dans la chaîne. */
    ChargeurForme* _suivant;

public:
    /**
     * @brief Constructeur du maillon.
     * @param s Maillon suivant (nullptr si c'est le dernier).
     */
    ChargeurForme(ChargeurForme* s) : _suivant(s) {}

    /** @brief Destructeur virtuel. */
    virtual ~ChargeurForme() {}

    /**
     * @brief Méthode virtuelle pure à implémenter pour chaque type de forme.
     * @param ligne Ligne de texte à analyser.
     * @param flux Flux du fichier (pour les lectures multi-lignes comme les Groupes).
     * @return Forme* Pointeur vers la forme créée ou nullptr.
     */
    virtual Forme* charger(const std::string& ligne, std::ifstream& flux) = 0;
};

#endif