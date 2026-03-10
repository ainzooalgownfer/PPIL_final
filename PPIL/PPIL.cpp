/**
 * @file main.cpp
 * @brief Soutenance Finale : Dessin, Transformations Dynamiques et Persistence.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "header/Vecteur2D.h"
#include "header/Cercle.h"
#include "header/Segement.h"
#include "header/Polygone.h"
#include "header/Group.h"
#include "header/VisiteurDessin.h"
#include "header/VisiteurSauvegardeTexte.h"
#include "header/ChargeurCercle.h"
#include "header/ChargeurSegment.h"
#include "header/ChargeurPolygone.h"
#include "header/ChargeurGroup.h"
#include "header/Connexion_m.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

void afficherMenu() {
    cout << "\n========== PANNEAU DE CONTROLE PPIL ==========" << endl;
    cout << "1. DESSINER : Envoyer la scene actuelle a Java" << endl;
    cout << "2. TRANSLATION : Deplacer (+50, +50)" << endl;
    cout << "3. ROTATION : Entrer un angle (Degres)" << endl;
    cout << "4. HOMOTHETIE : Entrer un rapport (Ratio)" << endl;
    cout << "5. SAUVEGARDER : Ecrire l'etat actuel dans le fichier" << endl;
    cout << "6. CHARGER : Lire le fichier et dessiner" << endl;
    cout << "7. EFFACER : Nettoyer le canevas Java (CLEAR)" << endl;
    cout << "0. QUITTER" << endl;
    cout << "Choix : ";
}

int main() {
    const string NOM_FICHIER = "sauvegarde_scene.txt";
    try {
        ConnexionManager::getInstance()->connecter("127.0.0.1", 12345);
        VisiteurDessin visiteurD;

        // --- OBJETS PERSISTANTS ---
        Cercle* monCercle = new Cercle(Vecteur2D(100, 100), 40.0, Forme::RED);

        Groupe* monCarre = new Groupe(Forme::BLUE);
        monCarre->ajouter(new Segment(Vecteur2D(300, 300), Vecteur2D(500, 300), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(500, 300), Vecteur2D(500, 500), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(500, 500), Vecteur2D(300, 500), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(300, 500), Vecteur2D(300, 300), Forme::BLUE));

        vector<Vecteur2D> pts = { Vecteur2D(600, 100), Vecteur2D(550, 250), Vecteur2D(650, 250) };
        Polygone* monTriangle = new Polygone(pts, Forme::GREEN);

        // Configuration COR
        ChargeurForme* maillonSimple = new ChargeurCercle(new ChargeurSegment(new ChargeurPolygone(nullptr)));
        ChargeurGroupe* cor = new ChargeurGroupe(maillonSimple, nullptr);
        cor->setTete(cor);

        int choix = -1;
        while (choix != 0) {
            clearConsole();
            afficherMenu();
            if (!(cin >> choix)) break;

            switch (choix) {
            case 1:
                monCercle->accepte(&visiteurD);
                monCarre->accepte(&visiteurD);
                monTriangle->accepte(&visiteurD);
                break;

            case 2:
                monCercle->translation(Vecteur2D(50, 50));
                monCarre->translation(Vecteur2D(50, 50));
                monTriangle->translation(Vecteur2D(50, 50));
                cout << "\n[OK] Objets deplaces." << endl;
                break;

            case 3: {
                double angleDeg;
                cout << "Entrez l'angle de rotation en degres (ex: 45) : ";
                cin >> angleDeg;
                double rad = angleDeg * (M_PI / 180.0);
                Vecteur2D pivot(400, 300); 

                monCercle->rotation(pivot, rad);
                monCarre->rotation(pivot, rad);
                monTriangle->rotation(pivot, rad);

                cout << "\n[OK] Rotation de " << angleDeg << " deg effectuee." << endl;
                break;
            }

            case 4: {
                double k;
                cout << "Entrez le rapport d'homothetie (ex: 1.5 pour grossir, 0.5 pour reduire) : ";
                cin >> k;
                Vecteur2D pivot(400, 300);

               
                monCercle->homothetie(monCercle->getCentre(), k);
                monCarre->homothetie(pivot, k);
                monTriangle->homothetie(pivot, k);

                cout << "\n[OK] Homothetie de rapport " << k << " effectuee." << endl;
                break;
            }

            case 5: {
                VisiteurSauvegardeTexte vS(NOM_FICHIER);
                monCercle->accepte(&vS);
                monCarre->accepte(&vS);
                monTriangle->accepte(&vS);
                cout << "\n[SAVE] Scene enregistree dans le dossier build." << endl;
                break;
            }

            case 6: {
                ifstream flux(NOM_FICHIER);
                if (!flux) { cout << "Erreur: Fichier absent." << endl; break; }
                string ligne;
                while (getline(flux, ligne)) {
                    if (ligne.empty()) continue;
                    Forme* f = cor->charger(ligne, flux);
                    if (f) { f->accepte(&visiteurD); delete f; }
                }
                flux.close();
                break;
            }

            case 7:
                ConnexionManager::getInstance()->envoyer("CLEAR\n");
                break;
            }
            if (choix != 0) {
                cout << "\nAppuyez sur Entree pour continuer...";
                cin.ignore(); cin.get();
            }
        }

        ConnexionManager::getInstance()->deconnecter();
        delete monCercle; delete monCarre; delete monTriangle; delete cor;

    }
    catch (const exception& e) {
        cerr << "ERREUR : " << e.what() << endl;
    }
    return 0;
}