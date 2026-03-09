package graphics;

import cor.ShapeHandler;
import java.awt.*;
import java.awt.image.BufferStrategy;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFrame;

/**
 * Fenêtre de rendu principal utilisant le rendu actif (Active Rendering).
 * Cette classe gère l'affichage graphique, la persistance de la scène (historique)
 * et l'optimisation du dessin via une stratégie de double buffering.
 */
public class DessinFenetre extends JFrame {
    private Canvas canvas;
    private BufferStrategy bs;
    
    /** * Liste servant de mémoire pour le "Scene Graph". 
     * Stocke toutes les requêtes de formes pour permettre le rafraîchissement complet.
     */
    private final List<String> history = new ArrayList<>();

    /**
     * Efface l'écran et réinitialise l'historique des formes.
     * Cette méthode est synchronisée pour éviter les conflits lors de l'accès à l'historique.
     */
    public synchronized void effacer() {
        history.clear(); // Vide la mémoire de la scène
        Graphics2D g2d = (Graphics2D) bs.getDrawGraphics();
        try {
            g2d.setColor(Color.WHITE);
            g2d.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
        } finally {
            g2d.dispose();
        }
        bs.show(); // Affiche le cadre blanc vide
        System.out.println("History cleared.");
    }

    /**
     * Constructeur de la fenêtre de dessin.
     * @param titre  Le titre de la fenêtre.
     * @param width  La largeur de la zone de dessin.
     * @param height La hauteur de la zone de dessin.
     */
    public DessinFenetre(String titre, int width, int height) {
        setTitle(titre);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
        canvas.setBackground(Color.WHITE);
        
        // On ignore le mécanisme de peinture standard d'AWT car nous gérons le rendu manuellement
        canvas.setIgnoreRepaint(true); 
        add(canvas);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        // Configuration du Double Buffering (2 tampons : un pour le calcul, un pour l'affichage)
        canvas.createBufferStrategy(2);
        bs = canvas.getBufferStrategy();
    }

    /**
     * Le cœur du moteur de rendu actif.
     * Méthode synchronisée pour gérer les requêtes provenant de plusieurs clients C++ en toute sécurité.
     * @param chain   La tête de la chaîne de responsabilité (ShapeHandler) pour traiter les formes.
     * @param request La nouvelle requête de forme à ajouter et à dessiner.
     */
    public synchronized void renderRequest(ShapeHandler chain, String request) {
        // 1. Sauvegarde de la nouvelle forme dans la mémoire de la scène
        if (request != null && !request.isEmpty()) {
            history.add(request);
        }

        // 2. Lancement de la boucle de rendu (stratégie robuste pour BufferStrategy)
        do {
            do {
                // Récupération du contexte graphique depuis le buffer
                Graphics2D g2d = (Graphics2D) bs.getDrawGraphics();
                try {
                    // Nettoyage de l'arrière-plan pour éviter les effets de "traînée"
                    g2d.setColor(Color.WHITE);
                    g2d.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

                    // Activation de l'anticrénelage pour une meilleure qualité visuelle
                    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, 
                                       RenderingHints.VALUE_ANTIALIAS_ON);

                    // 3. REDESSIN COMPLET DE L'HISTORIQUE
                    // On repasse chaque chaîne de caractères enregistrée à travers la chaîne de responsabilité
                    for (String shapeData : history) {
                        chain.handle(shapeData, g2d);
                    }

                } finally {
                    // Libération des ressources graphiques
                    g2d.dispose();
                }
            } while (bs.contentsRestored());
            
            // 4. Envoi du cadre complété à l'écran (Swap buffers)
            bs.show();
            
        } while (bs.contentsLost());
    }
}