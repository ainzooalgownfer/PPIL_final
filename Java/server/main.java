package server;

import cor.CercleHandler;
import cor.PolygoneHandler;
import cor.SegmentHandler;
import cor.ShapeHandler;
import graphics.DessinFenetre;

/**
 * Point d'entrée principal du serveur de dessin Java.
 * Cette classe orchestre l'initialisation de l'interface graphique, la configuration
 * du patron de conception "Chaîne de Responsabilité" et le lancement du serveur TCP.
 */
public class main {
    
    /**
     * Méthode principale (Main) qui lance l'application.
     * @param args Arguments de la ligne de commande (non utilisés ici).
     */
    public static void main(String[] args) {
        // 1. Définition du port d'écoute (doit correspondre au client C++ : 12345)
        int port = 12345;

        // 2. Initialisation de la fenêtre graphique (JFrame + Canvas)
        // Fournit le contexte Graphics2D nécessaire pour le rendu actif.
        DessinFenetre fenetre = new DessinFenetre("PPIL Drawing Server - L3 Synthesis", 800, 600);

        // 3. Assemblage de la Chaîne de Responsabilité (CoR)
        /* * Chaque maillon sait traiter un type de forme spécifique.
         * Si un maillon ne reconnaît pas la requête, il la passe au suivant.
         * Structure de la chaîne : Cercle -> Segment -> Polygone -> null (fin)
         */
        ShapeHandler chain = new CercleHandler(
                                new SegmentHandler(
                                    new PolygoneHandler(null)
                                )
                             );

        // 4. Démarrage du serveur multi-clients
        /* * Le serveur écoute les connexions entrantes et délègue chaque client 
         * à un thread séparé pour permettre des dessins simultanés.
         */
        DessinServer server = new DessinServer(port, fenetre, chain);
        
        System.out.println("Java Server is ready. Launch your C++ application now.");
        
        // Lancement de la boucle d'écoute du serveur
        server.start();
    }
}