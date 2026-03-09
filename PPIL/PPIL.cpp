/**
 * @file main.cpp
 * @brief Console de Soutenance Finale : Cercle, Segment, Polygone et Groupes.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib> // Pour system("cls")

#include "header/Vecteur2D.h"
#include "header/Cercle.h"
#include "header/Segement.h"
#include "header/Polygone.h"
#include "header/Group.h"
#include "header/VisiteurDessin.h"
#include "header/Connexion_m.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void afficherMenu() {
    cout << "\n========== PANNEAU DE CONTROLE PPIL ==========" << endl;
    cout << "1. Envoyer TOUTES les formes (Cercle, Carre, Triangle)" << endl;
    cout << "2. TRANSLATION (+50, +50) sur tout" << endl;
    cout << "3. ROTATION (Choisir l'angle) sur tout" << endl;
    cout << "4. HOMOTHETIE (Choisir le ratio) sur tout" << endl;
    cout << "5. EFFACER LE SERVEUR JAVA (Reset History)" << endl;
    cout << "0. QUITTER" << endl;
    cout << "Choix : ";
}

int main() {
    try {
        ConnexionManager::getInstance()->connecter("127.0.0.1", 12345);
        VisiteurDessin visiteur;

        // --- PREPARATION DES OBJETS ---
        // 1. Cercle (Rouge)
        Cercle* monCercle = new Cercle(Vecteur2D(100, 100), 40.0, Forme::RED);

        // 2. Carre (Groupe Bleu de 4 Segments)
        Groupe* monCarre = new Groupe(Forme::BLUE);
        monCarre->ajouter(new Segment(Vecteur2D(300, 300), Vecteur2D(500, 300), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(500, 300), Vecteur2D(500, 500), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(500, 500), Vecteur2D(300, 500), Forme::BLUE));
        monCarre->ajouter(new Segment(Vecteur2D(300, 500), Vecteur2D(300, 300), Forme::BLUE));

        // 3. Triangle (Polygone Vert)
        vector<Vecteur2D> pts = { Vecteur2D(600, 100), Vecteur2D(550, 250), Vecteur2D(650, 250) };
        Polygone* monTriangle = new Polygone(pts, Forme::GREEN);

        int choix = -1;
        while (choix != 0) {
            system("cls"); // Nettoie la console C++ pour chaque tour de menu
            afficherMenu();
            if (!(cin >> choix)) break;

            switch (choix) {
            case 1:
                monCercle->accepte(&visiteur);
                monCarre->accepte(&visiteur);
                monTriangle->accepte(&visiteur);
                cout << "\n > Formes envoyees." << endl;
                break;

            case 2:
                monCercle->translation(Vecteur2D(50, 50));
                monCarre->translation(Vecteur2D(50, 50));
                monTriangle->translation(Vecteur2D(50, 50));
                monCercle->accepte(&visiteur);
                monCarre->accepte(&visiteur);
                monTriangle->accepte(&visiteur);
                break;

            case 3: {
                double angle; cout << "Angle (deg) : "; cin >> angle;
                double rad = angle * (M_PI / 180.0);
                Vecteur2D pivot(400, 300); // Centre de rotation
                monCercle->rotation(pivot, rad);
                monCarre->rotation(pivot, rad);
                monTriangle->rotation(pivot, rad);
                monCercle->accepte(&visiteur);
                monCarre->accepte(&visiteur);
                monTriangle->accepte(&visiteur);
                break;
            }

            case 4: {
                double k; cout << "Ratio (ex: 1.2) : "; cin >> k;
                Vecteur2D pivot(400, 300);
                monCercle->homothetie(monCercle->getCentre(), k); // Le cercle grossit sur place
                monCarre->homothetie(pivot, k);
                monTriangle->homothetie(pivot, k);
                monCercle->accepte(&visiteur);
                monCarre->accepte(&visiteur);
                monTriangle->accepte(&visiteur);
                break;
            }

            case 5:
                ConnexionManager::getInstance()->envoyer("CLEAR\n");
                cout << "\n > Serveur Java nettoye." << endl;
                break;
            }
            if (choix != 0) {
                cout << "\nAppuyez sur Entree pour continuer...";
                cin.ignore(); cin.get();
            }
        }

        ConnexionManager::getInstance()->deconnecter();
        delete monCercle; delete monCarre; delete monTriangle;

    }
    catch (const exception& e) { cerr << "Erreur: " << e.what() << endl; }
    return 0;
}